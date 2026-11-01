// void VoxelAnimClass::AI() (0x0070D380, slot 23)
// One step of a voxel animation: keeps its start sound at the animation,
// counts its time down and, while it lasts, leaves trailer animations and
// moves the bounce state (a bounce damages what is in the cell); when the
// time runs out it splashes in water or leaves its expire animation and
// explosion, spawns its follow-up voxel animations (meteors) and ore, and
// removes itself.
#include "shared/voxel_anim.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/overlay.hpp"
#include "shared/overlay_type.hpp"
#include "shared/tiberium.hpp"
#include "shared/terrain.hpp"
#include "shared/sound_play.hpp"
#include "shared/cd_timer.hpp"
#include "shared/unknown_geometry.hpp"

// @ref ?Unknown_0047F600@@YIXUCoordStruct@@HPAVWarheadTypeClass@@HH@Z=0047f600
// @ref ?unknown_478ba0@CellClass@@QAE_N_N@Z=00478ba0
// @ref __real@8@3ff99da7b584ce88b000=007ae5f8

void VoxelAnimClass::AI()
{
    if (Class->StartSound != -1) {
        Voc_Update_At(Center_Coord(), &unknown_fc);
    }
    if (unknown_f8) {
        unknown_slot60();
        return;
    }
    if (unknown_128 != 0) {
        unknown_128--;
    }
    if (unknown_128 <= 0) {
        bool water = Map[CoordStruct(Coord)].unknown_ec == 2;
        bool bridge = CoordStruct(Coord).Z >= Map.Unknown_0055A280(CoordStruct(Coord)) + unknown_geometry_j;
        if (water && !bridge) {
            if (Class->IsMeteor) {
                new AnimClass(Rules->SplashList[Rules->SplashList.Count() - 1], Coord + CoordStruct(0, 0, 5), 0, 1, 0x600, 0);
            } else {
                new AnimClass(Rules->unknown_09c, CoordStruct(Coord), 0, 1, 0x600, 0);
                new AnimClass(Rules->SplashList[0], Coord + CoordStruct(0, 0, 10), 0, 1, 0x600, 0);
            }
        } else if (Class->ExpireAnim != 0) {
            new AnimClass(Class->ExpireAnim,
                CoordStruct((int)BounceClass::unknown_00.Position.X, (int)BounceClass::unknown_00.Position.Y, (int)BounceClass::unknown_00.Position.Z),
                0, 1, 0x2600, -30);
            Unknown_0047E2C0(BounceClass::Coord(), Class->Damage, 0, Class->Warhead, 1);
            Unknown_0047F600(BounceClass::Coord(), Class->Damage, Class->Warhead, 0, 0);
        }
        if (!water || bridge) {
            Rect dirty(0, 0, 0, 0);
            if (Class->IsMeteor) {
                CoordStruct center = BounceClass::Coord();
                if (Class->Spawns != 0 && Class->SpawnCount > 0) {
                    int count = Random_Pick(0, Class->SpawnCount) + Random_Pick(0, Class->SpawnCount);
                    for (int index = 0; index < count; index++) {
                        new VoxelAnimClass(Class->Spawns, center, 0);
                    }
                }
                if (Class->IsTiberium && !bridge) {
                    for (int facing = 0; facing < 8; facing++) {
                        CellClass &cell = Map[Adjacent_Cell(Coord_Cell(center), facing)];
                        if (cell.unknown_478ba0(false)) {
                            TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[OverlayClass::To_Tiberium(0x7F)];
                            if (cell.unknown_11c != 0) {
                                new OverlayClass(OverlayTypes[tiberium->Image->ArrayIndex + cell.unknown_11c * 2 + tiberium->NumFrames + Random_Pick(0, 1) - 2], Cell(cell.MapCoords), -1);
                            } else {
                                new OverlayClass(OverlayTypes[tiberium->Image->ArrayIndex + Random_Pick(0, 11)], Cell(cell.MapCoords), -1);
                            }
                            tiberium->Add_Growth_Cell(cell.MapCoords);
                            cell.OverlayData = 0;
                            Rect rect = cell.unknown_474eb0();
                            rect.Y -= unknown_int_839634;
                            dirty = Union(dirty, rect);
                            Map.Unknown_00631570(cell.MapCoords);
                        }
                    }
                    unknown_tactical_83996c->Register_Dirty_Area(dirty, 0);
                }
            } else if (Class->IsTiberium && !bridge) {
                CellClass &cell = Map[BounceClass::Coord()];
                if (cell.unknown_478ba0(false)) {
                    TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[OverlayClass::To_Tiberium(0x7F)];
                    if (cell.unknown_11c != 0) {
                        new OverlayClass(OverlayTypes[tiberium->Image->ArrayIndex + cell.unknown_11c * 2 + tiberium->NumFrames + Random_Pick(0, 1) - 2], Cell(cell.MapCoords), -1);
                    } else {
                        new OverlayClass(OverlayTypes[tiberium->Image->ArrayIndex + Random_Pick(0, 11)], Cell(cell.MapCoords), -1);
                    }
                    tiberium->Add_Growth_Cell(cell.MapCoords);
                    cell.OverlayData = 0;
                    dirty = cell.unknown_474eb0();
                    Map.Unknown_00631570(cell.MapCoords);
                }
            }
        }
        unknown_slot60();
        return;
    }
    if (Class->TrailerAnim != 0 && Frame % 2 == 0) {
        new AnimClass(Class->TrailerAnim,
            CoordStruct((int)BounceClass::unknown_00.Position.X, (int)BounceClass::unknown_00.Position.Y,
                        (int)(BounceClass::unknown_00.Position.Z * unknown_geometry_diagonal * 0.019245008972988385 + 0.5)),
            1, 1, 0x600, 0);
    }
    int result = BounceClass::unknown_00.Unknown_004370E0();
    if (Class->IsMeteor) {
        BounceClass::unknown_00.unknown_2c += BounceClass::unknown_00.unknown_08;
    }
    switch (result) {
        case 1:
            if (Map[CoordStruct(Coord)].unknown_ec == 2) {
                unknown_128 = 0;
            } else {
                if (Class->BounceAnim != 0) {
                    new AnimClass(Class->BounceAnim, CoordStruct(Coord), 0, 1, 0x600, 0);
                }
                for (ObjectClass *object = Map[BounceClass::Coord()].OccupierPtr; object; object = object->unknown_30) {
                    CoordStruct delta = BounceClass::Coord() - CoordStruct(object->Coord);
                    int distance = abs(delta.Y) + abs(delta.X);
                    if (distance <= Class->DamageRadius) {
                        object->unknown_slot86(&Class->Damage, Unknown_006A2970(distance), Class->Warhead, 0, 0, 0);
                    }
                }
            }
            break;
        case 2:
            unknown_128 = 0;
            break;
    }
    unknown_slot103(BounceClass::Coord());
}
