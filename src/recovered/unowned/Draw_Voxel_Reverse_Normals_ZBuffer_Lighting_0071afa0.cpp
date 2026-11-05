// Reverse span drawing with normal lighting and the native unsigned depth test.
void Draw_Voxel_Reverse_Normals_ZBuffer_Lighting(VoxelFuncArgumentStruct *parameters)
{
    Fill_Delta_Table2(parameters);
    unsigned short x=parameters->TransformMatrix[0].I;
    unsigned short y=parameters->TransformMatrix[0].J;
    unsigned short z=parameters->TransformMatrix[0].K;
    for (unsigned row=0;row<parameters->YSize;++row) {
        unsigned row_column=parameters->StartIndex;
        unsigned short row_x=x, row_y=y, row_z=z;
        for (unsigned column=0;column<parameters->XSize;++column) {
            unsigned short column_x=x, column_y=y, column_z=z;
            unsigned offset=((unsigned *)parameters->EndOffset)[parameters->StartIndex];
            if (offset!=0xffffffff) {
                unsigned char *data=parameters->DataOffset+offset;
                unsigned remaining=parameters->ZSize;
                while (remaining) {
                    unsigned count=*data;
                    --data;
                    unsigned char value;
                    unsigned char normal_index;
                    unsigned char &shade=normal_index;
                    if (count) {
                        remaining-=count;
                        while (count) {
                            unsigned index=(x>>8)|(y&0xff00);
                            if ((z>>8)>unknown_zbuffer_ad0a70[index]) {
                                shade=*data;
                                --data;
                                shade=unknown_shades_af8e10[shade];
                                value=*data;
                                --data;
                                value=unknown_lit_colors_af4608[shade][value];
                                unknown_zbuffer_ad0a70[index]=z>>8;
                                unknown_zbuffer_ad0a70[index+1]=z>>8;
                                unknown_grid_ae3408[index]=value;
                                unknown_grid_ae3408[index+1]=value;
                            } else data-=2;
                            x+=parameters->TransformMatrix[3].I;
                            y+=parameters->TransformMatrix[3].J;
                            z+=parameters->TransformMatrix[3].K;
                            --count;
                        }
                    }
                    --data;
                    value=*data;
                    --data;
                    x+=unknown_steps_af8a10[value][0];
                    y+=unknown_steps_af8a10[value][1];
                    z+=parameters->TransformMatrix[3].K*value;
                    remaining-=value;
                }
            }
            x=column_x+parameters->TransformMatrix[1].I;
            y=column_y+parameters->TransformMatrix[1].J;
            z=column_z+parameters->TransformMatrix[1].K;
            parameters->StartIndex=parameters->StrideX+parameters->StartIndex;
        }
        x=row_x+parameters->TransformMatrix[2].I;
        y=row_y+parameters->TransformMatrix[2].J;
        z=row_z+parameters->TransformMatrix[2].K;
        parameters->StartIndex=parameters->StrideY+row_column;
    }
}
