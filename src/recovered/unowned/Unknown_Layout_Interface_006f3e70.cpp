// void Unknown_Layout_Interface_006F3E70(int width, int height) (0x006F3E70)
// Lays out the interface panel rectangles for a screen of width x height:
// on screens of 1024x768 or more the 800x600 panel is centred. The main
// screen (MNSCRNS/MNSCRNL by 640/480), the sidebar top, warning and button
// background, the animated button, the multiplayer button, the button count
// (0x00AC102C) and the bottom piece, and the lower-left screen (LWSCRNS/L).
// @ref ??2@YAPAXI@Z=00782017
// @ref ?unknown_shape_ac1128@@3PAUShapeFileStruct@@A=00ac1128
// @ref ?unknown_shape_ac1010@@3PAUShapeFileStruct@@A=00ac1010
// @ref ?unknown_shape_ac10e8@@3PAUShapeFileStruct@@A=00ac10e8
// @ref ?unknown_shape_ac10b4@@3PAUShapeFileStruct@@A=00ac10b4
// @ref ?unknown_shape_ac107c@@3PAUShapeFileStruct@@A=00ac107c
// @ref ?unknown_shape_ac10b8@@3PAUShapeFileStruct@@A=00ac10b8
// @ref ?unknown_shape_ac0fec@@3PAUShapeFileStruct@@A=00ac0fec
// @ref ?unknown_shape_ac1044@@3PAUShapeFileStruct@@A=00ac1044
// @ref ?unknown_shape_ac10d8@@3PAUShapeFileStruct@@A=00ac10d8
// @ref ?unknown_shape_ac1060@@3PAUShapeFileStruct@@A=00ac1060
// @ref ?unknown_rect_ac11c0@@3PAVRect@@A=00ac11c0
// @ref ?unknown_rect_ac11c4@@3PAVRect@@A=00ac11c4
// @ref ?unknown_rect_ac11bc@@3PAVRect@@A=00ac11bc
// @ref ?unknown_rect_ac11c8@@3PAVRect@@A=00ac11c8
// @ref ?unknown_rect_ac11b4@@3PAVRect@@A=00ac11b4
// @ref ?unknown_rect_ac11b8@@3PAVRect@@A=00ac11b8
// @ref ?unknown_rect_ac11cc@@3PAVRect@@A=00ac11cc
// @ref ?unknown_rect_ac11d0@@3PAVRect@@A=00ac11d0
// @ref ?unknown_count_ac102c@@3HA=00ac102c
#define SHAPE_FILE_EMPTY_RECT Rect(0, 0, 0, 0)
#include "shared/shape_file.hpp"

extern ShapeFileStruct *unknown_shape_ac1128;    // MNSCRNS.SHP
extern ShapeFileStruct *unknown_shape_ac1010;    // MNSCRNL.SHP
extern ShapeFileStruct *unknown_shape_ac10e8;    // SDTP.SHP
extern ShapeFileStruct *unknown_shape_ac10b4;    // SDWRNTMP.SHP
extern ShapeFileStruct *unknown_shape_ac107c;    // SDBTNBKGD.SHP
extern ShapeFileStruct *unknown_shape_ac10b8;    // SDBTNANM.SHP
extern ShapeFileStruct *unknown_shape_ac0fec;    // SDMPBTN.SHP
extern ShapeFileStruct *unknown_shape_ac1044;    // SDBTM.SHP
extern ShapeFileStruct *unknown_shape_ac10d8;    // LWSCRNS.SHP
extern ShapeFileStruct *unknown_shape_ac1060;    // LWSCRNL.SHP
extern Rect *unknown_rect_ac11c0;
extern Rect *unknown_rect_ac11c4;
extern Rect *unknown_rect_ac11bc;
extern Rect *unknown_rect_ac11c8;
extern Rect *unknown_rect_ac11b4;
extern Rect *unknown_rect_ac11b8;
extern Rect *unknown_rect_ac11cc;
extern Rect *unknown_rect_ac11d0;
extern int unknown_count_ac102c;

void __fastcall Unknown_Layout_Interface_006F3E70(int width, int height)
{
    int left = 0;
    int right = width;
    if (width >= 1024) {
        left = (width - 800) / 2;
        right = width - left;
    }
    int top = 0;
    int bottom = height;
    int span = height;
    if (height >= 768) {
        top = (height - 600) / 2;
        bottom = height - top;
        span = height - top * 2;
    }
    bool small_width = width == 640;
    bool small_height = height == 480;

    int w = small_width ? unknown_shape_ac1128->Get_Width() : unknown_shape_ac1010->Get_Width();
    int h = small_height ? unknown_shape_ac1128->Get_Height() : unknown_shape_ac1010->Get_Height();
    unknown_rect_ac11c0 = new Rect(left, top, w, h);

    int tw = unknown_shape_ac10e8->Get_Width();
    int th = unknown_shape_ac10e8->Get_Height();
    int x = right - tw;
    unknown_rect_ac11c4 = new Rect(x, top, tw, th);

    int wh = unknown_shape_ac10b4->Get_Height();
    unknown_rect_ac11bc = new Rect(x, top, tw, wh);

    int by = unknown_rect_ac11c4->Height + top;
    int bh = unknown_shape_ac107c->Get_Height();
    unknown_rect_ac11c8 = new Rect(x, by, tw, bh);

    int aw = unknown_shape_ac10b8->Get_Width();
    int ah = unknown_shape_ac10b8->Get_Height();
    int ax = unknown_rect_ac11c8->Width - aw + unknown_rect_ac11c8->X;
    int ay = unknown_rect_ac11c8->Y;
    unknown_rect_ac11b4 = new Rect(ax, ay, aw, ah);

    int mw = unknown_shape_ac0fec->Get_Width();
    int mh = unknown_shape_ac0fec->Get_Height();
    int my = unknown_rect_ac11c8->Height + unknown_rect_ac11c8->Y - mh;
    unknown_rect_ac11b8 = new Rect(right - mw, my, mw, mh);

    unknown_count_ac102c = (span - unknown_rect_ac11c4->Height) / unknown_rect_ac11c8->Height;
    int offset = unknown_rect_ac11c8->Height * unknown_count_ac102c;
    int used = unknown_rect_ac11c4->Height + offset;
    int ly = unknown_rect_ac11c8->Y + offset;
    int lw = unknown_shape_ac1044->Get_Width();
    unknown_rect_ac11cc = new Rect(right - lw, ly, lw, span - used);

    int sw = small_width ? unknown_shape_ac10d8->Get_Width() : unknown_shape_ac1060->Get_Width();
    int sh = small_height ? unknown_shape_ac10d8->Get_Height() : unknown_shape_ac1060->Get_Height();
    unknown_rect_ac11d0 = new Rect(left, bottom - sh, sw, sh);
}
