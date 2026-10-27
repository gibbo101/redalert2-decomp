#pragma once

// Observed exact-target font fields; original class/API names remain unknown.
// Native service/span ownership is not part of these original-width projections.
struct FontClipRectangle {
    int left;
    int top;
    int right;
    int bottom;
};
struct FontDrawState {
    unsigned char unknown_0x00[0x1c];
    int line_height;
    unsigned char unknown_0x20[4];
    unsigned short color;
    unsigned short unknown_0x26;
    int tab_width;
    int spacing;
    FontClipRectangle clip;
    unsigned char field_0x40;
    unsigned char clipping;
    unsigned char unknown_0x42[2];

    unsigned short ExchangeFontColor_00431430(unsigned short replacement);
    unsigned char ExchangeFontClippingFlag_00431450(unsigned char replacement);
};
typedef char FontDrawState_size_check[(sizeof(FontDrawState) == 0x44) ? 1 : -1];

// Byte-triplet storage used by the actual text color child; no packing pragmas.
struct RgbTriplet {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    void BlendRgbTowardTarget_0063cf20(unsigned int factor, const RgbTriplet& target);
};
typedef char RgbTriplet_size_check[(sizeof(RgbTriplet) == 3) ? 1 : -1];
