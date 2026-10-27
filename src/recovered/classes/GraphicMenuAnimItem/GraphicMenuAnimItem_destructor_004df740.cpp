// GraphicMenuAnimItem::~GraphicMenuAnimItem() -- 0x004DF740
// Deletes the item's animation (virtual destructor), then the base part.
#include "shared/graphic_menu.hpp"
// @ref ??1GraphicMenuItem@@UAE@XZ=004e0140
// @ref ??_7GraphicMenuAnimItem@@6B@=007a2b98

GraphicMenuAnimItem::~GraphicMenuAnimItem()
{
    delete Anim;
}
