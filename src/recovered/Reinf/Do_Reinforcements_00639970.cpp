// bool __fastcall Do_Reinforcements(TeamTypeClass *teamtype, int wp) -- 0x00639970 (TS reinf.cpp)
// Creates the team type's group and brings it in at its waypoint (or wp): infantry next to a
// building or transport pop out of it, droppod teams arrive by paradrop plane, others through
// Create_Reinforcement. Allied arrivals mark the radar event cell.
#include "shared/reinforcement.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/script.hpp"
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"
#include "shared/radar_event_class.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ??0CoordStruct@@QAE@ABVCell@@H@Z=0061ea80
// @ref ??_C@_07IIFO@PDPLANE?$AA@=007ee570
// @ref ?Create_Reinforcement@@YI_NPAVTeamTypeClass@@PAVFootClass@@ABVCell@@_N@Z=0063a050

FootClass * __fastcall _Create_Group(TeamTypeClass *teamtype);

static bool _Pop_Group_Out_Of_Object(FootClass *group, TechnoClass *object)
{
    int quantity = 0;

    while (group != 0) {
        TechnoClass *todo = group;
        group = (FootClass *)group->unknown_30;
        todo->unknown_30 = 0;

        switch (object->Kind_Of()) {
            case 6:
                if (object->unknown_slot62(todo) != 2) {
                    delete todo;
                } else {
                    object->unknown_slot149(3);
                    ++quantity;
                }
                break;

            case 1:
            case 2:
                object->Cargo.Unknown_00468960((FootClass *)todo);
                todo->unknown_slot69();
                object->unknown_slot116(0x10, false);
                ++quantity;
                break;

            default:
                delete todo;
                break;
        }
    }

    return quantity != 0;
}

static bool _Consists_Only_Of_Infantry(FootClass const *first)
{
    while (first != 0) {
        if (first->Kind_Of() != 0xF) {
            return false;
        }
        first = (FootClass const *)first->unknown_30;
    }
    return true;
}

static TechnoClass *_Who_Can_Pop_Out_Of(Cell origin)
{
    CellClass *cellptr = &Map[origin];
    TechnoClass *candidate = 0;

    for (int f = -1; f < 8; f++) {
        CellClass *ptr = cellptr;
        if (f != -1) {
            ptr = &ptr->Adjacent_Cell(f);
        }

        TechnoClass *building = (TechnoClass *)ptr->unknown_4717b0();
        if (building && building->Strength > 0) {
            candidate = building;
        }

        UnitClass *unit = (UnitClass *)ptr->Cell_Unit();
        if (unit && unit->Strength && unit->Type->Passengers > 0) {
            return unit;
        }
    }
    return candidate;
}

static bool _Create_Paradrop(TeamTypeClass *teamtype, FootClass *object, Cell origin)
{
    Cell dest;
    TechnoTypeClass *ptype = AircraftTypes[AircraftTypeClass::From_Name("PDPLANE")];
    unknown_a40774++;
    AircraftClass *plane = (AircraftClass *)ptype->unknown_slot35(object->House);
    unknown_a40774--;
    if (plane) {
        plane->unknown_32c = true;

        if (teamtype->UseTransportOrigin) {
            dest = teamtype->Transport_Waypoint_Location();
        } else {
            int source = object->House->unknown_128;
            switch (source) {
                case 0:
                case 1:
                case 2:
                case 3:
                    break;

                default:
                    source = 0;
                    break;
            }
            dest = Map.Unknown_0049A700(source, unknown_geometry_k, unknown_geometry_k, 4, 1, 0);
        }

        plane->unknown_slot116(0x1A, false);
        plane->unknown_slot260(0, 1);
        plane->unknown_slot220((AbstractClass *)&Map[origin]);

        unknown_a40774++;
        int placed = plane->unknown_slot53(&CoordStruct(dest, 0), 0);
        unknown_a40774--;
        if (placed) {
            plane->unknown_5b1 = true;
            plane->Cargo.Unknown_00468960(object);
            plane->unknown_slot117();
            return true;
        } else {
            delete plane;
        }
    }
    return false;
}

bool __fastcall Do_Reinforcements(TeamTypeClass *teamtype, int wp)
{
    if (!teamtype || !teamtype->TaskForce->CountEntries) return false;

    if (teamtype->Script == 0 || teamtype->Script->MissionCount == 0) {
        ScriptMissionClass tmission(5, 0);
        if (teamtype->Script == 0) {
            teamtype->Script = new ScriptTypeClass(0);
        }
        ScriptTypeClass *script = teamtype->Script;
        int count = script->MissionCount;
        if (count < 50) {
            script->MissionList[count] = tmission;
            script->MissionCount++;
        }
    }

    bool atwaypoint = false;
    bool drop_pod = false;
    if (teamtype->Droppod) {
        drop_pod = true;
    }

    FootClass *object = _Create_Group(teamtype);
    object->Team->IsTransient = false;

    if (!object) {
        return false;
    }

    atwaypoint = wp != -1;
    Cell origin;
    if (atwaypoint) {
        origin = unknown_id_source_a3d290->Get_Waypoint_Location(wp);
    } else {
        origin = teamtype->Waypoint_Location();
    }

    if (!drop_pod && origin != unknown_geometry_k && _Consists_Only_Of_Infantry(object)) {
        TechnoClass *candidate = _Who_Can_Pop_Out_Of(origin);
        if (candidate != 0) {
            return _Pop_Group_Out_Of_Object(object, candidate);
        }
    }

    bool onmap = atwaypoint && Map.Unknown_0055A660(origin, true);

    bool ok;
    if (!drop_pod) {
        ok = Create_Reinforcement(teamtype, object, origin, onmap);
    } else {
        ok = _Create_Paradrop(teamtype, object, origin);
    }

    if (ok && teamtype->Owner->Is_Ally(unknown_player_a35db4)) {
        RadarEventClass_unknown_remember_cell(origin);
    }
    return true;
}
