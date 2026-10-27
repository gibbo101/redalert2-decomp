// ColorListClass::ColorListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down) (0x0047D7C0)
// An empty colour list with the default selection style.
#include "shared/color_list.hpp"
// @ref ??0ListClass@@QAE@HHHHHIPBX0@Z=00539bf0
// @ref ??_7ColorListClass@@6B@=0079dc6c
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94

ColorListClass::ColorListClass(int id, int x, int y, int w, int h, unsigned flags, void const *up, void const *down) :
    ListClass(id, x, y, w, h, flags, up, down),
    Style(1),
    SelectColor(0)
{
}
