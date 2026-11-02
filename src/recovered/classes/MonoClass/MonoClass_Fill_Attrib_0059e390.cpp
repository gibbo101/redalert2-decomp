// void MonoClass::Fill_Attrib(int x, int y, int width, int height, int attribute) (0x0059E390)
// Sets the attribute of a block of the window's cells (window relative) and redraws the block.
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90

void MonoClass::Fill_Attrib(int x, int y, int width, int height, int attribute)
{
    if (unknown_mono_enabled_a70f0a) {
        int left = WindowX + x;
        int top = WindowY + y;
        int right = left + width;
        int bottom = top + height;
        for (int row = top; row < bottom; row++) {
            for (int column = left; column < right; column++) {
                Attributes[column][row] = attribute;
            }
        }
        Refresh(left, top, width, height);
    }
}
