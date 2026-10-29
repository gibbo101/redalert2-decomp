// @ref ?Unknown_0054E580@MapClass@@QAE_NVCell@@H@Z=0054e580
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@HHHH0H@Z=005502e0
// @ref ?unknown_47b7e0@CellClass@@QBE_NXZ=0047b7e0
// int UnitClass::unknown_slot86 (0x006FCA30, slot 86: the damage path; Take_Damage hypothesis).
// After FootClass's damage, a destroyed unit plays its death frames, sinks (heavy naval
// units over water), sprays particles or explodes, unloads or kills its passengers, may
// release a crew member and may drop a crate near itself (0x005502E0 with a 1x1 size);
// a damaged harvester reports the attack, flees from the attacker or returns to a dock.
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/building_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/house.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/anim.hpp"
#include "shared/particle_system.hpp"
#include "shared/tag.hpp"
#include "shared/random.hpp"
#include "shared/vox_class.hpp"
#include "shared/radar_event.hpp"
#include "shared/unknown_globals.hpp"
extern char const Unit_Ore_Miner_Under_Attack_007F819C[];
extern CoordStruct const unknown_coord_ad04c0;
extern Cell const unknown_cell_ad0488;
// @ref ?Unit_Ore_Miner_Under_Attack_007F819C@@3QBDB=007f819c
// @ref ?unknown_coord_ad04c0@@3UCoordStruct@@B=00ad04c0
// @ref ?unknown_cell_ad0488@@3VCell@@B=00ad0488
// @ref ?unknown_flag_a3d2c1@@3_NA=00a3d2c1
// @ref ?Unknown_0063B5B0@@YI_NHVCell@@@Z=0063b5b0
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
// @ref ?unknown_slot86@FootClass@@UAEHPAHHPAVWarheadTypeClass@@PAVTechnoClass@@_NH@Z=004c6000
// @ref ?unknown_4ccfc0@FootClass@@QAEPAV1@XZ=004ccfc0
// @ref ?unknown_6fd3a0@UnitClass@@QAEXXZ=006fd3a0
// @ref ?unknown_707170@UnitClass@@QAE_NPAVTechnoClass@@@Z=00707170
// @ref ?unknown_func_6b8cc0@TeamClass@@QAE_NPAVFootClass@@@Z=006b8cc0
// @ref ?unknown_func_6b41f0@TagClass@@QBE_NXZ=006b41f0
// @ref ?Is_Radio_Contact@RadioClass@@QBE_NPAVTechnoClass@@@Z=00636e30
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Is_Ally@HouseClass@@QBE_NPAVTechnoClass@@@Z=004e5580
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?Attach_Tag@ObjectClass@@QAE_NPAVTagClass@@@Z=005d4430
static inline AnimTypeClass *Unit_Damage_Last_Water_Animation() {
    DynamicVectorClass<AnimTypeClass *> const &animations =
        static_cast<DynamicVectorClass<AnimTypeClass *> const &>(Rules->SplashList);
    return animations[animations.Count() - 1];
}
static inline CoordStruct Unit_Damage_Raised_Position(CoordStruct const &position) { CoordStruct result = position; result.Z += 5; return result; }
int UnitClass::unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead,
                            TechnoClass *source, bool forced, int arg6)
{
    CoordStruct animation_position;
    bool restore_selection = unknown_77 && House->Unknown_004F52B0();
    int result = FootClass::unknown_slot86(damage, distance, warhead, source, forced, arg6);
    if (result == 5) return result;
    if (result == 4) {
        if (Type->DeathFrames > 0) {
            if (unknown_5c0 == -1) {
                unknown_5c0 = 0;
                unknown_slot216((int)source);
            }
            Strength = 1;
            unknown_7d = true;
        } else {
            if (Type->Naval && !Type->Underwater && !Type->Organic &&
                Type->Weight >= Rules->ShipSinkingWeight) {
                CoordStruct position = Coord;
                Cell cell = Coord_Cell(position);
                if (Map[cell].unknown_47b7e0() && !unknown_205) {
                    unknown_slot216((int)source);
                    Strength = 1;
                    unknown_7d = true;
                    unknown_325 = true;
                    unknown_slot210();
                    goto remove_passengers;
                }
            }
            unknown_slot216((int)source);
            if (warhead == Rules->unknown_cac) {
                int count = abs(unknown_id_source_a3d290->Random()() % 3) + 7;
                while (count > 0) {
                    ParticleSystemClass *system = new ParticleSystemClass(Rules->unknown_cf4,
                        Center_Coord(), 0, this, unknown_coord_ad04c0);
                    system->unknown_e5 = true;
                    --count;
                }
            } else {
                if (unknown_slot108() <= 10 && unknown_7c) {
                    animation_position = Coord;
                    if (Map[animation_position].unknown_ec == 2) {
                        new AnimClass(Rules->unknown_09c, (animation_position = Coord), 0, 1, 0x600, 0);
                        new AnimClass(Unit_Damage_Last_Water_Animation(),
                            (animation_position = Unit_Damage_Raised_Position(Coord)),
                            0, 1, 0x600, 0);
                        goto remove_passengers;
                    }
                }
                unknown_6fd3a0();
            }
        }
remove_passengers:
        unknown_slot71(0);
        if (!Type->Crashable) {
            while (Cargo.Object) {
                FootClass *passenger = unknown_4ccfc0();
                if (!passenger) break;
                int move = passenger->unknown_slot101(&Map[CoordStruct(Coord)], -1, -1, 0, 1);
                bool can_place = move == 0 || move == 2;
                ++unknown_a40774;
                passenger->unknown_79 = unknown_79;
                animation_position = Coord;
                animation_position.Z = unknown_slot105()->Center_Coord().Z;
                if (!forced && !unknown_7c && can_place) {
                    int facing = Dir_To_256(unknown_2e0.Current());
                    if (passenger->unknown_slot53(&animation_position, facing)) {
                        passenger->unknown_slot87(unknown_coord_ad04c0, true, false);
                        if (!House->Unknown_004F52F0()) {
                            if (Team) Team->unknown_func_6b8cc0(passenger);
                            else passenger->unknown_slot116(15, false);
                        }
                        if (restore_selection) passenger->unknown_slot80();
                        goto passenger_removed;
                    }
                }
                passenger->unknown_slot55(source);
                delete passenger;
passenger_removed:
                --unknown_a40774;
            }
        }
        {
            InfantryClass *crew;
            if (unknown_290 == -1) {
                if ((unsigned char)arg6 || !Type->Crewed || Type->Passengers != 0 ||
                    (double)unknown_id_source_a3d290->Random()(0, 0x7ffffffe) *
                        (1.0 / 2147483646.0) >= Rules->CrewEscape)
                    goto drop_crate;
            }
            if (unknown_290 != -1) {
                crew = new InfantryClass(InfantryTypes[unknown_290], House);
            } else {
                InfantryTypeClass *crew_type = (InfantryTypeClass *)unknown_slot184();
                if (!crew_type) goto drop_crate;
                crew = new InfantryClass(crew_type, House);
            }
            if (crew) {
                crew->unknown_79 = unknown_79;
                CoordStruct position = Coord;
                if (crew->unknown_slot53(&position, 0)) {
                    crew->Strength = unknown_id_source_a3d290->Random()(5, crew->Type->MaxStrength / 2);
                    crew->unknown_slot87(unknown_coord_ad04c0, true, false);
                    if (!House->Unknown_004F52F0()) crew->unknown_slot116(15, false);
                    else crew->unknown_slot116(5, false);
                    if (restore_selection) crew->unknown_slot80();
                    if (unknown_34 && unknown_34->unknown_func_6b41f0()) crew->Attach_Tag(unknown_34);
                } else {
                    delete crew;
                }
            }
        }
drop_crate:
        if (Type->CarriesCrate &&
            ((unknown_id_source_a3d290->TruckCrate && !Type->IsTrain) ||
             (unknown_id_source_a3d290->unknown_2229 && Type->IsTrain))) {
            Cell destination;
            destination = Map.Unknown_005502E0(unknown_slot104(), 1, -1, 0, false,
                Point2D(1, 1), 1, 0, 0, 1, Cell(0, 0), 0);
            if (destination != unknown_cell_ad0488 && unknown_flag_a3d2c1)
                Map.Unknown_0054E580(destination, 20);
        }
        if (Type->Crashable) {
            if (!unknown_slot224(0)) unknown_slot60();
        } else {
            if (!unknown_325) unknown_slot60();
        }
    } else {
        if (result && Type->Harvester && House == unknown_player_a35db4) {
            Cell cell = Coord_Cell(unknown_slot19(0));
            if (Unknown_0063B5B0(4, cell))
                Speech_Play_Name(Unit_Ore_Miner_Under_Attack_007F819C, -1, -1);
        }
        if (Team || !source || unknown_370 || House->Is_Ally(source) || House->Unknown_004F52F0())
            return result;
        if (unknown_707170(source)) {
            unknown_slot260(source, 1);
            unknown_slot116(2, false);
            return result;
        }
        if (!(Type->Harvester || Type->Weeder) || unknown_slot166() <= 0 ||
            Health_Ratio() > Rules->unknown_1368) return result;
        TechnoClass *dock = 0;
        for (int index = 0; index < Type->Dock.Count(); ++index) {
            dock = unknown_slot301(Type->Dock[index], 0, 0);
            if (dock) break;
        }
        if (dock && !Is_Radio_Contact(dock) && unknown_slot150(2, dock) == 1)
            unknown_slot116(7, false);
    }
    return result;
}
