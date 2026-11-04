// int UnitClass::unknown_slot28(ObjectClass *object, bool arg2) (0x00703BD0, slot 28)
// TibSun UnitClass::What_Action(ObjectClass const *, bool): the action for a clicked object.
// Action numbers are ActionType values as in the Foot answer: 4 self, 5 attack, 7 select,
// 0x1E no deploy, 0x1D repair, 0x1F enter. A deploying unit checks its building footprint
// with its own occupation lifted; a loaded unit checks the passenger can stand in the cell.
#include "shared/unit.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/ground_type.hpp"
TechnoClass *__fastcall As_Techno_0040dbd0(AbstractClass *object);
unsigned char __fastcall Infantry_Action_Allowed_00614b50(int action);
// @ref ?As_Techno_0040dbd0@@YIPAVTechnoClass@@PAVAbstractClass@@@Z=0040dbd0
// @ref ?Infantry_Action_Allowed_00614b50@@YIEH@Z=00614b50
// @ref ?unknown_slot28@FootClass@@UAEHPAVObjectClass@@_N@Z=004cc740

// The cell's land type as an inline, so its read is not shared across the passenger's virtual
// call (shared/cell_class.hpp has this member; shared/cell.hpp does not).
inline int Land_Type_00703bd0(CellClass const *cell) { return cell->unknown_ec; }
// A building's type (a view: BuildingClass is not declared in this unit).
class UnknownBuildingView_00703bd0 : public TechnoClass {
public:
    BuildingTypeClass *Type;
};

int UnitClass::unknown_slot28(ObjectClass *object, bool arg2)
{
    int action = FootClass::unknown_slot28(object, arg2);
    if (action == 8) {
        return 8;
    }
    if (unknown_6c16f0(-1) < 0 && House->Unknown_004F52B0() && action != 4) {
        if (House->Is_Ally((TechnoClass *)object)) {
            if (object->unknown_slot31() && object != this && object->unknown_slot30()) {
                if (object->Kind_Of() != 2 || Map[object->Center_Coord()].unknown_4717b0() == 0) {
                    if (object->Health_Ratio() < Rules->unknown_1360) {
                        action = 0x1d;
                    }
                }
            } else if (object->Kind_Of() != 6) {
                action = 7;
            }
        } else {
            action = 0;
        }
    }
    if (action == 5) {
        if (!unknown_slot38()) {
            if ((Type->Crusher || unknown_6d7910(0x11)) && object->Class_Of()->unknown_1fd) {
                action = 1;
            } else {
                action = 7;
            }
        }
    } else if (action == 4) {
        if (Infantry_Action_Allowed_00614b50(action)) {
            if (Type->DeploysInto != 0) {
                Cell cell = Cell(Center_Coord());
                for (int index = 0; index < Rules->unknown_7c8.Count(); index++) {
                    if (Rules->unknown_7c8[index] == Type->DeploysInto) {
                        cell = cell + AdjacentCell[7];
                        break;
                    }
                }
                unknown_slot71(0);
                Locomotor.Checked()->Mark_All_Occupation_Bits(0);
                if (!Type->DeploysInto->unknown_slot42(cell, 0)) {
                    action = 0x1e;
                }
                Locomotor.Checked()->Mark_All_Occupation_Bits(1);
                unknown_slot71(1);
            } else if (!Type->IsSimpleDeployer) {
                if (Type->Passengers > 0) {
                    if (Cargo.Count == 0) {
                        action = 0x1e;
                    } else if (!unknown_79) {
                        CellClass *cell = &Map[CoordStruct(Coord)];
                        ObjectClass *passenger = Cargo.unknown_468a10();
                        if (passenger != 0 && Ground[Land_Type_00703bd0(cell)].Cost[passenger->unknown_slot32()->SpeedType] < 0.01 && Land_Type_00703bd0(cell) != 2) {
                            action = 0x1e;
                        }
                        if (Type->SpeedType != 3 && unknown_slot108() != 0) {
                            action = 0x1e;
                        }
                    }
                } else {
                    action = 0;
                }
            }
            if (action == 4 && !unknown_slot186()) {
                action = 0x1e;
            }
        } else {
            action = 0x1e;
        }
    }
    TechnoClass *techno = As_Techno_0040dbd0(object);
    if (House->Unknown_004F52B0() && techno != 0 && techno->House->Is_Ally(this)) {
        if (object->Kind_Of() == 6 && unknown_slot150(0xF, (TechnoClass *)object) == 1) {
            action = 3;
        }
    }
    if (House->Unknown_004F52B0() && action == 7) {
        if (object->Kind_Of() == 6) {
            UnknownBuildingView_00703bd0 *building = (UnknownBuildingView_00703bd0 *)object;
            if (building->Type->UnitRepair && unknown_slot150(0xF, building) == 1 && !building->In_Radio_Contact() && building->Cargo.Object == 0) {
                action = 1;
            }
        }
    } else if (action == 5) {
        if (!unknown_slot163()) {
            action = 0x3B;
        }
    }
    if (action != 0x1F) {
        if (House->Is_Ally((TechnoClass *)object) && House->Unknown_004F52B0() && As_Techno_0040dbd0(object) != 0 && action != 5 && action != 0x1D && action != 0x1A) {
            TechnoTypeClass *type = object->unknown_slot32();
            if (object != this && type != 0 && type->Passengers > 0) {
                if (object != 0 && object->AbstractFlags.IsFoot && static_cast<FootClass *>(object)->Locomotor.Checked()->Is_Moving()) {
                    action = 0x1F;
                } else {
                    switch (unknown_slot150(0xF, (TechnoClass *)object)) {
                    case 1:
                        action = 3;
                        break;
                    case 10:
                        action = 0x1F;
                        break;
                    }
                }
            }
        }
    }
    if (action == 0 && House->Unknown_004F52B0()) {
        action = 2;
    }
    if (action == 5 && !unknown_slot185()) {
        action = 0;
    }
    if (action == 2) {
        if (object->unknown_slot48() && object->unknown_slot51(true) == 0) {
            if (object->unknown_slot50(true)->Kind_Of() == 0x15) {
                action = 1;
            }
        }
    } else if (action == 5 && object->Class_Of()->unknown_203) {
        action = 2;
    }
    return action;
}
