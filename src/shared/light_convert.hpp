// LightConvertClass: a ConvertClass whose remap is tinted by a light colour
// (RTTI vtable 0x007A55DC, base ConvertClass, size 0x1B4; constructor
// 0x00538860, scalar deleting destructor 0x00538F30). Field names are
// hypotheses from the constructor.
#ifndef RA2_SHARED_LIGHT_CONVERT_HPP
#define RA2_SHARED_LIGHT_CONVERT_HPP

#include "shared/convert.hpp"

class LightConvertClass : public ConvertClass {
public:
    LightConvertClass(PaletteClass const &artpalette, PaletteClass const &screenpalette, Surface *surface,
                      int red, int green, int blue, bool skip_blitters, unsigned char const *remap,
                      int unknown_shadow_count);                      // 0x00538860
    virtual ~LightConvertClass();                                     // slot 0 (??_G 0x00538F30)

    // Rebuilds the tinted tables from the colour (0x00538AA0).
    // Vtable slot 1 (0x007A55DC); Ion.cpp's lighting 0x00520B00 calls it through the vtable.
    virtual void Set_Tint(int red, int green, int blue, bool unknown4);

    PaletteClass const *ArtPalette;                                   // +0x188
    PaletteClass const *ScreenPalette;                                // +0x18C
    unsigned char const *unknown_190;                                 // +0x190 remap, default 0x007DF768
    int unknown_194;                                                  // +0x194
    int Red;                                                          // +0x198
    int Green;                                                        // +0x19C
    int Blue;                                                         // +0x1A0
    int StoredRed;                                                    // +0x1A4
    int StoredGreen;                                                  // +0x1A8
    int StoredBlue;                                                   // +0x1AC
    bool unknown_1b0;                                                 // +0x1B0
};

#endif
