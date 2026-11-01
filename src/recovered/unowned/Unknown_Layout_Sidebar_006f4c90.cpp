// void Unknown_Layout_Sidebar_006F4C90(int width, int height) (0x006F4C90)
// Lays out the sidebar rectangles for a screen of width x height from the
// sixteen sidebar shapes 0x006F4B00 loads (0x006F5150 frees them): the
// backdrop (small/medium/large by width 640/800), the right column pieces,
// the repeated strip count (0x00AC10CC), the bottom bar pieces and the
// repeated tab count (0x00AC0FF4), then the merged column rectangles.
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ??2@YAPAXI@Z=00782017
// @ref ?unknown_window_839640@@3VRect@@A=00839640
// @ref ?unknown_shape_ac10c4@@3PAUShapeFileStruct@@A=00ac10c4
// @ref ?unknown_shape_ac10bc@@3PAUShapeFileStruct@@A=00ac10bc
// @ref ?unknown_shape_ac105c@@3PAUShapeFileStruct@@A=00ac105c
// @ref ?unknown_shape_ac10f8@@3PAUShapeFileStruct@@A=00ac10f8
// @ref ?unknown_shape_ac0ff0@@3PAUShapeFileStruct@@A=00ac0ff0
// @ref ?unknown_shape_ac1070@@3PAUShapeFileStruct@@A=00ac1070
// @ref ?unknown_shape_ac1078@@3PAUShapeFileStruct@@A=00ac1078
// @ref ?unknown_shape_ac10ec@@3PAUShapeFileStruct@@A=00ac10ec
// @ref ?unknown_shape_ac1094@@3PAUShapeFileStruct@@A=00ac1094
// @ref ?unknown_shape_ac1058@@3PAUShapeFileStruct@@A=00ac1058
// @ref ?unknown_shape_ac1048@@3PAUShapeFileStruct@@A=00ac1048
// @ref ?unknown_shape_ac1098@@3PAUShapeFileStruct@@A=00ac1098
// @ref ?unknown_shape_ac10a4@@3PAUShapeFileStruct@@A=00ac10a4
// @ref ?unknown_shape_ac10b0@@3PAUShapeFileStruct@@A=00ac10b0
// @ref ?unknown_rect_ac11d4@@3PAVRect@@A=00ac11d4
// @ref ?unknown_rect_ac11d8@@3PAVRect@@A=00ac11d8
// @ref ?unknown_rect_ac11dc@@3PAVRect@@A=00ac11dc
// @ref ?unknown_rect_ac11e0@@3PAVRect@@A=00ac11e0
// @ref ?unknown_rect_ac11e8@@3PAVRect@@A=00ac11e8
// @ref ?unknown_rect_ac11ec@@3PAVRect@@A=00ac11ec
// @ref ?unknown_rect_ac11f0@@3PAVRect@@A=00ac11f0
// @ref ?unknown_rect_ac11f4@@3PAVRect@@A=00ac11f4
// @ref ?unknown_rect_ac11fc@@3PAVRect@@A=00ac11fc
// @ref ?unknown_rect_ac1200@@3PAVRect@@A=00ac1200
// @ref ?unknown_rect_ac1204@@3PAVRect@@A=00ac1204
// @ref ?unknown_rect_ac1208@@3PAVRect@@A=00ac1208
// @ref ?unknown_rect_ac120c@@3PAVRect@@A=00ac120c
// @ref ?unknown_rect_ac1210@@3PAVRect@@A=00ac1210
// @ref ?unknown_rect_ac11e4@@3PAVRect@@A=00ac11e4
// @ref ?unknown_rect_ac11f8@@3PAVRect@@A=00ac11f8
// @ref ?unknown_value_ac10cc@@3HA=00ac10cc
// @ref ?unknown_value_ac0ff4@@3HA=00ac0ff4
// @ref ?unknown_value_ac10c8@@3HA=00ac10c8
// @ref ?unknown_value_ac10a0@@3HA=00ac10a0
// @ref ?unknown_value_ac1080@@3HA=00ac1080
#define SHAPE_FILE_EMPTY_RECT Rect(0, 0, 0, 0)
#include "shared/shape_file.hpp"
#include "shared/shell_art.hpp"

extern ShapeFileStruct *unknown_shape_ac10c4;
extern ShapeFileStruct *unknown_shape_ac10bc;
extern ShapeFileStruct *unknown_shape_ac105c;
extern ShapeFileStruct *unknown_shape_ac10f8;
extern ShapeFileStruct *unknown_shape_ac0ff0;
extern ShapeFileStruct *unknown_shape_ac1070;
extern ShapeFileStruct *unknown_shape_ac1078;
extern ShapeFileStruct *unknown_shape_ac10ec;
extern ShapeFileStruct *unknown_shape_ac1094;
extern ShapeFileStruct *unknown_shape_ac1058;
extern ShapeFileStruct *unknown_shape_ac1048;
extern ShapeFileStruct *unknown_shape_ac1098;
extern ShapeFileStruct *unknown_shape_ac10a4;
extern ShapeFileStruct *unknown_shape_ac10b0;
extern Rect *unknown_rect_ac11d4;
extern Rect *unknown_rect_ac11d8;
extern Rect *unknown_rect_ac11dc;
extern Rect *unknown_rect_ac11e0;
extern Rect *unknown_rect_ac11e8;
extern Rect *unknown_rect_ac11ec;
extern Rect *unknown_rect_ac11f0;
extern Rect *unknown_rect_ac11f4;
extern Rect *unknown_rect_ac11fc;
extern Rect *unknown_rect_ac1200;
extern Rect *unknown_rect_ac1204;
extern Rect *unknown_rect_ac1208;
extern Rect *unknown_rect_ac120c;
extern Rect *unknown_rect_ac1210;
extern Rect *unknown_rect_ac11e4;
extern Rect *unknown_rect_ac11f8;
extern int unknown_value_ac10cc;
extern int unknown_value_ac0ff4;
extern int unknown_value_ac10c8;
extern int unknown_value_ac10a0;
extern int unknown_value_ac1080;
extern int unknown_value_8523e0;                 // screen width

