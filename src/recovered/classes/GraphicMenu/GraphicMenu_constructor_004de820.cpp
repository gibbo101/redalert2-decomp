// GraphicMenu::GraphicMenu() (0x004DE820): the default background "Title.PCX" and theme "Intro", no animation, no items.
#include "shared/graphic_menu_class.hpp"
// @ref ??0MSEngine@@QAE@XZ=005b2be0
// @ref ??0Wstring@@QAE@PBD@Z=0076d920
// @ref ??_7GraphicMenu@@6B@=007a2b3c
// @ref ??_GGraphicMenu@@UAEPAXI@Z=004def10
// @ref ??_7?$DynamicVectorClass@PAVGraphicMenuItem@@@@6B@=007a2b44
// @ref ??_C@_09KEDK@Title?4PCX?$AA@=007d9da0
// @ref ??_C@_05MDNJ@Intro?$AA@=007d9d98

GraphicMenu::GraphicMenu() :
    Background("Title.PCX"),
    Theme("Intro"),
    Anim(0)
{
}
