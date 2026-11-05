// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?Bucket_Index@UnknownControlIndex@OwnerDraw@@QBEIABI@Z=00602020
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_surface_count_a763d8@OwnerDraw@@3HA=00a763d8
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??_7XSurface@@6B@=0079af8c
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ?unknown_session_a3d298@@3VUnknownSessionState@@A=00a3d298
// @ref ?Unknown_00672F10@UnknownSessionState@@QAEEXZ=00672f10
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_Get_Art_006f3460@@YI_NXZ=006f3460
// @ref ?Unknown_006F3650@@YIXPAVSurface@@ABVRect@@_N@Z=006f3650
// @ref ?Unknown_006F3930@@YIXPAVSurface@@ABVRect@@PAVConvertClass@@PBUShapeFileStruct@@3@Z=006f3930
// @ref ?Unknown_6F3A60@@YIXPAVSurface@@ABVRect@@@Z=006f3a60
// @ref ?Unknown_6F3AC0@@YIXPAVSurface@@ABVRect@@@Z=006f3ac0
// @ref ?Unknown_6F3B20@@YIXPAVSurface@@ABVRect@@@Z=006f3b20
// @ref ?Unknown_6F4620@@YIXPAVSurface@@ABVRect@@_N@Z=006f4620
// @ref ?Unknown_Get_Art_6f2230@@YAPAXXZ=006f2230
// @ref ?unknown_art_ac1218@@3PAXA=00ac1218
// @ref ?unknown_art_ac121c@@3PAXA=00ac121c
// @ref ?unknown_art_ac1220@@3PAXA=00ac1220
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_bitmap_writer_a76378@@3VUnknownBitmapWriter@@A=00a76378
// @ref ?Get_Image_0068ca40@UnknownBitmapWriter@@QAEPAVSurface@@PBDH@Z=0068ca40
// @ref ?unknown_dialog_back_name_7e8d1c@OwnerDraw@@3PBDB=007e8d1c
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/palette.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/session_state.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/owner_draw_dialog_control.hpp"

bool __fastcall Unknown_Get_Art_006f3460();
void __fastcall Unknown_006F3650(Surface *surface, Rect const &window, bool arg3);
void __fastcall Unknown_006F3930(Surface *surface, Rect const &window, ConvertClass *drawer, ShapeFileStruct const *shape640,
                                 ShapeFileStruct const *shape);
void __fastcall Unknown_6F3A60(Surface *surface, Rect const &window);
void __fastcall Unknown_6F3AC0(Surface *surface, Rect const &window);
void __fastcall Unknown_6F3B20(Surface *surface, Rect const &window);
void __fastcall Unknown_6F4620(Surface *surface, Rect const &window, bool arg3);
void *Unknown_Get_Art_6f2230();
extern void *unknown_art_ac1218;
extern void *unknown_art_ac121c;
extern void *unknown_art_ac1220;

namespace OwnerDraw {

// Draws a dialog's background (TibSun OwnerDraw::Draw_Dialog_Back): built once into the record's cached
// surface (interface art, the multiplayer art shape, or the dbak6440.pcx image), then blitted to the
// background surface.
extern char const *unknown_dialog_back_name_7e8d1c;
// One more inline level over Get: at this depth Bucket_Index stays out of line (0x00602020).
static inline void Lookup(unsigned int const &key, UnknownControlRecord *&record)
{
    unknown_registry_a73640.Get(key, record);
}
void __fastcall unknown_draw_dialog_back_5fee70(HWND window)
{
    ConvertClass *drawer = 0;
    unsigned int key = (unsigned int)window;
    UnknownControlRecord *record = 0;
    Lookup(key, record);
    UnknownControlRecord *const &found = record;
    if (found) {
        RECT client;
        GetClientRect(window, &client);
        RECT screen;
        Window_Rect_In_Main_Client(window, &screen);
        Rect full;
        full.Set(screen.left, screen.top, screen.right - screen.left, screen.bottom - screen.top);
        if (full.Width <= client.right) {
            full.Width = client.right;
        }
        if (full.Height <= client.bottom) {
            full.Height = client.bottom;
        }
        if (record->unknown_20 == 0) {
            Surface *surface = record->surface_10;
            if (!surface) {
                surface = new BSurface(client.right, client.bottom, 2);
                record->surface_10 = surface;
                unknown_surface_count_a763d8++;
            }
            if (record->unknown_b0 == 1) {
                if (unknown_session_a3d298.Unknown_00672F10()) {
                    Unknown_6F4620(surface, full, false);
                } else {
                    if (Unknown_Get_Art_006f3460()) {
                        Unknown_006F3650(surface, full, !record->unknown_d4);
                        drawer = (ConvertClass *)unknown_5e9f40(window);
                        ShapeFileStruct const *shape640 = (ShapeFileStruct const *)unknown_5ea8a0(window);
                        ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_5ea900(window);
                        Unknown_006F3930(surface, full, drawer, shape640, shape);
                        if (record->unknown_d5) {
                            Unknown_6F3AC0(surface, full);
                        }
                        if (record->unknown_d6) {
                            Unknown_6F3A60(surface, full);
                        }
                        if (unknown_5ea6c0(window)) {
                            Unknown_6F3B20(surface, full);
                        }
                    }
                }
            } else if (record->unknown_b0 == 2) {
                Rect to = full;
                to.X = 0;
                to.Y = 0;
                surface->Copy_From(to, *unknown_surface_839958, full, false, true);
                void *shape;
                if (unknown_session_a3d298.Unknown_00672F10()) {
                    if (unknown_id_source_a3d290->unknown_2239) {
                        shape = unknown_art_ac121c;
                    } else {
                        shape = unknown_art_ac1220;
                    }
                } else {
                    shape = unknown_art_ac1218;
                }
                drawer = (ConvertClass *)Unknown_Get_Art_6f2230();
                CC_Draw_Shape(surface, drawer, (ShapeFileStruct const *)shape, 0,
                              Point2D(0, 0), to, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            } else {
                Surface *back = unknown_bitmap_writer_a76378.Get_Image_0068ca40(unknown_dialog_back_name_7e8d1c, 0);
                Rect to = full;
                Rect from = full;
                to.X -= screen.left;
                to.Y -= screen.top;
                int width = back->Get_Width();
                int height = back->Get_Height();
                if (unknown_8523e0 > width) {
                    from.X -= (unknown_8523e0 - width) / 2;
                }
                if (unknown_8523e4 > height) {
                    from.Y -= (unknown_8523e4 - height) / 2;
                }
                surface->Copy_From(to, *back, from, false, true);
            }
            if (surface) {
                Rect from = full;
                from.X -= screen.left;
                from.Y -= screen.top;
                unknown_surface_839958->Copy_From(full, *surface, from, false, true);
            }
        }
    }
}

}
