// void __fastcall Unknown_00422BA0(int arg1, Cell const &cell) (0x00422BA0)
// Damages the center of a cell with the rules' values (+0x1190, warhead
// +0xC60); in game mode 0 it also hands unknown_481fb0 to 0x004955D0 (30).
// Called from BulletClass's AI; arg1 is not read.
#include "shared/anim.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0047E2C0@@YIXABUCoordStruct@@HHPAVWarheadTypeClass@@H@Z=0047e2c0
// @ref ?Unknown_004955D0@@YIXPAXHP6AXXZ@Z=004955d0
// @ref ?unknown_palette_837e10@@3VPaletteClass@@A=00837e10
// @ref ?unknown_481fb0@@YAXXZ=00481fb0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

void __fastcall Unknown_00422BA0(int arg1, Cell const &cell)
{
    CoordStruct coord;
    coord.Z = 0;
    coord.X = cell.X * 256 + 128;
    coord.Y = cell.Y * 256 + 128;
    Unknown_0047E2C0(coord, Rules->unknown_1190, 0, Rules->unknown_c60, 0);
    if (unknown_game_mode_a3d298 == 0) {
        Unknown_004955D0(&unknown_palette_837e10, 30, unknown_481fb0);
    }
}
