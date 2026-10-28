// bool Prep_For_Blit(Surface &dest, Rect const &dcliprect, Rect &drect, Surface &source,
//                    Rect const &scliprect, Rect &srect, bool &overlapped, void *&dbuffer,
//                    void *&sbuffer) (0x007753B0)
// Clips both areas against their windows, marks a copy within one surface
// whose source starts above (or level and left of) its overlapping
// destination as overlapped (it must run backward), and locks both surfaces
// at the areas' top left corners; the destination is unlocked again when the
// source cannot be locked.
#include "shared/surface.hpp"
// @ref ?Clip_Blit_Rects@@YI_NAAVRect@@ABV1@01@Z=00775190
// @ref ??HTPoint2D@@QBE?AU0@ABU0@@Z=00435540
// @ref ?Top_Left@Rect@@QBE?AUTPoint2D@@XZ=00435560

bool __fastcall Prep_For_Blit(Surface &dest, Rect const &dcliprect, Rect &drect, Surface &source,
                              Rect const &scliprect, Rect &srect, bool &overlapped, void *&dbuffer,
                              void *&sbuffer)
{
    overlapped = false;
    dbuffer = 0;
    sbuffer = 0;
    if (drect.Is_Valid() && dcliprect.Is_Valid() && srect.Is_Valid() && scliprect.Is_Valid()
        && Clip_Blit_Rects(drect, dcliprect, srect, scliprect)) {
        overlapped = false;
        if (&source == &dest) {
            if (srect.X < drect.X + drect.Width && srect.Y < drect.Y + drect.Height
                && srect.X + srect.Width > drect.X && srect.Y + srect.Height > drect.Y
                && (srect.Y < drect.Y || (srect.Y == drect.Y && srect.X < drect.X))) {
                overlapped = true;
            }
        }
        dbuffer = dest.Lock(dcliprect.Top_Left() + drect.Top_Left());
        if (dbuffer) {
            sbuffer = source.Lock(scliprect.Top_Left() + srect.Top_Left());
            if (!sbuffer) {
                dest.Unlock();
            } else {
                return true;
            }
        }
    }
    return false;
}
