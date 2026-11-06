// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// Rect RadarClass::Unknown_00630B70(Rect const &, Rect &, bool) (0x00630B70)
// TibSun radar.cpp RadarClass::Compute_Background: makes the background colour array (+0x1238)
// and the radar drawing surface (+0x121C) on first use, fills in the colours of update_rect,
// then box-filters the cell colours down into the surface pixels over the updated area.
// From ra2-decomp RadarClass::Compute_Background (YR 0x006547C0), adapted to our names.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??0Surface@@QAE@HH@Z=0049ed90
// @ref ??_7XSurface@@6B@=0079af8c
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ?Unknown_00631250@RadarClass@@QAEXABVRect@@0@Z=00631250
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref __ftol=0077f110
// @ref __real@4@40068c00000000000000=007a87f8
// @ref __real@4@4005d800000000000000=007a87f4
#include "shared/radar.hpp"
#include "shared/surface.hpp"
#include "shared/hicolor.hpp"
#include "shared/crt_memory.hpp"
#include "shared/always.hpp"

#define RB_MIN(a, b) ((a) < (b) ? (a) : (b))

// The surface pixel span of a cell rectangle at scale, each far edge one past and clipped to the surface.
static inline void Radar_Pixel_Bounds(Rect const &rect, float scale, int width, int height, int &left, int &right, int &top, int &bottom)
{
    left = (int)(rect.X * scale);
    right = RB_MIN((int)((rect.X + rect.Width) * scale) + 1, width);
    top = (int)(rect.Y * scale);
    bottom = RB_MIN((int)((rect.Y + rect.Height) * scale) + 1, height);
}

Rect RadarClass::Unknown_00630B70(Rect const &cell_rect, Rect &update_rect, bool fill_in)
{
    if (fill_in && !update_rect.Is_Valid()) {
        update_rect = cell_rect;
    }

    if (BackgroundColors == 0) {
        BackgroundColors = new RGBClass[cell_rect.Height * cell_rect.Width];
        memset(BackgroundColors, 0, cell_rect.Height * cell_rect.Width * sizeof(RGBClass));
        RadarCellWidth = cell_rect.Width;
        RadarCellHeight = cell_rect.Height;
    }

    if (fill_in) {
        Unknown_00631250(cell_rect, update_rect);
    }

    int rect1_width = cell_rect.Width;
    float zoom_scale = unknown_1484;
    int surface_width;
    int surface_height;

    if (unknown_121c == 0) {
        zoom_scale = 140 / (float)rect1_width;
        float scaled_height = cell_rect.Height * zoom_scale;
        if (scaled_height < 108) {
            surface_width = 140;
            surface_height = scaled_height;
        } else {
            zoom_scale = 108 / (float)cell_rect.Height;
            float scaled_width = rect1_width * zoom_scale;
            surface_width = scaled_width;
            surface_height = 108;
        }
        unknown_1484 = zoom_scale;

        unknown_121c = new BSurface(surface_width, surface_height, 2);
        unknown_121c->Fill(0);
    } else {
        surface_width = unknown_121c->Get_Width();
        surface_height = unknown_121c->Get_Height();
    }

    float pixels_per_cell_x = (float)cell_rect.Width / (float)surface_width;
    float pixels_per_cell_y = (float)cell_rect.Height / (float)surface_height;
    float inv_area = 1.0 / (pixels_per_cell_x * pixels_per_cell_y);

    unsigned short *data = (unsigned short *)unknown_121c->Lock();

    int surf_left, surf_right, surf_top, surf_bottom;
    Radar_Pixel_Bounds(update_rect, zoom_scale, surface_width, surface_height, surf_left, surf_right, surf_top, surf_bottom);

    float src_x = surf_left / zoom_scale;
    float src_y = surf_top / zoom_scale;

    if (surf_top < surf_bottom) {

        for (int surfy = surf_top; surfy < surf_bottom; ++surfy) {

            int src_y_min = RB_MIN(RadarCellHeight, (int)src_y);
            float src_y_end = src_y + pixels_per_cell_y;
            int src_y_max = RB_MIN(RadarCellHeight, (int)src_y_end + 1);

            if (surf_left < surf_right) {

                unsigned short *pixel_data = data + surf_left + surface_width * surfy;

                for (int surfx = surf_left; surfx < surf_right; ++surfx) {

                    float accum_r = 0.0f;
                    float accum_g = 0.0f;
                    float accum_b = 0.0f;

                    int src_x_min = RB_MIN(RadarCellWidth, (int)src_x);
                    float src_x_end = src_x + pixels_per_cell_x;
                    int src_x_max = RB_MIN(RadarCellWidth, (int)src_x_end + 1);

                    for (int srcy = src_y_min; srcy < src_y_max; ++srcy) {

                        float y_weight;
                        if (src_y_max - src_y_min <= 1) {
                            y_weight = pixels_per_cell_y;
                        } else if (srcy == src_y_min) {
                            y_weight = (float)(srcy + 1) - src_y;
                        } else if (srcy == src_y_max - 1) {
                            y_weight = src_y_end - (float)srcy;
                        } else {
                            y_weight = 1.0f;
                        }

                        int idx = src_x_min + srcy * rect1_width;

                        for (int srcx = src_x_min; srcx < src_x_max; ++srcx, ++idx) {

                            float x_weight;
                            if (src_x_max - src_x_min <= 1) {
                                x_weight = pixels_per_cell_x;
                            } else if (srcx == src_x_min) {
                                x_weight = (float)(srcx + 1) - src_x;
                            } else if (srcx == src_x_max - 1) {
                                x_weight = src_x_end - (float)srcx;
                            } else {
                                x_weight = 1.0f;
                            }

                            float weight = x_weight * y_weight * inv_area;

                            if (idx < RadarCellHeight * RadarCellWidth) {
                                RGBClass &color = BackgroundColors[idx];
                                accum_r += (float)color.Get_Red() * weight;
                                accum_g += (float)color.Get_Green() * weight;
                                accum_b += (float)color.Get_Blue() * weight;
                            }
                        }
                    }

                    *pixel_data++ = Build_Hicolor_Pixel(RB_MIN(255, (int)(accum_r + 0.5)), RB_MIN(255, (int)(accum_g + 0.5)), RB_MIN(255, (int)(accum_b + 0.5)));
                    src_x = src_x_end;
                }
            }

            src_x = surf_left / zoom_scale;
            src_y = src_y_end;
        }
    }

    unknown_121c->Unlock();

    int pixel_count = (surface_width * surface_height) / 8 + 1;
    if (unknown_1270 == 0) {
        unknown_1270 = new unsigned char[pixel_count];
        memset(unknown_1270, 0, pixel_count);
    }

    Rect result(surf_left, surf_top, surf_right - surf_left, surf_bottom - surf_top);
    return result;
}
