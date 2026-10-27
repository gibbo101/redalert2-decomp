// void TechnoTypeClass::Load_Palette() (0x006DF620)
// Loads Palette= when named.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Load@PaletteName@@QAEPAXXZ=00603380

void TechnoTypeClass::Load_Palette()
{
    if (PaletteFile.Buffer[0]) {
        Palette = PaletteFile.Load();
    }
}
