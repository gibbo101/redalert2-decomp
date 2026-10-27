// void MonoClass::Scroll(int lines) (0x0059E410)
// Moves the window's text one line up (positive) or down (negative) and blanks
// the line that comes free.
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90

void MonoClass::Scroll(int lines)
{
    if (unknown_mono_enabled_a70f0a) {
        int x = WindowX;
        int y = WindowY;
        int width = WindowWidth;
        int height = WindowHeight;
        if (lines > 0) {
            for (int column = x; column < x + width; column++) {
                for (int row = y; row < y + height - 1; row++) {
                    Characters[column][row] = Characters[column][row + 1];
                    Attributes[column][row] = Attributes[column][row + 1];
                }
                Characters[column][y + height - 1] = ' ';
                Attributes[column][y + height - 1] = 0;
            }
        } else if (lines < 0) {
            for (int column = x; column < x + width; column++) {
                for (int row = y + height - 1; row > y; row--) {
                    Characters[column][row] = Characters[column][row - 1];
                    Attributes[column][row] = Attributes[column][row - 1];
                }
                Characters[column][y] = ' ';
                Attributes[column][y] = 0;
            }
        }
        Refresh(0, 0, 80, 25);
    }
}
