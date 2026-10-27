// void GScreenClass::AI(int &input, Point2D const &xy) (0x004E10C0, slot 10)
// Damps the screen shake every other frame: each offset swaps sign and
// moves one step toward zero.
#include "shared/gscreen.hpp"
#include "shared/cd_timer.hpp"
// @ref ?Frame@@3HA=00a40d2c

void GScreenClass::AI(int &input, Point2D const &xy)
{
    if (!(Frame & 1)) {
        if (ShakeX < 0) {
            ShakeX = -1 - ShakeX;
        } else if (ShakeX > 0) {
            ShakeX = 1 - ShakeX;
        }
        if (ShakeY < 0) {
            ShakeY = -1 - ShakeY;
        } else if (ShakeY > 0) {
            ShakeY = 1 - ShakeY;
        }
    }
}
