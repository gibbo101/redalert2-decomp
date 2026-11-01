// Screen pixel <-> RGBClass helpers kept out of line as COMDATs (0x00432D90 after BitText.cpp; also called
// from the planning unit 0x00618C00/0x0061FC20). Names are placeholders.
#ifndef RA2_SHARED_HICOLOR_PIXEL_HPP
#define RA2_SHARED_HICOLOR_PIXEL_HPP

#include "shared/hicolor.hpp"

inline RGBClass Pixel_To_RGB(unsigned short pixel)
{
    return RGBClass((pixel >> unknown_shift_852fb8) << unknown_shift_852fbc,
                    (pixel >> unknown_shift_852fc8) << unknown_shift_852fcc,
                    (pixel >> unknown_shift_852fc0) << unknown_shift_852fc4);
}

inline int __fastcall RGB_To_Pixel(int red, int green, int blue)
{
    return ((red >> unknown_shift_852fbc) << unknown_shift_852fb8)
         | ((green >> unknown_shift_852fcc) << unknown_shift_852fc8)
         | ((blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
}

#endif
