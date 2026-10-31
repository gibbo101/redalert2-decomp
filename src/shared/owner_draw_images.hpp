// The owner-drawn dialog image preload (ownrdraw.cpp 0x005FC8A0). Kept out of pcx_cache.hpp and
// owner_draw_dialog_control.hpp: new declarations there renumber the labels of the fragile row 0x0073FEE0.
#ifndef RA2_SHARED_OWNER_DRAW_IMAGES_HPP
#define RA2_SHARED_OWNER_DRAW_IMAGES_HPP

// The owner-drawn dialog background image name, "dbak6440.pcx" (0x007E8D1C).
extern char const *unknown_dialog_background_7e8d1c;

namespace OwnerDraw {
// Loads the owner-drawn dialog and control images into the PCX image cache (0x005FC8A0).
void __fastcall Load_Dialog_Images_5fc8a0();
}

#endif
