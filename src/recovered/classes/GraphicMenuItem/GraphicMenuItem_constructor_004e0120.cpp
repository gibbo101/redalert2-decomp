// GraphicMenuItem::GraphicMenuItem(int id) -- 0x004E0120
// A disabled, visible item without a sound.
#include "shared/graphic_menu.hpp"
// @ref ??_7GraphicMenuItem@@6B@=007a2bd0

GraphicMenuItem::GraphicMenuItem(int id) : ID(id), Enabled(false), Visible(true), Sound(0)
{
}