void __fastcall Unknown_Layout_Sidebar_006F4C90(int width, int height)
{
    ShapeFileStruct *backdrop;
    if (unknown_value_8523e0 == 640) {
        backdrop = unknown_shape_ac10c4;
    } else if (unknown_value_8523e0 == 800) {
        backdrop = unknown_shape_ac10bc;
    } else {
        backdrop = unknown_shape_ac105c;
    }
    int w = backdrop->Get_Width();
    int h = backdrop->Get_Height();
    unknown_rect_ac11d4 = new Rect(0, 0, w, h);

    w = unknown_shape_ac10f8->Get_Width();
    h = unknown_shape_ac10f8->Get_Height();
    int x = width - w;
    unknown_rect_ac11d8 = new Rect(x, 0, w, h);
    int y = h;
    h = unknown_shape_ac0ff0->Get_Height();
    unknown_rect_ac11dc = new Rect(x, y, w, h);
    y += h;
    h = unknown_shape_ac1070->Get_Height();
    unknown_rect_ac11e0 = new Rect(x, y, w, h);
    y += h;
    h = unknown_shape_ac1078->Get_Height();
    unknown_rect_ac11e8 = new Rect(x, y, w, h);
    y += h;
    h = unknown_shape_ac10ec->Get_Height();
    unknown_rect_ac11ec = new Rect(x, y, w, h);
    h = unknown_shape_ac1094->Get_Height();
    unknown_rect_ac11f0 = new Rect(x, y, w, h);
    h = unknown_shape_ac1058->Get_Height();
    unknown_rect_ac11f4 = new Rect(x, y, w, h);

    unknown_value_ac10cc = (height - unknown_rect_ac11f0->Height - unknown_rect_ac11e8->Height - unknown_rect_ac11e0->Height
                            - unknown_rect_ac11dc->Height - unknown_rect_ac11d8->Height) / unknown_rect_ac11ec->Height;
    y += unknown_value_ac10cc * unknown_rect_ac11ec->Height;
    unknown_rect_ac11f0->Y = y;
    unknown_rect_ac11f4->Y = unknown_rect_ac11f0->Height + y;

    y = height - 32;
    int bar_width = Unknown_Bar_Rect().Width;
    unknown_rect_ac11fc = new Rect(0, y, bar_width, 32);
    w = unknown_shape_ac1048->Get_Width();
    h = unknown_shape_ac1048->Get_Height();
    unknown_rect_ac1200 = new Rect(0, y, w, h);
    w = unknown_shape_ac1098->Get_Width();
    h = unknown_shape_ac1098->Get_Height();
    unknown_rect_ac1204 = new Rect(0, y, w, h);
    unknown_rect_ac1208 = new Rect(0, y, w, h);
    w = unknown_shape_ac10a4->Get_Width();
    h = unknown_shape_ac10a4->Get_Height();
    unknown_rect_ac120c = new Rect(0, y, w, h);
    w = unknown_shape_ac10b0->Get_Width();
    h = unknown_shape_ac10b0->Get_Height();
    unknown_rect_ac1210 = new Rect(0, y, w, h);

    unknown_value_ac0ff4 = (width - unknown_rect_ac1204->Width - unknown_rect_ac11d8->Width - unknown_rect_ac1210->Width)
                           / unknown_rect_ac120c->Width;
    int bar_x = unknown_rect_ac11d8->X - unknown_rect_ac1210->Width;
    unknown_rect_ac1210->X = bar_x;
    bar_x -= unknown_rect_ac120c->Width * unknown_value_ac0ff4;
    unknown_rect_ac120c->X = bar_x;
    bar_x -= unknown_rect_ac1204->Width;
    unknown_rect_ac1204->X = bar_x;
    unknown_value_ac10c8 = bar_x;
    int tab_x = unknown_rect_ac1210->X - unknown_rect_ac1208->Width;
    unknown_rect_ac1208->X = tab_x;
    unknown_value_ac10a0 = tab_x;
    unknown_value_ac1080 = unknown_rect_ac1210->X - unknown_rect_ac1204->Width - unknown_rect_ac1204->X;

    int column_x = unknown_rect_ac11dc->X;
    int column_y = unknown_rect_ac11dc->Y;
    int column_width = unknown_rect_ac11dc->Width;
    int column_height = unknown_rect_ac11e0->Height + unknown_rect_ac11dc->Height;
    unknown_rect_ac11e4 = new Rect(column_x, column_y, column_width, column_height);
    int strip_x = unknown_rect_ac11e8->X;
    int strip_y = unknown_rect_ac11e8->Y;
    int strip_width = unknown_rect_ac11e8->Width;
    int strip_height = unknown_value_ac10cc * unknown_rect_ac11ec->Height + unknown_rect_ac11f0->Height + unknown_rect_ac11e8->Height;
    unknown_rect_ac11f8 = new Rect(strip_x, strip_y, strip_width, strip_height);
}
