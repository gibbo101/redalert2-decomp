// void __fastcall Unknown_0062CF40(int index) (0x0062CF40): saves the game state of the frame into sync
// state slot index (houses, every infantry, unit, aircraft and building, the map and logic layers) for
// Unknown_0062DBA0; without sync logging it only draws the random number.
#include "shared/queue.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/display.hpp"
#include "shared/unknown_list_832470.hpp"
#include "shared/id_source.hpp"
#include "shared/color_scheme.hpp"
#include "shared/house_type.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/ccini_extra.hpp"
// @ref ??_C@_07BKIB@Neutral?$AA@=007e14b8
// @ref ??_C@_07GALJ@Special?$AA@=007cdd70
// @ref ??_C@_0CH@LOGO@Adjusted?5allocation?5of?5log?5?$CFd?5to@=007edf10
// @ref ?unknown_flag_ab62e8@@3_NA=00ab62e8
// @ref ?unknown_random_aabce0@@3HA=00aabce0

void __fastcall Unknown_0062CF40(int index)
{
    if (!unknown_flag_ab62e8) {
        unknown_random_aabce0 = unknown_id_source_a3d290->RandomNumber();
        return;
    }

    UnknownSyncState *state = &unknown_sync_states_a780d8[index];
    state->unknown_000 = GameCRC;
    state->RandomNumber = unknown_id_source_a3d290->RandomNumber();
    state->Frame = ::Frame;

    int i, j;
    AbstractClass *target;
    int id;
    bool is_object;     // assigned only for a target (left unset otherwise, as the original keeps it in memory)
    char const *name;
    for (i = 0; i < 8; i++) {
        UnknownSyncHouse *sh = &state->Houses[i];
        sh->ID = -1;
        if (i < Houses.Count()) {
            sh->Name[0] = 0;
            for (j = 0; j < unknown_players_a3fa7c.Count(); j++) {
                if (unknown_players_a3fa7c[j]->ID == i) {
                    strncpy(sh->Name, Unknown_006FA120(unknown_players_a3fa7c[j]->Name), sizeof(sh->Name));
                }
            }
            if (sh->Name[0] == 0 && (_stricmp(Houses[i]->Type->ID, "Neutral") == 0 ||
                                     _stricmp(Houses[i]->Type->ID, "Special") == 0)) {
                strcpy(sh->Name, Houses[i]->Type->ID);
            }
            sh->IsHuman = Houses[i]->unknown_134;
            sh->Color[sizeof(sh->Color) - 1] = 0;
            strncpy(sh->Color, ColorSchemes[Houses[i]->ColorSchemeIndex]->Name, sizeof(sh->Color) - 1);
            sh->ID = i;
            sh->HouseType[sizeof(sh->HouseType) - 1] = 0;
            strncpy(sh->HouseType, HouseTypes[Houses[i]->Type->ArrayIndex]->ID, sizeof(sh->HouseType) - 1);
        }
    }

    int objects = Infantry.Count() + Units.Count() + Aircraft.Count() + unknown_BuildingClass_list_00a40af8.Count();
    int layered = unknown_list_832470.Count();
    for (i = 0; i < 5; i++) {
        layered += DisplayClass::Layer[i].Count();
    }
    if (!state->Buffer) {
        state->Buffer = new char[state->BufferSize];
    }
    int size = objects * sizeof(UnknownSyncObject) + layered * sizeof(UnknownSyncLayerObject);
    if (size + 0x400 > state->BufferSize) {
        delete[] state->Buffer;
        state->BufferSize = (size + 0xFFFF) & 0xFFFF0000;
        Debug_Printf("Adjusted allocation of log %d to %dKb\n", index, state->BufferSize >> 10);
        state->Buffer = new char[state->BufferSize];
    }

    UnknownSyncObject *obj = (UnknownSyncObject *)state->Buffer;
    int count = 0;
    state->Objects = obj;

    state->Counts[0] = Infantry.Count();
    for (count = 0; count < Infantry.Count(); count++) {
        InfantryClass *infp = Infantry[count];
        obj->Coord = Coord_CRC(infp->Coord);
        obj->Facing = Dir_To_256(infp->unknown_2e0.Current());
        obj->Mission = infp->unknown_slot91();
        obj->Type = infp->Type->ArrayIndex;
        obj->Speed = infp->unknown_468 * 256.0;
        obj->Owner = infp->House->ArrayIndex;
        obj->TypeName[sizeof(obj->TypeName) - 1] = 0;
        strncpy(obj->TypeName, infp->Type->ID, sizeof(obj->TypeName) - 1);
        target = infp->unknown_494;
        id = 0;
        if (target) {
            is_object = target->AbstractFlags.IsTechno;
        }
        if (target) {
            if (is_object) {
                id = target->unknown_slot16();
            } else if (target->Kind_Of() == 11) {
                id = ((CellClass *)target)->MapCoords.Y << 16 | ((CellClass *)target)->MapCoords.X;
            }
            name = Name_From_RTTI((RTTIType)target->Kind_Of());
            obj->NavCom[sizeof(obj->NavCom) - 1] = 0;
            obj->NavComID = id;
            strncpy(obj->NavCom, name, sizeof(obj->NavCom) - 1);
        } else {
            obj->NavComID = 0;
            obj->NavCom[0] = 0;
        }
        target = infp->unknown_228;
        id = 0;
        if (target) {
            is_object = target->AbstractFlags.IsTechno;
        }
        if (target) {
            if (is_object) {
                id = target->unknown_slot16();
            } else if (target->Kind_Of() == 11) {
                id = ((CellClass *)target)->MapCoords.Y << 16 | ((CellClass *)target)->MapCoords.X;
            }
            name = Name_From_RTTI((RTTIType)target->Kind_Of());
            obj->Target[sizeof(obj->Target) - 1] = 0;
            obj->TargetID = id;
            strncpy(obj->Target, name, sizeof(obj->Target) - 1);
        } else {
            obj->TargetID = 0;
            obj->Target[0] = 0;
        }
        obj++;
    }

    state->Counts[1] = Units.Count();
    for (i = 0; i < Units.Count(); i++) {
        UnitClass *unitp = Units[i];
        obj->Coord = Coord_CRC(unitp->Coord);
        obj->Facing = Dir_To_256(unitp->unknown_2e0.Current());
        obj->Facing2 = Dir_To_256(unitp->unknown_2f8.Current());
        obj->Mission = unitp->unknown_slot91();
        obj->Type = unitp->Type->ArrayIndex;
        obj->Speed = unitp->unknown_468 * 256.0;
        obj->Owner = unitp->House->ArrayIndex;
        obj->TrackNumber = unitp->Locomotor.Checked()->Get_Track_Number();
        obj->TrackIndex = unitp->Locomotor.Checked()->Get_Track_Index();
        obj->SpeedAccum = unitp->Locomotor.Checked()->Get_Speed_Accum();
        obj->TypeName[sizeof(obj->TypeName) - 1] = 0;
        strncpy(obj->TypeName, unitp->Type->ID, sizeof(obj->TypeName) - 1);
        target = unitp->unknown_494;
        id = 0;
        if (target) {
            is_object = target->AbstractFlags.IsTechno;
        }
        if (target) {
            if (is_object) {
                id = target->unknown_slot16();
            } else if (target->Kind_Of() == 11) {
                id = ((CellClass *)target)->MapCoords.Y << 16 | ((CellClass *)target)->MapCoords.X;
            }
            name = Name_From_RTTI((RTTIType)target->Kind_Of());
            obj->NavCom[sizeof(obj->NavCom) - 1] = 0;
            obj->NavComID = id;
            strncpy(obj->NavCom, name, sizeof(obj->NavCom) - 1);
        } else {
            obj->NavComID = 0;
            obj->NavCom[0] = 0;
        }
        target = unitp->unknown_228;
        id = 0;
        if (target) {
            is_object = target->AbstractFlags.IsTechno;
        }
        if (target) {
            if (is_object) {
                id = target->unknown_slot16();
            } else if (target->Kind_Of() == 11) {
                id = ((CellClass *)target)->MapCoords.Y << 16 | ((CellClass *)target)->MapCoords.X;
            }
            name = Name_From_RTTI((RTTIType)target->Kind_Of());
            obj->Target[sizeof(obj->Target) - 1] = 0;
            obj->TargetID = id;
            strncpy(obj->Target, name, sizeof(obj->Target) - 1);
        } else {
            obj->TargetID = 0;
            obj->Target[0] = 0;
        }
        obj++;
        count++;
    }

    state->Counts[2] = Aircraft.Count();
    for (i = 0; i < Aircraft.Count(); i++) {
        AircraftClass *aircraftp = Aircraft[i];
        obj->Coord = Coord_CRC(aircraftp->Coord);
        obj->Facing = Dir_To_256(aircraftp->unknown_2e0.Current());
        obj->Mission = aircraftp->unknown_slot91();
        obj->Type = aircraftp->Type->ArrayIndex;
        obj->Speed = aircraftp->unknown_468 * 256.0;
        obj->Owner = aircraftp->House->ArrayIndex;
        obj->TypeName[sizeof(obj->TypeName) - 1] = 0;
        strncpy(obj->TypeName, aircraftp->Type->ID, sizeof(obj->TypeName) - 1);
        target = aircraftp->unknown_494;
        id = 0;
        if (target) {
            is_object = target->AbstractFlags.IsTechno;
        }
        if (target) {
            if (is_object) {
                id = target->unknown_slot16();
            } else if (target->Kind_Of() == 11) {
                id = ((CellClass *)target)->MapCoords.Y << 16 | ((CellClass *)target)->MapCoords.X;
            }
            name = Name_From_RTTI((RTTIType)target->Kind_Of());
            obj->NavCom[sizeof(obj->NavCom) - 1] = 0;
            obj->NavComID = id;
            strncpy(obj->NavCom, name, sizeof(obj->NavCom) - 1);
        } else {
            obj->NavComID = 0;
            obj->NavCom[0] = 0;
        }
        target = aircraftp->unknown_228;
        id = 0;
        if (target) {
            is_object = target->AbstractFlags.IsTechno;
        }
        if (target) {
            if (is_object) {
                id = target->unknown_slot16();
            } else if (target->Kind_Of() == 11) {
                id = ((CellClass *)target)->MapCoords.Y << 16 | ((CellClass *)target)->MapCoords.X;
            }
            name = Name_From_RTTI((RTTIType)target->Kind_Of());
            obj->Target[sizeof(obj->Target) - 1] = 0;
            obj->TargetID = id;
            strncpy(obj->Target, name, sizeof(obj->Target) - 1);
        } else {
            obj->TargetID = 0;
            obj->Target[0] = 0;
        }
        obj++;
        count++;
    }

    state->Counts[3] = unknown_BuildingClass_list_00a40af8.Count();
    for (i = 0; i < unknown_BuildingClass_list_00a40af8.Count(); i++) {
        BuildingClass *bldgp = unknown_BuildingClass_list_00a40af8[i];
        obj->Coord = Coord_CRC(bldgp->Coord);
        obj->Facing = Dir_To_256(bldgp->unknown_2e0.Current());
        obj->Mission = bldgp->unknown_slot91();
        obj->Type = bldgp->Type->ArrayIndex;
        obj->Owner = bldgp->House->ArrayIndex;
        obj->NavComID = 0;
        obj->NavCom[0] = 0;
        obj->TypeName[sizeof(obj->TypeName) - 1] = 0;
        strncpy(obj->TypeName, bldgp->Type->ID, sizeof(obj->TypeName) - 1);
        target = bldgp->unknown_228;
        id = 0;
        if (target) {
            is_object = target->AbstractFlags.IsTechno;
        }
        if (target) {
            if (is_object) {
                id = target->unknown_slot16();
            } else if (target->Kind_Of() == 11) {
                id = ((CellClass *)target)->MapCoords.Y << 16 | ((CellClass *)target)->MapCoords.X;
            }
            name = Name_From_RTTI((RTTIType)target->Kind_Of());
            obj->Target[sizeof(obj->Target) - 1] = 0;
            obj->TargetID = id;
            strncpy(obj->Target, name, sizeof(obj->Target) - 1);
        } else {
            obj->TargetID = 0;
            obj->Target[0] = 0;
        }
        obj++;
        count++;
    }
    state->ObjectCount = count;

    UnknownSyncLayerObject *obj_layer = (UnknownSyncLayerObject *)obj;
    for (i = 0; i < 5; i++) {
        state->Layers[i] = obj_layer;
        count = 0;
        for (j = 0; j < DisplayClass::Layer[i].Count(); j++) {
            ObjectClass *objp = DisplayClass::Layer[i][j];
            if (objp->Kind_Of() == 4 && objp->Fetch_ID() == -2) {
                continue;
            }
            obj_layer->Value = Coord_CRC(objp->Coord);
            obj_layer->RTTI = objp->Kind_Of();
            if (objp->Kind_Of() != 0x2B && objp->Kind_Of() != 0x13) {
                obj_layer->Type = objp->Class_Of()->unknown_slot16();
                obj_layer->Name[sizeof(obj_layer->Name) - 1] = 0;
                strncpy(obj_layer->Name, objp->Class_Of()->ID, sizeof(obj_layer->Name) - 1);
            } else {
                obj_layer->Type = -1;
                obj_layer->Name[0] = 0;
            }
            HouseClass *owner = objp->Owning_House();
            if (owner) {
                obj_layer->Owner = owner->ArrayIndex;
            } else {
                obj_layer->Owner = -1;
            }
            obj_layer++;
            count++;
        }
        state->LayerCounts[i] = count;
    }

    state->Logic = obj_layer;
    count = 0;
    for (i = 0; i < unknown_list_832470.Count(); i++) {
        ObjectClass *objp = unknown_list_832470[i];
        if (objp->Kind_Of() == 4 && objp->Fetch_ID() == -2) {
            continue;
        }
        obj_layer->Value = Coord_CRC(objp->Coord);
        obj_layer->RTTI = objp->Kind_Of();
        if (objp->Kind_Of() != 0x2B && objp->Kind_Of() != 0x13) {
            obj_layer->Type = objp->Class_Of()->unknown_slot16();
            obj_layer->Name[sizeof(obj_layer->Name) - 1] = 0;
            strncpy(obj_layer->Name, objp->Class_Of()->ID, sizeof(obj_layer->Name) - 1);
        } else {
            obj_layer->Type = -1;
            obj_layer->Name[0] = 0;
        }
        HouseClass *owner = objp->Owning_House();
        if (owner) {
            obj_layer->Owner = owner->ArrayIndex;
        } else {
            obj_layer->Owner = -1;
        }
        obj_layer++;
        count++;
    }
    state->LogicCount = count;
}
