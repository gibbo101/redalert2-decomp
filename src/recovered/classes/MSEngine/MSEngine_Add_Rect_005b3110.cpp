// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// void MSEngine::Add_Rect(Rect const &rect) (0x005B3110)
// Adopted from ra2-decomp MSEngine::Add_Update_Rect (YR 0x005D1FD0).
// Merges rect into the dirty list: the first overlapping entry is removed
// and the union added again; otherwise rect is appended while there is
// room, else the entry whose union with rect has the smallest area is
// replaced by that union.
#include "shared/ms_engine.hpp"
// @ref ?Add_Rect@MSEngine@@QAEXABVRect@@@Z=005b3110

#define MS_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MS_MAX(a, b) (((a) > (b)) ? (a) : (b))

static inline bool Overlaps(Rect const &rect1, Rect const &rect2)
{
    bool overlapping = false;
    if (rect1.X < rect2.X) {
        if (rect1.X + rect1.Width >= rect2.X) {
            overlapping = true;
        }
    } else {
        if (rect2.X + rect2.Width >= rect1.X) {
            overlapping = true;
        }
    }

    if (rect1.Y < rect2.Y) {
        if (rect1.Y + rect1.Height < rect2.Y) {
            overlapping = false;
        }
    } else {
        if (rect2.Y + rect2.Height < rect1.Y) {
            overlapping = false;
        }
    }
    return overlapping;
}

void MSEngine::Add_Rect(Rect const &rect)
{
    int index;

    if (!rect.Is_Valid()) {
        return;
    }

    for (index = 0; index < RectCount; index++) {
        Rect const &update_rect = Rects[index];
        if (Overlaps(rect, update_rect) == true) {
            int rect_right = rect.X + rect.Width;
            int rect_bottom = rect.Y + rect.Height;
            int i_rect_right = update_rect.X + update_rect.Width;
            int i_rect_bottom = update_rect.Y + update_rect.Height;

            Rect new_rect;
            new_rect.X = MS_MIN(rect.X, update_rect.X);
            new_rect.Y = MS_MIN(rect.Y, update_rect.Y);
            new_rect.Width = rect_right > i_rect_right ? rect_right - new_rect.X : i_rect_right - new_rect.X;
            new_rect.Height = rect_bottom > i_rect_bottom ? rect_bottom - new_rect.Y : i_rect_bottom - new_rect.Y;

            RectCount--;
            for (; index < RectCount; index++) {
                Rects[index] = Rects[index + 1];
            }

            Add_Rect(new_rect);
            return;
        }
    }

    if (RectCount < Rects.Length()) {
        Rects[RectCount] = rect;
        RectCount++;
        return;
    }

    unsigned min_size = 0xFFFFFFFF;
    Rect min_rect(0, 0, 0, 0);
    int min_id = 0;

    for (index = 0; index < RectCount; index++) {
        Rect const &entry = Rects[index];
        int entry_left = entry.X;
        int entry_right = entry_left + entry.Width;
        int entry_top = entry.Y;
        int entry_bottom = entry_top + entry.Height;

        int left = MS_MIN(rect.X, entry_left);
        int top = MS_MIN(rect.Y, entry_top);
        int rect_right = rect.X + rect.Width;
        int width = rect_right > entry_right ? rect_right - left : entry_right - left;
        int bottom = MS_MAX(rect.Y + rect.Height, entry_bottom);
        unsigned area = width * (bottom - top);

        if (area < min_size) {
            min_size = area;
            min_id = index;
            min_rect.Set(left, top, width, bottom - top);
        }
    }

    Rects[min_id] = min_rect;
}
