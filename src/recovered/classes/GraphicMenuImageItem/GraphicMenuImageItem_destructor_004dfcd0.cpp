// GraphicMenuImageItem::~GraphicMenuImageItem() -- 0x004DFCD0
// Deletes the hover sound entry and destroys the name; the images belong
// to the screen engine and are not deleted here.
#include "shared/graphic_menu.hpp"
// @ref ??1GraphicMenuItem@@UAE@XZ=004e0140
// @ref ??1MSSfxEntry@@QAE@XZ=005b16c0
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7GraphicMenuImageItem@@6B@=007a2bb4

GraphicMenuImageItem::~GraphicMenuImageItem()
{
    delete unknown_sound_30;
}
