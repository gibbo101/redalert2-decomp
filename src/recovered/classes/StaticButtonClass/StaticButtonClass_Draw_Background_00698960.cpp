// void StaticButtonClass::Draw_Background() (0x00698960, slot 34)
// Saves the screen area under the gadget on first use, then restores it.
#include "shared/gadget.hpp"
#include "shared/blit.hpp"

void StaticButtonClass::Draw_Background()
{
    if (!Background.Is_Valid() && Width > 0 && Height > 0) {
        new (&Background) Buffer(unknown_surface_83995c->Bytes_Per_Pixel() * Height * Width);
        if (Background.Is_Valid()) {
            To_Buffer(*unknown_surface_83995c, Rect(X, Y, Width, Height), Background);
        }
    }
    if (Background.Is_Valid()) {
        From_Buffer(*unknown_surface_83995c, Rect(X, Y, Width, Height), Background);
    }
}
