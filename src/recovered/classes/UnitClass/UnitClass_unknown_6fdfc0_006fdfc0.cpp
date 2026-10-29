// bool UnitClass::unknown_6fdfc0() (0x006FDFC0; hypothesis: Try_To_Deploy).
// A unit with a DeploysInto type (slot 186 permitting, not moving) tests
// the building's footprint at its cell (one cell north-west unless
// 0x0045EC50 says the type deploys in place). A blocked site plays
// EVA_CannotDeployHere for the player. A clear site first turns the unit to
// the type's deploy facing (0x0045EC90), then replaces it with a new
// building: attackers of the unit retarget the building (a construction
// yard is not retargeted by vehicle thieves), veterancy, health ratio,
// selection and tag carry over, and for a construction yard in a
// multiplayer game a house without 0x004F52F0 moves its base center and
// plan there. Returns true while deploying.
// Names are hypotheses.
#include "shared/unit.hpp"
#include "shared/building_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/tag.hpp"
#include "shared/vox_class.hpp"
#include "shared/sound_play.hpp"
#include "shared/adjacent_cell.hpp"
// @ref ??_C@_0BF@JPJL@EVA_CannotDeployHere?$AA@=007d5ddc
// @ref ?Unknown_004EF5A0@HouseClass@@QAEXXZ=004ef5a0
// @ref ?Unknown_004F6310@HouseClass@@QAEXXZ=004f6310
// @ref ?unknown_func_45ec50@BuildingTypeClass@@QBE_NXZ=0045ec50

bool UnitClass::unknown_6fdfc0()
{
    if (unknown_slot186()) {
        if (unknown_494) return false;
        if (Locomotor.Checked()->Is_Moving()) return false;
        if (Type->DeploysInto == 0) return false;
        unknown_slot71(0);
        Locomotor.Checked()->Mark_All_Occupation_Bits(0);
        Cell cell = unknown_slot104();
        Cell origin;
        if (Type->DeploysInto->unknown_func_45ec50()) {
            origin = cell;
        } else {
            origin = cell + AdjacentCell[7];
        }
        if (!Type->DeploysInto->unknown_slot42(origin, 0)) {
            if (House->Unknown_004F52B0()) Speech_Play_Name("EVA_CannotDeployHere", -1, -1);
            if (!House->Unknown_004F52F0()) Type->DeploysInto->unknown_458b10(origin, House);
            Locomotor.Checked()->Mark_All_Occupation_Bits(1);
            unknown_slot71(1);
        } else {
            Locomotor.Checked()->Mark_All_Occupation_Bits(1);
            unknown_slot71(1);
            int facing = Type->DeploysInto->unknown_func_45ec90();
            if (Dir_To_256(unknown_2e0.Current()) != facing) {
                if (!Locomotor.Checked()->Is_Moving_Now()) {
                    Locomotor.Checked()->Do_Turn(UnknownFacingDir((unsigned short)(facing << 8)));
                }
                unknown_slot149(3);
                unknown_57c = true;
                return true;
            }
            bool selected = unknown_77;
            unknown_slot71(0);
            Locomotor.Checked()->Mark_All_Occupation_Bits(0);
            BuildingClass *building = new BuildingClass(Type->DeploysInto, House);
            if (building) {
                building->unknown_slot116(18, false);
                if (building->unknown_slot53(&CoordStruct(origin.X * 256 + 128, origin.Y * 256 + 128, 0), 0)) {
                    unknown_slot149(3);
                    for (int index = 0; index < Technos.Count(); index++) {
                        TechnoClass *techno = Technos[index];
                        if (techno->unknown_228 && techno->unknown_228->Kind_Of() == 1 &&
                            techno->unknown_228 == this && techno->unknown_7d &&
                            techno != this && techno != building) {
                            if (building->Type->ConstructionYard && techno->Kind_Of() == 15 &&
                                ((InfantryTypeClass *)techno->unknown_slot32())->VehicleThief) {
                                techno->unknown_slot220(0);
                            } else {
                                techno->unknown_slot220(building);
                            }
                        }
                    }
                    building->unknown_114 = unknown_114;
                    building->unknown_1ac = unknown_1ac;
                    building->unknown_118 = unknown_118;
                    if (building->House->Unknown_004F52B0()) {
                        Voc_Play_At(Rules->BuildingDrop, Center_Coord(), 0);
                    } else {
                        building->unknown_59a = true;
                        building->unknown_59b = true;
                    }
                    if (building->Type->Artillary || building->Type->TickTank) {
                        building->unknown_2c8.Set_Current(UnknownFacingDir(0x4000));
                    }
                    building->unknown_slot220(unknown_228);
                    building->unknown_slot96(House);
                    building->unknown_5ad = true;
                    if (!House->Unknown_004F52F0() && building->Type->ConstructionYard && unknown_game_mode_a3d298) {
                        CoordStruct position = building->Coord;
                        Cell base = Coord_Cell(position);
                        House->BaseCenter = Cell_Center(base);
                        House->Unknown_004EF5A0();
                        House->unknown_55f0.Nodes[0].Cell = base;
                        House->unknown_55f0.unknown_50 = base;
                        House->unknown_136 = true;
                        House->unknown_13a = true;
                        House->unknown_13b = true;
                        House->Unknown_004F6310();
                    }
                    building->Strength = (int)(Health_Ratio() * building->Type->MaxStrength);
                    building->Strength = building->Strength > 1 ? building->Strength : 1;
                    building->unknown_70 = building->Strength;
                    if (selected) building->unknown_slot80();
                    unknown_slot210();
                    if (unknown_34) {
                        building->Attach_Tag(unknown_34);
                        unknown_34->unknown_2c--;
                        unknown_34 = 0;
                    }
                    unknown_slot60();
                    return true;
                }
                delete building;
            }
            Locomotor.Checked()->Mark_All_Occupation_Bits(1);
            unknown_slot71(1);
        }
    }
    unknown_57c = false;
    return false;
}
