// @ref ?Pose_Dir_00417890@AircraftClass@@QBEIXZ=00417890
// @ref _grand_turret_frames_007acab0=007acab0
// @ref _grand_none_0084ed10=0084ed10
// @ref _grand_south_step_00851a80=00851a80
// @ref _grand_eva_nuclear_007cf87c=007cf87c
// @ref _grand_eva_iron_007cf864=007cf864
// @ref _grand_eva_weather_007cf84c=007cf84c
// @ref _grand_eva_chrono_007cf830=007cf830
// Building completion/capture initialization, complete original body 004426D0.
#include "shared/building.hpp"
#include "shared/sidebar.hpp"
#include "shared/house.hpp"
#include "shared/unit.hpp"
#include "shared/aircraft.hpp"
#include "shared/light_source.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/radar_event.hpp"
#include "shared/vox_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
extern "C" char const unknown_turret_separator_007cf730[];
extern "C" unsigned int grand_turret_frames_007acab0[32];
extern "C" Cell grand_none_0084ed10;
extern "C" Cell grand_south_step_00851a80;
extern "C" char const grand_eva_nuclear_007cf87c[];
extern "C" char const grand_eva_iron_007cf864[];
extern "C" char const grand_eva_weather_007cf84c[];
extern "C" char const grand_eva_chrono_007cf830[];
// Aircraft heading member's original 9-byte body was independently reproduced.
// No canonical rename or header migration has been applied.
void BuildingClass::unknown_slot282(bool captured)
{
    if (unknown_5b4 && !captured) return;
    if (Type->ProduceCashDelay) {
        unknown_5a0 = CDTimerClass<FrameTimerClass>(Type->ProduceCashDelay);
    }
    if (!unknown_5b4) {
        if (Type->Refinery) {
            int storage_stage = (int)unknown_294.Get_Total_Amount();
            if (storage_stage != 0) storage_stage = ((int)unknown_294.Get_Total_Amount() << 2) / Type->Storage;
            unknown_5c0 = storage_stage;
            if (storage_stage >= 3) {
                unknown_44c920(6, Health_Ratio() <= Rules->unknown_1368, false, 0);
            } else if (storage_stage >= 2) {
                unknown_44c920(5, Health_Ratio() <= Rules->unknown_1368, false, 0);
            } else if (storage_stage >= 1) {
                unknown_44c920(4, Health_Ratio() <= Rules->unknown_1368, false, 0);
            } else if (storage_stage >= 0) {
                unknown_44c920(3, Health_Ratio() <= Rules->unknown_1368, false, 0);
            }
        } else {
            unknown_44c920(17, Health_Ratio() <= Rules->unknown_1368, unknown_554.Count() > 0, 0);
            unknown_44c920(3, Health_Ratio() <= Rules->unknown_1368, unknown_554.Count() > 0, 0);
            unknown_44c920(4, Health_Ratio() <= Rules->unknown_1368, false, 0);
            unknown_44c920(5, Health_Ratio() <= Rules->unknown_1368, false, 0);
            unknown_44c920(6, Health_Ratio() <= Rules->unknown_1368, false, 0);
        }
        if (Type->OrePurifier) ++House->unknown_52cc;
        if (Type->Helipad) {
            House->unknown_218 += Type->NumberOfDocks;
            // The canonical sidebar member is reached through the actual Map base.
            Map.Unknown_0067C310(3);
        }
        if (Type->SuperWeapon != -1) {
            for (int i = 0; i < House->Supers.Count(); ++i) {
                SuperClass *super = House->Supers[i];
                if (super->Type->Type == Type->SuperWeapon) {
                    if ((super->RechargeTimer.Value() / 15) * 60 <= 4) {
                        unknown_44c920(15, Health_Ratio() <= Rules->unknown_1368, unknown_554.Count() > 0, 0);
                    } else {
                        unknown_44c920(13, Health_Ratio() <= Rules->unknown_1368, unknown_554.Count() > 0, 0);
                    }
                }
            }
        }
        if (unknown_slot232() && !Type->TurretAnimIsVoxel) {
            if (unknown_4d0 != -1) {
                int frame = unknown_4d0;
                unknown_4d0 = -1;
                Set_Turret_Animation_Frame_0043bd40(frame);
            } else {
                unknown_44c920(9, false, false, 0);
            }
            if (unknown_slot232() && unknown_454[9]) {
                unsigned int frame = grand_turret_frames_007acab0[Dir_To_32(unknown_2e0.Current())];
                AnimClass *animation = static_cast<AnimClass *>(unknown_454[9]);
                if (animation) {
                    animation->Set_Stage(frame);
                    animation->Set_Step(0);
                }
            }
        }
        if (Type->LightIntensity) {
            if (!unknown_4e8) {
                unknown_4e8 = new LightSourceClass(Center_Coord(), Type->LightVisibility,
                    Type->LightIntensity, Type->LightRedTint, Type->LightGreenTint, Type->LightBlueTint);
            }
            unknown_4e8->Activate(0);
        }
        if (Type->LaserFencePost) unknown_44e5a0(false);
        if (Type->SensorArray) unknown_slot288(grand_none_0084ed10);
        if (Type->DetectDisguise) unknown_slot290(grand_none_0084ed10);
        unknown_5ad = true;
    }
    if (Type->RevealToAll && !House->Unknown_004F52B0()) {
        if (!captured) {
            unknown_slot262(false, false, true, unknown_player_a35db4);
            CoordStruct coordinate = Coord;
            Map.Unknown_0054A550(coordinate, 0, unknown_1f4 + 3, 0);
        }
        Unknown_0063B5B0(12, Cell(Position_Coord_004f3f40()));
    }
    if (!House->Unknown_004F52B0() && unknown_int_a3d548 == 0 && unknown_game_mode_a3d298 != 0 &&
        (Type->SuperWeapon == -1 || !Supers[Type->SuperWeapon]->Type->AuxBuilding ||
         House->unknown_5460.unknown_func_491d10(Supers[Type->SuperWeapon]->Type->AuxBuilding->ArrayIndex) != 0)) {
        switch (Type->SuperWeapon) {
        case 0: Speech_Play_Name(grand_eva_nuclear_007cf87c, -1, -1); break;
        case 1: Speech_Play_Name(grand_eva_iron_007cf864, -1, -1); break;
        case 2: Speech_Play_Name(grand_eva_weather_007cf84c, -1, -1); break;
        case 3: Speech_Play_Name(grand_eva_chrono_007cf830, -1, -1); break;
        }
    }
    if (Type->WeaponsFactory && Type->Naval) {
        Cell result = Map.Unknown_005502E0(unknown_slot104(), 5, -1, 10, false, Point2D(5, 5),
            false, false, false, true, Cell(0, 0), 0);
        result = Cell(result.X + 2, result.Y + 2);
        if (result != grand_none_0084ed10) unknown_440140(&result, false);
    }
    House->unknown_144 = true;
    unknown_5b4 = true;
    House->unknown_5668 = true;
    House->unknown_5669 = true;
    if (unknown_slot32()->GapGenerator) unknown_slot235();
    if (Type->FreeUnit && unknown_a40774 == 0 && !captured && !unknown_flag_a40d13 &&
        (!House->unknown_func_4f52f0() || unknown_258 == 0 || unknown_258 > Type->Raw_Cost())) {
        Cell origin(Center_Coord());
        short south_y = (short)(origin.Y + grand_south_step_00851a80.Y);
        short south_x = (short)(origin.X + grand_south_step_00851a80.X);
        Cell cell(south_x, south_y);
        bool placed = false;
        UnitClass *unit = new UnitClass(Type->FreeUnit, House);
        if (unit) {
            if (!unit->unknown_slot53(&CoordStruct(cell), 0xC0)) {
                Cell nearby_cell = Map.Unknown_005502E0(Cell(Position_Coord_004f3f40()), 2,
                    Map.Zone(Cell(Position_Coord_004f3f40()), unit->Type->MovementZone, false),
                    unit->Type->MovementZone, false, Point2D(1, 1), true, true, false, false, Cell(0, 0), 0);
                if (nearby_cell == grand_none_0084ed10 || !unit->unknown_slot53(&CoordStruct(nearby_cell), 0xA0)) {
                    Cell new_cell = Map.Unknown_005502E0(Cell(Position_Coord_004f3f40()), 2,
                        Map.Zone(Cell(Position_Coord_004f3f40()), unit->Type->MovementZone, false),
                        unit->Type->MovementZone, false, Point2D(1, 1), false, true, false, false, Cell(0, 0), 0);
                    if (new_cell == grand_none_0084ed10 || !unit->unknown_slot53(&CoordStruct(new_cell), 0xA0)) {
                        House->Refund_Money(unit->Type->unknown_slot46(House, true));
                        delete unit;
                    } else {
                        placed = true;
                    }
                } else {
                    placed = true;
                }
            } else {
                placed = true;
            }
            if (placed) {
                unit->unknown_slot116(10, false);
                unit->unknown_slot117();
            }
        } else {
            House->Refund_Money(Type->FreeUnit->unknown_slot46(House, true));
        }
    }
    if (!Rules->unknown_142c && Type->HoverPad && !captured) {
        ++unknown_a40774;
        AircraftClass *aircraft = new AircraftClass(Rules->PadAircraft[0], House);
        if (aircraft) {
            aircraft->unknown_slot109(0);
            if (aircraft->unknown_slot53(&Center_Coord(), aircraft->Pose_Dir_00417890())) {
                aircraft->unknown_slot116(5, false);
                aircraft->unknown_slot150(2, this);
                unknown_slot150(0x18, aircraft);
            }
        }
        --unknown_a40774;
    }
}
