// void MSEngine::Draw(Surface *surface) (0x005B2FB0)
// After Redraw: clears the surface, centres the background on it and draws
// every animation. Then updates every animation, deleting finished ones,
// and collects the rectangles they changed.
#include "shared/ms_engine.hpp"
// @ref ?unknown_redraw_8523dc@@3_NA=008523dc
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?Add_Rect@MSEngine@@QAEXABVRect@@@Z=005b3110

void MSEngine::Draw(Surface *surface)
{
    int index;
    if (unknown_redraw_8523dc == true) {
        unknown_redraw_8523dc = false;
        surface->Fill(0);
        Rect rect = unknown_surface_839958->Get_Rect();
        rect.X = (surface->Get_Width() - rect.Width) / 2;
        rect.Y = (surface->Get_Height() - rect.Height) / 2;
        surface->Copy_From(unknown_surface_839958->Get_Rect(), *unknown_surface_839958, rect, false, true);
        for (index = 0; index < Anims.Count(); index++) {
            Anims[index]->Draw(surface, 0);
        }
        RectCount = 0;
        Add_Rect(surface->Get_Rect());
        Unknown_Slot1(surface);
    }
    for (index = 0; index < Anims.Count(); index++) {
        Rect dirty;
        if (Anims[index]->Unknown_Slot4(surface, &dirty) == true) {
            delete Anims[index];
            Anims.Delete(index);
        }
        Add_Rect(dirty);
    }
}
