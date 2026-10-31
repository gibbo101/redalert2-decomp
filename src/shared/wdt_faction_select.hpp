// WorldDominationTour::FactionSelectDialogControl (RTTI vtable 0x007AF9DC; base
// OwnerDraw::SimpleDialogControl): the World Domination Tour faction picker's map
// control in WorldDom.cpp. Size 0x20 from the destructor 0x00768800 and the hit
// test 0x00768840; member names are hypotheses.
#ifndef RA2_SHARED_WDT_FACTION_SELECT_HPP
#define RA2_SHARED_WDT_FACTION_SELECT_HPP

#include "shared/owner_draw_dialog_control.hpp"

class Surface;
struct Point2D;

namespace WorldDominationTour {

class FactionSelectDialogControl : public OwnerDraw::SimpleDialogControl {
public:
    // Loads the three images (each only while still unset) and shows the first (inline in
    // WorldDom.cpp; out of line at 0x00769790).
    FactionSelectDialogControl();
    virtual ~FactionSelectDialogControl();                          // 0x00768800 (deleting 0x00769740)

    // Picks the image and selection (2 allied, 3 soviet, 0 none) under the
    // point and repaints the window when the selection changes (0x00768840).
    void Mouse_Move_00768840(HWND window, Point2D const &point);
    // Draws the current image on the background surface (0x00768940; the
    // argument is not read).
    void Draw_00768940(int unknown);

    int Selection;          // +0x0C
    Surface *NoneImage;     // +0x10 (deleted by the destructor)
    Surface *AlliedImage;   // +0x14
    Surface *SovietImage;   // +0x18
    Surface *Current;       // +0x1C
};

}

#endif
