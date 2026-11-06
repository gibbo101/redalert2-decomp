// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// 

// void SpotLightClass::unknown_func_5ddb90() (0x005DDB90; TibSun ovrlight.cpp Draw_It):
// lights, darkens or tints the pixels under the spot light through the type's falloff
// surface for the light's current radius; the plain light uses the asm blitters.
// From ra2-decomp SpotLightClass::Draw_It (YR 0x005FF850), adapted to our names.
// @ref _SpotLight_Index_Table=007e8c50
// @ref _SpotLight_Color_Mode=007e8c4c
// @ref _SpotLight_MMX_Buffer=00a73378
// @ref _SpotLight_Surfaces=00a731e0
// @ref _Brighten_Color_555=007983d1
// @ref _Brighten_Color_556=007982f4
// @ref _Brighten_Color_565=0079813a
// @ref _Brighten_Color_655=00798217
// @ref _MMX_Brighten_Color_555=00798602
// @ref _MMX_Brighten_Color_556=00798740
// @ref _MMX_Brighten_Color_565=007984c0
// @ref _MMX_Brighten_Color_655=00798880
// @ref ?Unknown_0053D840@@YAIXZ=0053d840
// @ref ?unknown_a6eb1c@@3IA=00a6eb1c
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_rect_839630@@3URect@@A=00839630
#include "shared/spot_light.hpp"
#include "shared/combat.hpp"
#include "shared/frame_rate.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/surface.hpp"
#include "shared/blit.hpp"
#include "shared/tactical.hpp"
#include "shared/hicolor.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"
extern Rect unknown_rect_839630;        // 0x00839630 tactical X, Y, width, height
extern "C" char SpotLight_Index_Table[];        // 0x007E8C50
extern "C" int SpotLight_Color_Mode;            // 0x007E8C4C
extern "C" void *SpotLight_MMX_Buffer;          // 0x00A73378
extern "C" Surface *SpotLight_Surfaces[];       // 0x00A731E0
extern "C" void __cdecl Brighten_Color_555(void *sptr, void *dptr, int spitch, int dpitch, int width, int height);       // 0x007983D1
extern "C" void __cdecl Brighten_Color_556(void *sptr, void *dptr, int spitch, int dpitch, int width, int height);       // 0x007982F4
extern "C" void __cdecl Brighten_Color_565(void *sptr, void *dptr, int spitch, int dpitch, int width, int height);       // 0x0079813A
extern "C" void __cdecl Brighten_Color_655(void *sptr, void *dptr, int spitch, int dpitch, int width, int height);       // 0x00798217
extern "C" void __cdecl MMX_Brighten_Color_555(void *sptr, void *dptr, int spitch, int dpitch, int width, int height, void *buffer);   // 0x00798602
extern "C" void __cdecl MMX_Brighten_Color_556(void *sptr, void *dptr, int spitch, int dpitch, int width, int height, void *buffer);   // 0x00798740
extern "C" void __cdecl MMX_Brighten_Color_565(void *sptr, void *dptr, int spitch, int dpitch, int width, int height, void *buffer);   // 0x007984C0
extern "C" void __cdecl MMX_Brighten_Color_655(void *sptr, void *dptr, int spitch, int dpitch, int width, int height, void *buffer);   // 0x00798880

#define SL_MIN(a, b) ((a) < (b) ? (a) : (b))

