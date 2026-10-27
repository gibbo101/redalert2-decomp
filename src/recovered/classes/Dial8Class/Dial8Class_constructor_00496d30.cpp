#include "shared/dial8.hpp"
#include "shared/techno.hpp"
// @ref ??0ControlClass@@QAE@IHHHHI_N@Z=00483430
// @ref ??_7Dial8Class@@6B@=0079e794
Dial8Class::Dial8Class(unsigned id, int x, int y, int width, int height, unsigned direction)
 : ControlClass(id, x, y, width, height, 7, true)
{
    Center.X = Width / 2 + X;
    Center.Y = Height / 2 + Y;
    Direction = direction;
    Selected = Dir_To_8(UnknownFacingDir((unsigned short)(direction << 8)));
    Previous = Selected;
    OuterPoints[0].X = Center.X;
    OuterPoints[0].Y = Center.Y - height * 8 / 2 / 10;
    OuterPoints[1].X = Center.X + width * 56 / 2 / 100;
    OuterPoints[1].Y = Center.Y - height * 56 / 2 / 100;
    OuterPoints[2].X = Center.X + width * 8 / 2 / 10;
    OuterPoints[2].Y = Center.Y;
    OuterPoints[3].X = Center.X + width * 56 / 2 / 100;
    OuterPoints[3].Y = Center.Y + height * 56 / 2 / 100;
    OuterPoints[4].X = Center.X;
    OuterPoints[4].Y = Center.Y + height * 8 / 2 / 10;
    OuterPoints[5].X = Center.X - width * 56 / 2 / 100;
    OuterPoints[5].Y = Center.Y + height * 56 / 2 / 100;
    OuterPoints[6].X = Center.X - width * 8 / 2 / 10;
    OuterPoints[6].Y = Center.Y;
    OuterPoints[7].X = Center.X - width * 56 / 2 / 100;
    OuterPoints[7].Y = Center.Y - height * 56 / 2 / 100;
    InnerPoints[0].X = Center.X;
    InnerPoints[0].Y = Center.Y - height * 6 / 2 / 10;
    InnerPoints[1].X = Center.X + width * 42 / 2 / 100;
    InnerPoints[1].Y = Center.Y - height * 42 / 2 / 100;
    InnerPoints[2].X = Center.X + width * 6 / 2 / 10;
    InnerPoints[2].Y = Center.Y;
    InnerPoints[3].X = Center.X + width * 42 / 2 / 100;
    InnerPoints[3].Y = Center.Y + height * 42 / 2 / 100;
    InnerPoints[4].X = Center.X;
    InnerPoints[4].Y = Center.Y + height * 6 / 2 / 10;
    InnerPoints[5].X = Center.X - width * 42 / 2 / 100;
    InnerPoints[5].Y = Center.Y + height * 42 / 2 / 100;
    InnerPoints[6].X = Center.X - width * 6 / 2 / 10;
    InnerPoints[6].Y = Center.Y;
    InnerPoints[7].X = Center.X - width * 42 / 2 / 100;
    InnerPoints[7].Y = Center.Y - height * 42 / 2 / 100;
}
