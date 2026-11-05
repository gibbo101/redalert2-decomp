// PaletteName: a palette file name (Palette=) and its loader (TechnoTypeClass,
// AnimClass +0xC4).
#ifndef RA2_SHARED_PALETTE_NAME_HPP
#define RA2_SHARED_PALETTE_NAME_HPP

// The palette file name (Palette=) and its loader (0x00603380).
struct PaletteName {
    // The constructor clears Buffer[0] in its body (0x006DA565).
    PaletteName() {}
    void *__fastcall Load();                       // 0x00603380 (name hypothesis)
    char Buffer[32];
};

// The number of extra building palettes loaded so far (0x00603D50; it
// creates the palette list on first use; hypothesis). TechnoTypeClass::
// Read_INI allows one.
int Unknown_00603D50();

#endif