void SpotLightClass::unknown_func_5ddb90()
{
    unsigned int flags = unknown_14 & 0xF;
    if ((flags & ~1) == 0) {
        if (unknown_a6eb1c < Unknown_0053D840()) {
            return;
        }
    }

    Point2D drawpoint;
    if (unknown_tactical_83996c->Coord_To_Pixel(Coord, drawpoint)) {
        if (!(unknown_id_source_a3d290->unknown_000 & 0x1000) || !Map.Unknown_005683C0(Coord)) {
            Surface *dsurf = unknown_surface_83995c;
            Rect drect(drawpoint.X - 128, drawpoint.Y - 64, 255, 127);
            Rect dcliprect = unknown_rect_839630;
            int index = SpotLight_Index_Table[unknown_0c];
            if (index < 64) {
                index = index * unknown_10 / 64;
            }
            Surface *ssurf = SpotLight_Surfaces[index];
            int stride = dsurf->Stride();
            bool overlapped = false;
            Rect srect(0, 0, 255, 127);
            Rect scliprect(0, 0, 255, 127);
            void *dbuffer;
            void *sbuffer;
            if (Prep_For_Blit(*dsurf, dcliprect, drect, *ssurf, scliprect, srect, overlapped, dbuffer, sbuffer)) {

                unsigned short *dptr_row = (unsigned short *)dbuffer;
                unsigned char *sptr_row = (unsigned char *)sbuffer;
                unsigned short *dptr = dptr_row;
                unsigned char *sptr = sptr_row;
                unsigned char spixel;
                RGBClass rgb;

                int colormode = SpotLight_Color_Mode;
                if (flags == 0 && (unsigned)colormode <= 3) {
                    switch (colormode) {
                    case 0:
                        if (SpotLight_MMX_Buffer) {
                            MMX_Brighten_Color_555(sptr, dptr, 256, stride, srect.Width, srect.Height, SpotLight_MMX_Buffer);
                        } else {
                            Brighten_Color_555(sptr, dptr, 256, stride, srect.Width, srect.Height);
                        }
                        break;
                    case 1:
                        if (SpotLight_MMX_Buffer) {
                            MMX_Brighten_Color_556(sptr, dptr, 256, stride, srect.Width, srect.Height, SpotLight_MMX_Buffer);
                        } else {
                            Brighten_Color_556(sptr, dptr, 256, stride, srect.Width, srect.Height);
                        }
                        break;
                    case 2:
                        if (SpotLight_MMX_Buffer) {
                            MMX_Brighten_Color_565(sptr, dptr, 256, stride, srect.Width, srect.Height, SpotLight_MMX_Buffer);
                        } else {
                            Brighten_Color_565(sptr, dptr, 256, stride, srect.Width, srect.Height);
                        }
                        break;
                    case 3:
                        if (SpotLight_MMX_Buffer) {
                            MMX_Brighten_Color_655(sptr, dptr, 256, stride, srect.Width, srect.Height, SpotLight_MMX_Buffer);
                        } else {
                            Brighten_Color_655(sptr, dptr, 256, stride, srect.Width, srect.Height);
                        }
                        break;
                    default:
                        goto fallback;
                    }
                } else {
                    fallback:
                    if (unknown_14 & 1) {
                        for (int y = 0; y < srect.Height; y++) {
                            for (int x = 0; x < srect.Width; x++) {
                                spixel = *sptr++;
                                if (spixel != 0) {
                                    int scale = 256 - spixel;
                                    rgb = Deconstruct_Hicolor_Pixel(*dptr);
                                    *dptr = Build_Hicolor_Pixel((rgb.Red * scale) >> 8, (rgb.Green * scale) >> 8, (rgb.Blue * scale) >> 8);
                                }
                                dptr++;
                            }
                            dptr_row = (unsigned short *)((unsigned char *)dptr_row + stride);
                            dptr = dptr_row;
                            sptr_row += 256;
                            sptr = sptr_row;
                        }
                    } else if (unknown_14 & 0xE) {
                        for (int x = 0; x < srect.Height; x++) {
                            for (int y = 0; y < srect.Width; y++) {
                                spixel = *sptr++;
                                if (spixel != 0) {
                                    rgb = Deconstruct_Hicolor_Pixel(*dptr);
                                    int scale = spixel + 256;
                                    int rr = rgb.Red;
                                    int gg = rgb.Green;
                                    int bb = rgb.Blue;
                                    if (!(unknown_14 & 2)) {
                                        rr = (rr * scale) >> 8;
                                        if (rr > 255) rr = 255;
                                    }
                                    if (!(unknown_14 & 4)) {
                                        gg = (gg * scale) >> 8;
                                        if (gg > 255) gg = 255;
                                    }
                                    if (!(unknown_14 & 8)) {
                                        bb = (bb * scale) >> 8;
                                        if (bb > 255) bb = 255;
                                    }
                                    *dptr = Build_Hicolor_Pixel(rr, gg, bb);
                                }
                                dptr++;
                            }
                            dptr_row = (unsigned short *)((unsigned char *)dptr_row + stride);
                            dptr = dptr_row;
                            sptr_row += 256;
                            sptr = sptr_row;
                        }
                    } else {
                        for (int x = 0; x < srect.Height; x++) {
                            for (int y = 0; y < srect.Width; y++) {
                                spixel = *sptr++;
                                if (spixel != 0) {
                                    int scale = spixel + 256;
                                    rgb = Deconstruct_Hicolor_Pixel(*dptr);
                                    int rr = (rgb.Red * scale) >> 8;
                                    int gg = (rgb.Green * scale) >> 8;
                                    int bb = (rgb.Blue * scale) >> 8;
                                    *dptr = Build_Hicolor_Pixel(SL_MIN(255, rr), SL_MIN(255, gg), SL_MIN(255, bb));
                                }
                                dptr++;
                            }
                            dptr_row = (unsigned short *)((unsigned char *)dptr_row + stride);
                            dptr = dptr_row;
                            sptr_row += 256;
                            sptr = sptr_row;
                        }
                    }
                }
                dsurf->Unlock();
                ssurf->Unlock();
            }
        }
    }
}
