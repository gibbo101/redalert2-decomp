// TacticalProjection::TacticalProjection(int x, int y) (0x006A2740): the screen
// offset of a lepton offset through 0x006A6800, built in a Point2D first.
#include "shared/tactical.hpp"

TacticalProjection::TacticalProjection(int x, int y)
{
    Point2D pixel;
    Unknown_006A6800(x, y, &pixel.X, &pixel.Y);
    X = pixel.X;
    Y = pixel.Y;
}
