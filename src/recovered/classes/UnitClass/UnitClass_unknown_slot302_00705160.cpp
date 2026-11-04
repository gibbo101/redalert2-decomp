// void UnitClass::Overrun_Square(Cell const &where, bool threaten) (0x00705160, slot 302)
// Crushing (hypothesis): where is the cell entered, threaten asks only to
// scatter. Picks the bridge level (+0x79, or this cell's level 4 below the
// unit's). Only for crushers (or ability 17). With arg2, scatters the
// level's occupants (0x00476920). Otherwise every crushable occupant within
// 0x4000 (squared) that is an enemy (or any, for trains) and not flagged
// +0x7A is crushed: a vehicle thief heading for this unit takes it over
// instead; afterwards slot 252.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/infantry_type.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?unknown_476920@CellClass@@QAEXPBX_N11@Z=00476920
// @ref ?unknown_ad04c0@@3HA=00ad04c0
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?Distance_Squared@ObjectClass@@QBEHABUCoordStruct@@@Z=005d4e00
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60

// A value the scatter takes (0x00AD04C0; meaning unknown).
extern int unknown_ad04c0;
// An infantry's type and destination (a view until shared/infantry.hpp is
// installed).
struct UnknownUnitInfantryView2 : TechnoClass {
    char unknown_418[0x494 - 0x418];
    AbstractClass *unknown_494;             // +0x494
    char unknown_498[0x5A8 - 0x498];
    InfantryTypeClass *Type;                // +0x5A8
};

void UnitClass::Overrun_Square(Cell const &where, bool threaten)
{
    CellClass *cell = &Map[where];
    bool upper = false;
    if (cell->unknown_140 & 0x100) {
        if (unknown_79) {
            upper = true;
        } else {
            Cell position = Coord_Cell(Center_Coord());
            if (Map[position].unknown_11b == cell->unknown_11b + 4) {
                upper = true;
            }
        }
    }
    if (!Type->Crusher && !unknown_6d7910(17)) {
        return;
    }
    if (threaten) {
        if (upper) {
            if (cell->unknown_128 & 0x1F) {
                cell->unknown_476920(&unknown_ad04c0, true, false, true);
            }
        } else if (cell->unknown_124 & 0x1F) {
            cell->unknown_476920(&unknown_ad04c0, true, false, false);
        }
        return;
    }
    ObjectClass *object;
    if (upper) {
        object = cell->AltOccupierPtr;
    } else {
        object = cell->OccupierPtr;
    }
    int crushed = 0;
    while (object) {
        if (object->Class_Of()->unknown_1fd
            && (!House->Is_Ally((TechnoClass *)object) || Type->IsTrain)
            && Distance_Squared(object->Center_Coord()) < 0x4000 && !object->unknown_7a) {
            UnknownUnitInfantryView2 *infantry = (UnknownUnitInfantryView2 *)object;
            if (object->Kind_Of() == 15 && infantry->Type->VehicleThief && infantry->unknown_494 == this && !Type->IsTrain) {
                ObjectClass *next = object->unknown_30;
                unknown_372 = infantry->unknown_372;
                unknown_slot54(false);
                unknown_slot222(infantry->House, 1);
                object->unknown_slot60();
                object = next;
            } else {
                ObjectClass *next = object->unknown_30;
                crushed = 1;
                Voc_Play_At(object->Class_Of()->unknown_1c0, CoordStruct(Coord), 0);
                object->unknown_slot55(this);
                object->unknown_slot71(0);
                object->unknown_slot52();
                object->unknown_slot60();
                object = next;
            }
        } else {
            object = object->unknown_30;
        }
    }
    if (crushed) {
        unknown_slot252((int)object);
    }
}
