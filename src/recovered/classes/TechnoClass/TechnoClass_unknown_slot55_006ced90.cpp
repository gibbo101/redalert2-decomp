// void TechnoClass::unknown_slot55(TechnoClass *killer) (0x006CED90, slot 55)
// Records the object's destruction by the techno killer (may be null): springs
// its tag (events 6 and 4 with a killer; for non-units 7 with a killer, 0x30
// and 0x1D), gives the killer (and its +0x23C parent when the killer's type
// has +0xB18) experience for the object's cost (doubled for veterans,
// tripled for elites, none for an ally), notes the killer's owner on the
// owner (+0x53B8) and adds the points to the killer's owner (+0x5418); then
// counts the loss by kind in the killer owner's trackers and per-house
// tables and asks for a radar redraw.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/tag.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/foot.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_cell_ac0148@@3VCell@@A=00ac0148
// @ref ?Spring@TagClass@@QAE_NHPAVObjectClass@@VCell@@_NH@Z=006b3df0
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?unknown_7133a0@UnknownTechnoPair@@QBE_NXZ=007133a0
// @ref ?unknown_713420@UnknownTechnoPair@@QBE_NXZ=00713420
// @ref ?Unknown_00713360@UnknownTechnoPair@@QAEXHH@Z=00713360
// @ref ?Unknown_0070C490@UnknownHouseTracker@@QAEXH@Z=0070c490

void TechnoClass::unknown_slot55(TechnoClass *killer)
{
    int found = 0;
    int points = unknown_slot32()->unknown_slot33((int)House);
    if (unknown_7d && unknown_34 != 0 && killer != 0) {
        unknown_34->Spring(6, this, unknown_cell_ac0148, 0, 0);
    }
    if (unknown_7d) {
        if (unknown_34 != 0 && killer != 0) {
            unknown_34->Spring(4, this, unknown_cell_ac0148, 0, 0);
        }
        if (unknown_7d && Kind_Of() != 1) {
            if (unknown_7d && unknown_34 != 0 && killer != 0) {
                unknown_34->Spring(7, this, unknown_cell_ac0148, 0, 0);
            }
            if (unknown_7d && unknown_34 != 0) {
                unknown_34->Spring(0x30, this, unknown_cell_ac0148, 0, 0);
            }
            if (unknown_7d && unknown_34 != 0) {
                unknown_34->Spring(0x1D, this, unknown_cell_ac0148, 0, 0);
            }
        }
    }
    if (killer != 0) {
        if (killer->House->Is_Ally(this)) {
            points = 0;
        } else if (unknown_118.unknown_7133a0()) {
            points += points;
        } else if (unknown_118.unknown_713420()) {
            points *= 3;
        }
        if (killer->unknown_slot32()->Trainable) {
            killer->unknown_118.Unknown_00713360(killer->unknown_slot32()->unknown_slot33((int)House), points);
        }
        if (killer->unknown_slot32()->MissileSpawn && killer->unknown_23c != 0
            && ((TechnoClass *)killer->unknown_23c)->unknown_slot32()->Trainable) {
            ((TechnoClass *)killer->unknown_23c)->unknown_118.Unknown_00713360(
                ((TechnoClass *)killer->unknown_23c)->unknown_slot32()->unknown_slot33((int)House), points);
        }
        House->unknown_53b8 = killer->Owner();
        killer->House->unknown_5418 += points;
    }
    switch (Kind_Of()) {
    case 6:
        if (unknown_slot32()->unknown_202) {
            break;
        }
        if (((BuildingClass *)this)->unknown_434 != -1) {
            House->unknown_53b4++;
        }
        if (killer != 0) {
            killer->House->unknown_3aa0.Unknown_0070C490(((BuildingClass *)this)->Type->ArrayIndex);
            killer->House->unknown_5364[Owner()]++;
        }
        if (Map.Unknown_006331A0()) {
            Map.Unknown_006331E0(false);
        }
        break;
    case 2:
        if (killer != 0) {
            killer->House->unknown_2288.Unknown_0070C490(((AircraftClass *)this)->Type->ArrayIndex);
            found = 1;
        }
    case 15:
        if (killer != 0 && !found) {
            killer->House->unknown_2a90.Unknown_0070C490(((InfantryClass *)this)->Type->ArrayIndex);
            found = 1;
        }
    case 1:
        if (killer != 0 && !found) {
            killer->House->unknown_3298.Unknown_0070C490(((UnitClass *)this)->Type->ArrayIndex);
        }
        House->unknown_5360++;
        if (killer != 0) {
            killer->House->unknown_5310[Owner()]++;
        }
        if (Map.Unknown_006331A0()) {
            Map.Unknown_006331E0(false);
        }
        break;
    }
}
