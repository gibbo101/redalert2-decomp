// void HouseClass::Update_Color() (0x004F5400)
// The house colour (+0x55E9) from its colour scheme's palette entry, unpacked
// from the screen pixel the scheme's converter gives it (name hypothesis).
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
#include "shared/techno.hpp"
#include "shared/color_scheme.hpp"
#include "shared/convert.hpp"
#include "shared/hicolor.hpp"

void HouseClass::Update_Color()
{
    ColorScheme *scheme = ColorSchemes[ColorSchemeIndex];
    unknown_55e9 = Unpack_Hicolor_Pixel(scheme->Converter->Convert(scheme->unknown_color_0x330));
}
