// Draw_Voxel_Regular_Normals with each color lit through its normal's shade.
void Draw_Voxel_Regular_Normals_Lighting(VoxelFuncArgumentStruct *parameters)
{
    Fill_Delta_Table2(parameters);
    unsigned short x = parameters->TransformMatrix[0].I;
    unsigned short y = parameters->TransformMatrix[0].J;
    for (unsigned row = 0; row < parameters->YSize; row++) {
        unsigned row_column = parameters->StartIndex;
        unsigned short row_x = x;
        unsigned short row_y = y;
        for (unsigned column = 0; column < parameters->XSize; column++) {
            unsigned offset = ((unsigned *)parameters->StartOffset)[parameters->StartIndex];
            unsigned short column_x = x;
            unsigned short column_y = y;
            if (offset != 0xFFFFFFFF) {
                unsigned char *data = parameters->DataOffset + offset;
                unsigned remaining = parameters->ZSize;
                while (remaining) {
                    unsigned char value = *data;
                    data++;
                    x += unknown_steps_af8a10[value][0];
                    y += unknown_steps_af8a10[value][1];
                    remaining -= value;
                    unsigned count = *data;
                    data++;
                    if (count) {
                        remaining -= count;
                        while (count) {
                            value = *data;
                            data++;
                            unsigned char shade = *data;
                            data++;
                            shade = unknown_shades_af8e10[shade];
                            unsigned index = (x >> 8) | (y & 0xFF00);
                            unknown_grid_ae3408[index] = unknown_lit_colors_af4608[shade][value];
                            unknown_grid_ae3408[index + 1] = unknown_lit_colors_af4608[shade][value];
                            x += parameters->TransformMatrix[3].I;
                            y += parameters->TransformMatrix[3].J;
                            count--;
                        }
                    }
                    data++;
                }
            }
            x = column_x + parameters->TransformMatrix[1].I;
            y = column_y + parameters->TransformMatrix[1].J;
            parameters->StartIndex = parameters->StrideX + parameters->StartIndex;
        }
        x = row_x + parameters->TransformMatrix[2].I;
        y = row_y + parameters->TransformMatrix[2].J;
        parameters->StartIndex = parameters->StrideY + row_column;
    }
}
