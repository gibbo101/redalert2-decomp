// void ColorListClass::Set_Selected_Style(int style, int color) (0x0047D9C0, slot 52)
#include "shared/color_list.hpp"

void ColorListClass::Set_Selected_Style(int style, int color)
{
    Style = style;
    SelectColor = color;
}
