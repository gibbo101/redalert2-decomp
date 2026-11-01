// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
// The 256-step facing from one coordinate to another, measured from 0x20
// (the UnknownFacingDir(from, to) formula of 0x00423EF0 without its
// equal-coordinates case).
char __fastcall Unknown_00718E80(CoordStruct const &from, CoordStruct const &to)
{
    int x1 = from.X;
    int x2 = to.X;
    UnknownFacingDir dir;
    dir = UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y) - to.Y, double(x2) - x1) - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
    char facing = Dir_To_256(dir);
    facing = 0x20 - facing;
    return facing;
}
