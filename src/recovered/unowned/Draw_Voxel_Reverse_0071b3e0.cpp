void Draw_Voxel_Reverse(VoxelFuncArgumentStruct *parameters)
{
    Fill_Delta_Table2(parameters);
    unsigned short x = parameters->TransformMatrix[0].I;
    unsigned short y = parameters->TransformMatrix[0].J;
    for (unsigned row = 0; row < parameters->YSize; row++) {
        unsigned row_column = parameters->StartIndex;
        unsigned short row_x = x;
        unsigned short row_y = y;
        for (unsigned column = 0; column < parameters->XSize; column++) {
            unsigned offset = ((unsigned *)parameters->EndOffset)[parameters->StartIndex];
            unsigned short column_x = x;
            unsigned short column_y = y;
            if (offset != 0xFFFFFFFF) {
                unsigned char *data = parameters->DataOffset + offset;
                unsigned remaining = parameters->ZSize;
                while (remaining) {
                    unsigned count = *data;
                    data--;
                    if (count) {
                        remaining -= count;
                        while (count) {
                            unsigned char color = *data;
                            data--;
                            unknown_grid_ae3408[(x >> 8) | (y & 0xFF00)] = color;
                            unknown_grid_ae3408[(x >> 8) | (y & 0xFF00) + 1] = color;
                            x += parameters->TransformMatrix[3].I;
                            y += parameters->TransformMatrix[3].J;
                            count--;
                        }
                    }
                    data--;
                    unsigned char skip = *data;
                    data--;
                    x += unknown_steps_af8a10[skip][0];
                    y += unknown_steps_af8a10[skip][1];
                    remaining -= skip;
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
