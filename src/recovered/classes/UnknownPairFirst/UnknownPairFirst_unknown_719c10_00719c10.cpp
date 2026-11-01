#include "shared/surface.hpp"
inline void Draw_Shadow(VoxelFuncArgumentStruct *parameters, Surface *surface, int left, int top)
{
    unsigned short x = parameters->TransformMatrix[0].I;
    unsigned short y = parameters->TransformMatrix[0].J;
    unsigned row;
    unsigned row_column;
    unsigned short row_x;
    unsigned short row_y;
    if (surface) {
        for (row = 0; row < parameters->YSize; row++) {
            row_column = parameters->StartIndex;
            row_x = x;
            row_y = y;
            for (unsigned column = 0; column < parameters->XSize; column++) {
                unsigned offset = ((unsigned *)parameters->EndOffset)[parameters->StartIndex];
                unsigned short column_x = x;
                unsigned short column_y = y;
                if (offset != 0xFFFFFFFF) {
                    unsigned index = (x >> 8) | (y & 0xFF00);
                    unsigned short pixel_x = left + (x >> 8);
                    unsigned short pixel_y = top + (y >> 8);
                    int pixel = surface->Get_Pixel(Point2D(pixel_x, pixel_y));
                    int next = surface->Get_Pixel(Point2D(pixel_x + 1, pixel_y));
                    unknown_grid_ae3408[index] = pixel == 0;
                    unknown_grid_ae3408[index + 1] = next == 0;
                }
                x = column_x + parameters->TransformMatrix[1].I;
                y = column_y + parameters->TransformMatrix[1].J;
                parameters->StartIndex = parameters->StrideX + parameters->StartIndex;
            }
            x = row_x + parameters->TransformMatrix[2].I;
            y = row_y + parameters->TransformMatrix[2].J;
            parameters->StartIndex = parameters->StrideY + row_column;
        }
    } else {
        for (row = 0; row < parameters->YSize; row++) {
            row_column = parameters->StartIndex;
            row_x = x;
            row_y = y;
            for (unsigned column = 0; column < parameters->XSize; column++) {
                unsigned offset = ((unsigned *)parameters->EndOffset)[parameters->StartIndex];
                unsigned short column_x = x;
                unsigned short column_y = y;
                if (offset != 0xFFFFFFFF) {
                    unsigned char color = 1;
                    unsigned index = (x >> 8) | (y & 0xFF00);
                    unknown_grid_ae3408[index] = color;
                    unknown_grid_ae3408[index + 1] = color;
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
}

void UnknownPairFirst::unknown_719c10(UnknownVoxelRecord48 *record, Vector3 const *origin)
{
    UnknownVoxelTailer *tailer = unknown_719860(record->unknown_04, record->unknown_08);
    VoxelFuncArgumentStruct parameters;
    unsigned char size_x = tailer->unknown_a0;
    unsigned char size_y = tailer->unknown_a1;
    unsigned char size_z = 1;
    parameters.XSize = size_x;
    parameters.YSize = size_y;
    parameters.ZSize = size_z;
    parameters.StartOffset = 0;
    parameters.EndOffset = tailer->unknown_04;
    parameters.DataOffset = 0;
    Vector3 const &corner_x = record->Points[1];
    Vector3 const &corner = record->Points[2];
    Vector3 const &corner_y = record->Points[3];
    parameters.StrideX = 1;
    parameters.StrideY = size_x;
    parameters.StartIndex = 0;
    parameters.TransformMatrix[0].I = short(float(corner.X + 128 - origin->X) * 256);
    parameters.TransformMatrix[0].J = short(float(corner.Y + 128 - origin->Y) * 256);
    record->unknown_40 = record->unknown_40 + origin->X;
    record->unknown_44 = record->unknown_44 + origin->Y;
    parameters.TransformMatrix[1].I = (short)((corner_x.X - corner.X) / size_x * 256.0f);
    parameters.TransformMatrix[2].I = (short)((corner_y.X - corner.X) / size_y * 256.0f);
    parameters.TransformMatrix[1].J = (short)((corner_x.Y - corner.Y) / size_x * 256.0f);
    parameters.TransformMatrix[2].J = (short)((corner_y.Y - corner.Y) / size_y * 256.0f);
    Draw_Shadow(&parameters, record->unknown_3c, record->unknown_40, record->unknown_44);
}
