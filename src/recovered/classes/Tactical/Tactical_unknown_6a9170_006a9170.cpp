// void Tactical::Unknown_006A9170() (0x006A9170): after the view position
// (+0xD64) changed: the view origin +0xB0 is centred on the screen rectangle
// 0x00ABE560, projected through +0xDE4, and the visible cell rectangle +0xD80
// is derived from it. The 60 x 30 offset is converted through a Point2D whose
// members feed the two fild temporaries.
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
// @ref ?unknown_rect_abe560@@3VRect@@A=00abe560


void Tactical::Unknown_006A9170()
{
    Vector3 position;
    position.Z = 0.0f;
    int x = unknown_d64.X;
    int y = unknown_d64.Y;
    unknown_b0.X = x;
    unknown_b0.Y = y;
    unknown_b0.X = x - unknown_rect_abe560.Width / 2;
    unknown_b0.Y = y - unknown_rect_abe560.Height / 2;
    Point2D offset(unknown_b0.X - 60, unknown_b0.Y - 30);
    position.X = (float)offset.X;
    position.Y = (float)offset.Y;
    position = unknown_de4 * position;
    Point2D cell((int)position.X, (int)position.Y);
    unknown_d80.X = cell.X / 256;
    unknown_d80.Y = cell.Y / 256;
    unknown_d80.Width = unknown_rect_abe560.Width / 60 + 2;
    unknown_d80.Height = unknown_rect_abe560.Height / 15 + 4;
}
