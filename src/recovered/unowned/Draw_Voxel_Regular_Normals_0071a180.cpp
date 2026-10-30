// Draws a section's spans into the byte grid: each column's span list holds
// (skip, count, count (color, normal) pairs, count) runs; every voxel's color
// lands at the 8.8 fixed-point screen position stepped per depth, column and
// row. Not in the drawer table 0x007F9DE0 (hypothesis: the C version of an
// assembly drawer).
// Fill the per-depth screen offsets from the depth step (two inline
// variants with different code shapes).
inline void Fill_Delta_Table1(VoxelFuncArgumentStruct *parameters)
{
    short (&steps)[256][2] = unknown_steps_af8a10;
    steps[0][0] = 0;
    steps[0][1] = 0;
    Vector3i16 &step = parameters->TransformMatrix[3];
    for (unsigned depth = 1; depth < parameters->ZSize; depth++) {
        steps[depth][0] = steps[depth - 1][0] + step.I;
        steps[depth][1] = steps[depth - 1][1] + step.J;
    }
}

inline void Fill_Delta_Table2(VoxelFuncArgumentStruct *parameters)
{
    unknown_steps_af8a10[0][0] = 0;
    unknown_steps_af8a10[0][1] = 0;
    Vector3i16 *step = &parameters->TransformMatrix[3];
    for (unsigned depth = 1; depth < parameters->ZSize; depth++) {
        unknown_steps_af8a10[depth][0] = unknown_steps_af8a10[depth - 1][0] + step->I;
        unknown_steps_af8a10[depth][1] = unknown_steps_af8a10[depth - 1][1] + step->J;
    }
}

void Draw_Voxel_Regular_Normals(VoxelFuncArgumentStruct *parameters)
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
                    unsigned char skip = *data;
                    data++;
                    x += unknown_steps_af8a10[skip][0];
                    y += unknown_steps_af8a10[skip][1];
                    remaining -= skip;
                    unsigned count = *data;
                    data++;
                    if (count) {
                        remaining -= count;
                        while (count) {
                            unsigned char color = *data;
                            data++;
                            data++;
                            unsigned index = (x >> 8) | (y & 0xFF00);
                            unknown_grid_ae3408[index] = color;
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
