// void TerrainClass::AI() (0x006E3F10)
// Animated terrain starts its animation at random (AnimationProbability per
// frame, at AnimationRate); the stage advances when the timer expires. A
// crumbling object is removed on its last frame; a tiberium spawner spreads
// tiberium (0x00478A40) at its middle frame and stops. The stage steps
// through UnknownStage::Graphic_Logic, whose timer test keeps
// CDTimerClass::Value (0x00453EB0) out of line.
#include "shared/terrain.hpp"
#include "shared/random.hpp"
#include "shared/crt_memory.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
// @ref ?AI@ObjectClass@@UAEXXZ=005d27f0
// @ref ??R?$Random2Class@@QAEHXZ=00638840
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Value@?$CDTimerClass@VFrameTimerClass@@@@QBEJXZ=00453eb0
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_map_8324e0@@3VUnknownMap8324E0@@A=008324e0
// @ref ?Unknown_00548000@UnknownMap8324E0@@QAEHABUCoordStruct@@@Z=00548000
// @ref ?Spread_Tiberium@CellClass@@QAE_N_N@Z=00478a40
// @ref __real@8@3feb8637bd05af6c6800=007a7d20

void TerrainClass::AI()
{
    ObjectClass::AI();
    if (Class->IsAnimated && Animation.Fetch_Rate() == 0) {
        double chance = abs(unknown_id_source_a3d290->Random()()) % 1000000 * 0.000001;
        if (chance < Class->AnimationProbability) {
            Animation.Set_Stage(0);
            Animation.Set_Rate(Class->AnimationRate);
        }
    }
    if (Animation.Graphic_Logic()) {
        if (unknown_b5) {
            if (Animation.Fetch_Stage() == ((ShapeFileStruct const *)Class->unknown_slot39())->FrameCount - 1) {
                unknown_slot60();
                return;
            }
        }
        if (Class->SpawnsTiberium && Class->IsAnimated) {
            if (Animation.Fetch_Stage() == ((ShapeFileStruct const *)Class->unknown_slot39())->FrameCount / 2) {
                Animation.Set_Stage(0);
                Animation.Set_Rate(0);
                CoordStruct coord = Coord;
                Map[coord].Spread_Tiberium(true);
            }
        }
    }
}
