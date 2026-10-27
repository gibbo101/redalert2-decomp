// void MonoClass::Pan(int columns) (0x0059E590)
// Moves the window's text one column left (positive) or right (negative) and
// blanks the column that comes free.
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90

void MonoClass::Pan(int columns)
{
    if (unknown_mono_enabled_a70f0a) {
        int x = WindowX;
        int width = WindowWidth;
        int y = WindowY;
        int height = WindowHeight;
        if (columns > 0) {
            for (int row = y; row < y + height; row++) {
                for (int column = x; column < x + width - 1; column++) {
                    Characters[column][row] = Characters[column + 1][row];
                    Attributes[column][row] = Attributes[column + 1][row];
                }
                Characters[x + width - 1][row] = ' ';
                Attributes[x + width - 1][row] = 0;
            }
        } else if (columns < 0) {
            for (int row = y; row < y + height; row++) {
                for (int column = x + width - 1; column > x; column--) {
                    Characters[column][row] = Characters[column - 1][row];
                    Attributes[column][row] = Attributes[column - 1][row];
                }
                Characters[x][row] = ' ';
                Attributes[x][row] = 0;
            }
        }
        Refresh(0, 0, 80, 25);
    }
}
