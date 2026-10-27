// bool __fastcall Clip_Blit_Rects(Rect &toarea, Rect const &towindow, Rect &fromarea, Rect const &fromwindow) (0x00775190)
// Clips a destination and a source area against their windows. Equal-sized
// areas are trimmed together so they stay the same size; otherwise each is
// just intersected with its window. False when nothing is left.
#include "shared/surface.hpp"
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0

bool __fastcall Clip_Blit_Rects(Rect &toarea, Rect const &towindow, Rect &fromarea, Rect const &fromwindow)
{
    if (toarea.Width == fromarea.Width && toarea.Height == fromarea.Height) {
        if (toarea.X < 0) {
            fromarea.X -= toarea.X;
            fromarea.Width += toarea.X;
            toarea.Width += toarea.X;
            toarea.X = 0;
        }
        if (toarea.Y < 0) {
            fromarea.Y -= toarea.Y;
            fromarea.Height += toarea.Y;
            toarea.Height += toarea.Y;
            toarea.Y = 0;
        }
        int overlap = toarea.X - towindow.Width + toarea.Width;
        if (overlap > 0) {
            fromarea.Width -= overlap;
            toarea.Width -= overlap;
        }
        overlap = toarea.Height - towindow.Height + toarea.Y;
        if (overlap > 0) {
            fromarea.Height -= overlap;
            toarea.Height -= overlap;
        }

        if (fromarea.X < 0) {
            toarea.X -= fromarea.X;
            fromarea.Width += fromarea.X;
            toarea.Width += fromarea.X;
            fromarea.X = 0;
        }
        if (fromarea.Y < 0) {
            toarea.Y -= fromarea.Y;
            fromarea.Height += fromarea.Y;
            toarea.Height += fromarea.Y;
            fromarea.Y = 0;
        }
        overlap = fromarea.Width - fromwindow.Width + fromarea.X;
        if (overlap > 0) {
            fromarea.Width -= overlap;
            toarea.Width -= overlap;
        }
        overlap = fromarea.Y - fromwindow.Height + fromarea.Height;
        if (overlap > 0) {
            fromarea.Height -= overlap;
            toarea.Height -= overlap;
        }
    } else {
        toarea = toarea.Intersect(towindow);
        fromarea = fromarea.Intersect(fromwindow);
    }
    return toarea.Is_Valid() && fromarea.Is_Valid();
}
