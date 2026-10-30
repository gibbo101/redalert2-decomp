// Draw_Voxel_Regular with the depth test of Draw_Voxel_Regular_Normals_ZBuffer.
inline void Fill_Delta_Table3(VoxelFuncArgumentStruct *parameters)
{
    short (&steps)[256][2] = unknown_steps_af8a10;
    steps[0][0] = 0;
    steps[0][1] = 0;
    Vector3i16 &step = parameters->TransformMatrix[3];
    for (unsigned depth = 1; depth < parameters->ZSize; depth++) {
        steps[depth][0] = steps[depth - 1][0] + step.I;
        unknown_steps_af8a10[depth][1] = unknown_steps_af8a10[depth - 1][1] + step.J;
    }
}

void Draw_Voxel_Regular_ZBuffer(VoxelFuncArgumentStruct *parameters)
{
    Fill_Delta_Table3(parameters);
    unsigned short x = parameters->TransformMatrix[0].I;
    unsigned short y = parameters->TransformMatrix[0].J;
    unsigned short z = parameters->TransformMatrix[0].K;
    for (unsigned row = 0; row < parameters->YSize; row++) {
        unsigned row_column = parameters->StartIndex;
        unsigned short row_x = x;
        unsigned short row_y = y;
        unsigned short row_z = z;
        for (unsigned column = 0; column < parameters->XSize; column++) {
            unsigned short column_x = x;
            unsigned short column_y = y;
            unsigned short column_z = z;
            unsigned offset = ((unsigned *)parameters->StartOffset)[parameters->StartIndex];
            if (offset != 0xFFFFFFFF) {
                unsigned char *data = parameters->DataOffset + offset;
                unsigned remaining = parameters->ZSize;
                while (remaining) {
                    unsigned char value = *data;
                    data++;
                    x += unknown_steps_af8a10[value][0];
                    y += unknown_steps_af8a10[value][1];
                    z += parameters->TransformMatrix[3].K * value;
                    remaining -= value;
                    unsigned count = *data;
                    data++;
                    if (count) {
                        remaining -= count;
                        while (count) {
                            value = *data;
                            data++;
                            unsigned index = (x >> 8) | (y & 0xFF00);
                            if ((z >> 8) > unknown_zbuffer_ad0a70[index]) {
                                unknown_zbuffer_ad0a70[index] = z >> 8;
                                unknown_grid_ae3408[index] = value;
                                unknown_grid_ae3408[index + 1] = value;
                                unknown_zbuffer_ad0a70[index + 1] = z >> 8;
                            }
                            x += parameters->TransformMatrix[3].I;
                            y += parameters->TransformMatrix[3].J;
                            z += parameters->TransformMatrix[3].K;
                            count--;
                        }
                    }
                    data++;
                }
            }
            x = column_x + parameters->TransformMatrix[1].I;
            y = column_y + parameters->TransformMatrix[1].J;
            z = column_z + parameters->TransformMatrix[1].K;
            parameters->StartIndex = parameters->StrideX + parameters->StartIndex;
        }
        x = row_x + parameters->TransformMatrix[2].I;
        y = row_y + parameters->TransformMatrix[2].J;
        z = row_z + parameters->TransformMatrix[2].K;
        parameters->StartIndex = parameters->StrideY + row_column;
    }
}
