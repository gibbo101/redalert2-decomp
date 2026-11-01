// @ref ?unknown_shape_empty_rect_84ed88@@3VRect@@B=0084ed88
// Original0045ED50: rectangle of one shape frame,108body+4padding.
#include "shared/rect.hpp"
extern Rect const unknown_shape_empty_rect_84ed88;
#define SHAPE_FILE_EMPTY_RECT unknown_shape_empty_rect_84ed88
#define RA2_SHAPE_RECT_SOURCE
#include "shared/shape_file.hpp"
Rect ShapeFileStruct::Get_Frame_Rect(int frame) const
{
    ShapeFileFrameStruct const *record=Get_Frame(frame);
    if (record) return Rect(record->X,record->Y,record->Width,record->Height);
    return unknown_shape_empty_rect_84ed88;
}
