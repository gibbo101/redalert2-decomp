// GraphicMenuItem::~GraphicMenuItem() -- 0x004E0140
// Deletes the item's sound entry (MSSfxEntry::~MSSfxEntry 0x005B16C0).
#include "shared/graphic_menu.hpp"
// @ref ??1MSSfxEntry@@QAE@XZ=005b16c0
// @ref ??3@YAXPAX@Z=00781d3b

GraphicMenuItem::~GraphicMenuItem()
{
    delete Sound;
}
