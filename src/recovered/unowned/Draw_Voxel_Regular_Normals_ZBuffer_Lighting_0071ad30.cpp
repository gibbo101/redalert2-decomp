// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void Draw_Voxel_Regular_Normals_ZBuffer_Lighting(VoxelFuncArgumentStruct *parameters) (0x0071AD30)
// Adopted from ra2-decomp Draw_Voxel_Regular_Normals_ZBuffer_Lighting (YR 0x00757980).
// Draw_Voxel_Regular_Normals_ZBuffer with each colour lit through its normal's
// shade: a voxel lands only where its depth is above the depth grid's byte and
// writes two neighbouring cells of both grids.
void Draw_Voxel_Regular_Normals_ZBuffer_Lighting(VoxelFuncArgumentStruct *state)
{
    Fill_Delta_Table2(state);

    unsigned char value;
    unsigned char normal_index;
    unsigned short pixel_x = state->TransformMatrix[0].I;
    unsigned short pixel_y = state->TransformMatrix[0].J;
    unsigned short pixel_z = state->TransformMatrix[0].K;

    for (unsigned int y = 0; y < state->YSize; y++) {
        unsigned int base_index = state->StartIndex;
        unsigned short row_start_x = pixel_x;
        unsigned short row_start_y = pixel_y;
        unsigned short row_start_z = pixel_z;
        for (unsigned int x = 0; x < state->XSize; x++) {
            unsigned short column_start_x = pixel_x;
            unsigned short column_start_y = pixel_y;
            unsigned short column_start_z = pixel_z;
            unsigned int data_offset = ((unsigned int *)state->StartOffset)[state->StartIndex];
            if (data_offset != 0xFFFFFFFF) {
                unsigned char * ptr = state->DataOffset + data_offset;
                unsigned int remaining = state->ZSize;
                while (remaining) {
                    value = *ptr;
                    ptr++;
                    pixel_x += unknown_steps_af8a10[value][0];
                    pixel_y += unknown_steps_af8a10[value][1];
                    pixel_z += state->TransformMatrix[3].K * value;
                    remaining -= value;
                    unsigned int run_length = *ptr;
                    ptr++;
                    if (run_length) {
                        remaining -= run_length;
                        while (run_length) {
                            unsigned int buffer_index = (pixel_x >> 8) | (pixel_y & 0xFF00);
                            if ((pixel_z >> 8) > unknown_zbuffer_ad0a70[buffer_index]) {
                                value = *ptr;
                                ptr++;
                                normal_index = *ptr;
                                ptr++;
                                normal_index = unknown_shades_af8e10[normal_index];
                                unknown_grid_ae3408[buffer_index] = unknown_lit_colors_af4608[normal_index][value];
                                unknown_grid_ae3408[buffer_index + 1] = unknown_lit_colors_af4608[normal_index][value];
                                unknown_zbuffer_ad0a70[buffer_index] = (pixel_z >> 8);
                                unknown_zbuffer_ad0a70[buffer_index + 1] = (pixel_z >> 8);
                            } else {
                                ptr++;
                                ptr++;
                            }
                            pixel_x += state->TransformMatrix[3].I;
                            pixel_y += state->TransformMatrix[3].J;
                            pixel_z += state->TransformMatrix[3].K;
                            run_length--;
                        }
                    }
                    ptr++;
                }
            }
            pixel_x = column_start_x + state->TransformMatrix[1].I;
            pixel_y = column_start_y + state->TransformMatrix[1].J;
            pixel_z = column_start_z + state->TransformMatrix[1].K;
            state->StartIndex = state->StrideX + state->StartIndex;
        }
        pixel_x = row_start_x + state->TransformMatrix[2].I;
        pixel_y = row_start_y + state->TransformMatrix[2].J;
        pixel_z = row_start_z + state->TransformMatrix[2].K;
        state->StartIndex = state->StrideY + base_index;
    }
}
