////////////////////////////////////////////////////////////////////////////
//	Module 		: debug_renderer.cpp
//	Created 	: 19.06.2006
//  Modified 	: 19.06.2006
//	Author		: Dmitriy Iassenev
//	Description : debug renderer
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef DEBUG
#include "debug_renderer.h"

void CDebugRenderer::add_lines(
    Fvector const* vertices, u32 const& vertex_count, u16 const* pairs, u32 const& pair_count, u32 const& color)
{
    GEnv.DRender->add_lines(vertices, vertex_count, pairs, pair_count, color);
}

void CDebugRenderer::draw_obb(const Fmatrix& matrix, const u32& color)
{
    Fvector aabb[8];
    matrix.transform_tiny(aabb[0], Fvector().set(-1, -1, -1)); // 0
    matrix.transform_tiny(aabb[1], Fvector().set(-1, +1, -1)); // 1
    matrix.transform_tiny(aabb[2], Fvector().set(+1, +1, -1)); // 2
    matrix.transform_tiny(aabb[3], Fvector().set(+1, -1, -1)); // 3
    matrix.transform_tiny(aabb[4], Fvector().set(-1, -1, +1)); // 4
    matrix.transform_tiny(aabb[5], Fvector().set(-1, +1, +1)); // 5
    matrix.transform_tiny(aabb[6], Fvector().set(+1, +1, +1)); // 6
    matrix.transform_tiny(aabb[7], Fvector().set(+1, -1, +1)); // 7

    u16 aabb_id[12 * 2] = {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 1, 5, 2, 6, 3, 7, 0, 4};

    add_lines(aabb, sizeof(aabb) / sizeof(Fvector), &aabb_id[0], sizeof(aabb_id) / (2 * sizeof(u16)), color);
}

void CDebugRenderer::draw_obb(const Fmatrix& matrix, const Fvector& half_size, const u32& color)
{
    Fmatrix mL2W_Transform, mScaleTransform;

    mScaleTransform.scale(half_size);
    mL2W_Transform.mul_43(matrix, mScaleTransform);

    draw_obb(mL2W_Transform, color);
}

