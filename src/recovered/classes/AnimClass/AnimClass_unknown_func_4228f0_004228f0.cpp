// void AnimClass::unknown_func_4228f0() (0x004228F0)
// Marks the ground under a low animation (slot 108 < 30) with the size of
// its type's first frame (30 x 30 without an image): a Scorch type leaves a
// scorch (with Crater too, only half of the time); otherwise a Crater type
// flags the cell (6) and leaves a crater (ForceBigCraters: 300, forced).
#include "shared/shape_file.hpp"
#include "shared/random.hpp"
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_00475DB0@UnknownAnimCell@@QAEXH@Z=00475db0
// @ref ?Unknown_00688460@@YIXABUCoordStruct@@HH_N@Z=00688460
// @ref ?Unknown_00688750@@YIXABUCoordStruct@@HH_N@Z=00688750
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@8@3fe08000000200000000=0079c280

void AnimClass::unknown_func_4228f0()
{
    Cell where = Coord_Cell(Center_Coord());
    UnknownAnimCell *cell = (UnknownAnimCell *)&Map[where];
    int width = 30;
    int height = 30;
    ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_slot26();
    if (shape != 0) {
        width = shape->Get_Frame_Rect(Class->unknown_268).Width;
        height = shape->Get_Frame_Rect(Class->unknown_268).Height;
    }
    if (unknown_slot108() < 30) {
        if (Class->Scorch &&
            (!Class->Crater || unknown_id_source_a3d290->Random()(0, 0x7FFFFFFE) * (1.0 / 0x7FFFFFFE) < 0.5)) {
            Unknown_00688460(Center_Coord(), width, height, false);
            return;
        }
        if (Class->Crater) {
            cell->Unknown_00475DB0(6);
            if (Class->ForceBigCraters) {
                Unknown_00688750(Center_Coord(), 300, 300, true);
                return;
            }
            Unknown_00688750(Center_Coord(), width, height, false);
        }
    }
}
