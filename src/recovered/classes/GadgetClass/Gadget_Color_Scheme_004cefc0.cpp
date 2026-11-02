// int Gadget_Color_Scheme() (0x004CEFC0): the index of the colour scheme the gadgets draw with
// (Westwood's GadgetClass::Get_Color_Scheme: the scheme named by CurrentColorScheme, "Grey").
#include "shared/gadget.hpp"
#include "shared/color_scheme.hpp"
// @ref ?Gadget_Scheme_Name@@3PBDB=007d83b4
// @ref ?unknown_color_scheme_663d30@@YIPAVColorScheme@@PBDH@Z=00663d30
ColorScheme *__fastcall unknown_color_scheme_663d30(char const *name, int kind);   // shared/progress_screen.hpp

int __cdecl Gadget_Color_Scheme()
{
    ColorScheme *scheme = unknown_color_scheme_663d30(Gadget_Scheme_Name, 1);
    if (scheme != 0) {
        return scheme->Index;
    }
    return 0;
}