void CDebugRenderer::draw_ellipse(const Fmatrix& matrix, const u32& color)
{
    float vertices[114 * 3] = {0.0000f, 0.0000f, 1.0000f, 0.0000f, 0.3827f, 0.9239f, -0.1464f, 0.3536f, 0.9239f,
        -0.2706f, 0.2706f, 0.9239f, -0.3536f, 0.1464f, 0.9239f, -0.3827f, 0.0000f, 0.9239f, -0.3536f, -0.1464f, 0.9239f,
        -0.2706f, -0.2706f, 0.9239f, -0.1464f, -0.3536f, 0.9239f, 0.0000f, -0.3827f, 0.9239f, 0.1464f, -0.3536f,
        0.9239f, 0.2706f, -0.2706f, 0.9239f, 0.3536f, -0.1464f, 0.9239f, 0.3827f, 0.0000f, 0.9239f, 0.3536f, 0.1464f,
        0.9239f, 0.2706f, 0.2706f, 0.9239f, 0.1464f, 0.3536f, 0.9239f, 0.0000f, 0.7071f, 0.7071f, -0.2706f, 0.6533f,
        0.7071f, -0.5000f, 0.5000f, 0.7071f, -0.6533f, 0.2706f, 0.7071f, -0.7071f, 0.0000f, 0.7071f, -0.6533f, -0.2706f,
        0.7071f, -0.5000f, -0.5000f, 0.7071f, -0.2706f, -0.6533f, 0.7071f, 0.0000f, -0.7071f, 0.7071f, 0.2706f,
        -0.6533f, 0.7071f, 0.5000f, -0.5000f, 0.7071f, 0.6533f, -0.2706f, 0.7071f, 0.7071f, 0.0000f, 0.7071f, 0.6533f,
        0.2706f, 0.7071f, 0.5000f, 0.5000f, 0.7071f, 0.2706f, 0.6533f, 0.7071f, 0.0000f, 0.9239f, 0.3827f, -0.3536f,
        0.8536f, 0.3827f, -0.6533f, 0.6533f, 0.3827f, -0.8536f, 0.3536f, 0.3827f, -0.9239f, 0.0000f, 0.3827f, -0.8536f,
        -0.3536f, 0.3827f, -0.6533f, -0.6533f, 0.3827f, -0.3536f, -0.8536f, 0.3827f, 0.0000f, -0.9239f, 0.3827f,
        0.3536f, -0.8536f, 0.3827f, 0.6533f, -0.6533f, 0.3827f, 0.8536f, -0.3536f, 0.3827f, 0.9239f, 0.0000f, 0.3827f,
        0.8536f, 0.3536f, 0.3827f, 0.6533f, 0.6533f, 0.3827f, 0.3536f, 0.8536f, 0.3827f, 0.0000f, 1.0000f, 0.0000f,
        -0.3827f, 0.9239f, 0.0000f, -0.7071f, 0.7071f, 0.0000f, -0.9239f, 0.3827f, 0.0000f, -1.0000f, 0.0000f, 0.0000f,
        -0.9239f, -0.3827f, 0.0000f, -0.7071f, -0.7071f, 0.0000f, -0.3827f, -0.9239f, 0.0000f, 0.0000f, -1.0000f,
        0.0000f, 0.3827f, -0.9239f, 0.0000f, 0.7071f, -0.7071f, 0.0000f, 0.9239f, -0.3827f, 0.0000f, 1.0000f, 0.0000f,
        0.0000f, 0.9239f, 0.3827f, 0.0000f, 0.7071f, 0.7071f, 0.0000f, 0.3827f, 0.9239f, 0.0000f, 0.0000f, 0.9239f,
        -0.3827f, -0.3536f, 0.8536f, -0.3827f, -0.6533f, 0.6533f, -0.3827f, -0.8536f, 0.3536f, -0.3827f, -0.9239f,
        0.0000f, -0.3827f, -0.8536f, -0.3536f, -0.3827f, -0.6533f, -0.6533f, -0.3827f, -0.3536f, -0.8536f, -0.3827f,
        0.0000f, -0.9239f, -0.3827f, 0.3536f, -0.8536f, -0.3827f, 0.6533f, -0.6533f, -0.3827f, 0.8536f, -0.3536f,
        -0.3827f, 0.9239f, 0.0000f, -0.3827f, 0.8536f, 0.3536f, -0.3827f, 0.6533f, 0.6533f, -0.3827f, 0.3536f, 0.8536f,
        -0.3827f, 0.0000f, 0.7071f, -0.7071f, -0.2706f, 0.6533f, -0.7071f, -0.5000f, 0.5000f, -0.7071f, -0.6533f,
        0.2706f, -0.7071f, -0.7071f, 0.0000f, -0.7071f, -0.6533f, -0.2706f, -0.7071f, -0.5000f, -0.5000f, -0.7071f,
        -0.2706f, -0.6533f, -0.7071f, 0.0000f, -0.7071f, -0.7071f, 0.2706f, -0.6533f, -0.7071f, 0.5000f, -0.5000f,
        -0.7071f, 0.6533f, -0.2706f, -0.7071f, 0.7071f, 0.0000f, -0.7071f, 0.6533f, 0.2706f, -0.7071f, 0.5000f, 0.5000f,
        -0.7071f, 0.2706f, 0.6533f, -0.7071f, 0.0000f, 0.3827f, -0.9239f, -0.1464f, 0.3536f, -0.9239f, -0.2706f,
        0.2706f, -0.9239f, -0.3536f, 0.1464f, -0.9239f, -0.3827f, 0.0000f, -0.9239f, -0.3536f, -0.1464f, -0.9239f,
        -0.2706f, -0.2706f, -0.9239f, -0.1464f, -0.3536f, -0.9239f, 0.0000f, -0.3827f, -0.9239f, 0.1464f, -0.3536f,
        -0.9239f, 0.2706f, -0.2706f, -0.9239f, 0.3536f, -0.1464f, -0.9239f, 0.3827f, 0.0000f, -0.9239f, 0.3536f,
        0.1464f, -0.9239f, 0.2706f, 0.2706f, -0.9239f, 0.1464f, 0.3536f, -0.9239f, 0.0000f, 0.0000f, -1.0000f};

    u16 pairs[] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 0, 10, 0, 11, 0, 12, 0, 13, 0, 14, 0, 15, 0,
        16, 1, 2, 1, 17, 1, 18, 2, 3, 2, 18, 2, 19, 3, 4, 3, 19, 3, 20, 4, 5, 4, 20, 4, 21, 5, 6, 5, 21, 5, 22, 6, 7, 6,
        22, 6, 23, 7, 8, 7, 23, 7, 24, 8, 9, 8, 24, 8, 25, 9, 10, 9, 25, 9, 26, 10, 11, 10, 26, 10, 27, 11, 12, 11, 27,
        11, 28, 12, 13, 12, 28, 12, 29, 13, 14, 13, 29, 13, 30, 14, 15, 14, 30, 14, 31, 15, 16, 15, 31, 15, 32, 16, 1,
        16, 17, 16, 32, 17, 1, 17, 18, 17, 33, 17, 34, 18, 2, 18, 19, 18, 34, 18, 35, 19, 3, 19, 20, 19, 35, 19, 36, 20,
        4, 20, 21, 20, 36, 20, 37, 21, 5, 21, 22, 21, 37, 21, 38, 22, 6, 22, 23, 22, 38, 22, 39, 23, 7, 23, 24, 23, 39,
        23, 40, 24, 8, 24, 25, 24, 40, 24, 41, 25, 9, 25, 26, 25, 41, 25, 42, 26, 10, 26, 27, 26, 42, 26, 43, 27, 11,
        27, 28, 27, 43, 27, 44, 28, 12, 28, 29, 28, 44, 28, 45, 29, 13, 29, 30, 29, 45, 29, 46, 30, 14, 30, 31, 30, 46,
        30, 47, 31, 15, 31, 32, 31, 47, 31, 48, 32, 16, 32, 17, 32, 33, 32, 48, 33, 17, 33, 34, 33, 49, 33, 50, 34, 18,
        34, 35, 34, 50, 34, 51, 35, 19, 35, 36, 35, 51, 35, 52, 36, 20, 36, 37, 36, 52, 36, 53, 37, 21, 37, 38, 37, 53,
        37, 54, 38, 22, 38, 39, 38, 54, 38, 55, 39, 23, 39, 40, 39, 55, 39, 56, 40, 24, 40, 41, 40, 56, 40, 57, 41, 25,
        41, 42, 41, 57, 41, 58, 42, 26, 42, 43, 42, 58, 42, 59, 43, 27, 43, 44, 43, 59, 43, 60, 44, 28, 44, 45, 44, 60,
        44, 61, 45, 29, 45, 46, 45, 61, 45, 62, 46, 30, 46, 47, 46, 62, 46, 63, 47, 31, 47, 48, 47, 63, 47, 64, 48, 32,
        48, 33, 48, 49, 48, 64, 49, 33, 49, 50, 49, 65, 49, 66, 50, 34, 50, 51, 50, 66, 50, 67, 51, 35, 51, 52, 51, 67,
        51, 68, 52, 36, 52, 53, 52, 68, 52, 69, 53, 37, 53, 54, 53, 69, 53, 70, 54, 38, 54, 55, 54, 70, 54, 71, 55, 39,
        55, 56, 55, 71, 55, 72, 56, 40, 56, 57, 56, 72, 56, 73, 57, 41, 57, 58, 57, 73, 57, 74, 58, 42, 58, 59, 58, 74,
        58, 75, 59, 43, 59, 60, 59, 75, 59, 76, 60, 44, 60, 61, 60, 76, 60, 77, 61, 45, 61, 62, 61, 77, 61, 78, 62, 46,
        62, 63, 62, 78, 62, 79, 63, 47, 63, 64, 63, 79, 63, 80, 64, 48, 64, 49, 64, 65, 64, 80, 65, 49, 65, 66, 65, 81,
        65, 82, 66, 50, 66, 67, 66, 82, 66, 83, 67, 51, 67, 68, 67, 83, 67, 84, 68, 52, 68, 69, 68, 84, 68, 85, 69, 53,
        69, 70, 69, 85, 69, 86, 70, 54, 70, 71, 70, 86, 70, 87, 71, 55, 71, 72, 71, 87, 71, 88, 72, 56, 72, 73, 72, 88,
        72, 89, 73, 57, 73, 74, 73, 89, 73, 90, 74, 58, 74, 75, 74, 90, 74, 91, 75, 59, 75, 76, 75, 91, 75, 92, 76, 60,
        76, 77, 76, 92, 76, 93, 77, 61, 77, 78, 77, 93, 77, 94, 78, 62, 78, 79, 78, 94, 78, 95, 79, 63, 79, 80, 79, 95,
        79, 96, 80, 64, 80, 65, 80, 81, 80, 96, 81, 65, 81, 82, 81, 97, 81, 98, 82, 66, 82, 83, 82, 98, 82, 99, 83, 67,
        83, 84, 83, 99, 83, 100, 84, 68, 84, 85, 84, 100, 84, 101, 85, 69, 85, 86, 85, 101, 85, 102, 86, 70, 86, 87, 86,
        102, 86, 103, 87, 71, 87, 88, 87, 103, 87, 104, 88, 72, 88, 89, 88, 104, 88, 105, 89, 73, 89, 90, 89, 105, 89,
        106, 90, 74, 90, 91, 90, 106, 90, 107, 91, 75, 91, 92, 91, 107, 91, 108, 92, 76, 92, 93, 92, 108, 92, 109, 93,
        77, 93, 94, 93, 109, 93, 110, 94, 78, 94, 95, 94, 110, 94, 111, 95, 79, 95, 96, 95, 111, 95, 112, 96, 80, 96,
        81, 96, 97, 96, 112, 97, 81, 97, 98, 97, 112, 98, 82, 98, 97, 98, 99, 99, 83, 99, 98, 99, 100, 100, 84, 100, 99,
        100, 101, 101, 85, 101, 100, 101, 102, 102, 86, 102, 101, 102, 103, 103, 87, 103, 102, 103, 104, 104, 88, 104,
        103, 104, 105, 105, 89, 105, 104, 105, 106, 106, 90, 106, 105, 106, 107, 107, 91, 107, 106, 107, 108, 108, 92,
        108, 107, 108, 109, 109, 93, 109, 108, 109, 110, 110, 94, 110, 109, 110, 111, 111, 95, 111, 110, 111, 112, 112,
        96, 112, 97, 112, 111, 113, 97, 113, 98, 113, 99, 113, 100, 113, 101, 113, 102, 113, 103, 113, 104, 113, 105,
        113, 106, 113, 107, 113, 108, 113, 109, 113, 110, 113, 111, 113, 112};

    int count = sizeof(vertices) / (sizeof(float));
    Fvector* I = (Fvector*)vertices;
    Fvector* E = (Fvector*)(vertices + count);
    for (; I != E; ++I)
        matrix.transform_tiny(*I, Fvector().set(*I));

    add_lines((Fvector*)&vertices[0], sizeof(vertices) / sizeof(Fvector), &pairs[0], sizeof(pairs) / (2 * sizeof(u16)),
        color);
}
#endif // DEBUG
