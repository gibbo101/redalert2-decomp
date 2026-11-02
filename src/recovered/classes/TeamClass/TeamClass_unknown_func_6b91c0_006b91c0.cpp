// int TeamClass::unknown_func_6b91c0(int slot) (0x006B91C0; Red Alert's Recruit)
// Adds the nearest object (squared distance from the team's zone or the type's waypoint, 0x3200 more
// outside the type's group unless the group is -2 or the type recruits) of task force slot's type that
// may join, when the slot is still short: infantry, aircraft, or one of the owner's units with its
// passengers. Returns the number added.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/aircraft.hpp"
#include "shared/infantry_type.hpp"
// @ref _unknown_geometry_l=00ac0070
// @ref _unknown_geometry_k=00ac0050
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ?Aircraft@@3V?$DynamicVectorClass@PAVAircraftClass@@@@A=00a40398
// @ref ?Units@@3V?$DynamicVectorClass@PAVUnitClass@@@@A=00866198


int TeamClass::unknown_func_6b91c0(int slot)
{
    CoordStruct center = unknown_34 != 0 ? unknown_34->Center_Coord() : unknown_geometry_l;
    if (Class->Waypoint_Location() != unknown_geometry_k) {
        center = Cell_Coord(Class->Waypoint_Location());
    }
    int added = 0;
    if (Class->TaskForce->Entries[slot].Amount > unknown_84[slot]) {
        int group = Class->Get_Group();
        switch (Class->TaskForce->Entries[slot].Type->Kind_Of()) {
        case 0xF:
        case 0x10: {
            FootClass *best = 0;
            int best_distance = -1;
            for (int index = 0; index < Infantry.Count(); index++) {
                FootClass *infantry = (FootClass *)Infantry[index];
                if (group == -2 || infantry->unknown_1ac == group || Class->Recruiter) {
                    int distance = infantry->Distance_Squared(center);
                    if (infantry->unknown_1ac != group) {
                        distance += 0x3200;
                    }
                    if ((distance < best_distance || best_distance == -1) && unknown_func_6b8dc0(infantry, &slot)) {
                        best = infantry;
                        best_distance = distance;
                    }
                }
            }
            if (best != 0) {
                best->unknown_slot220(0);
                unknown_func_6b8cc0(best);
                added++;
            }
            break;
        }
        case 2:
        case 3: {
            AircraftClass *best = 0;
            int best_distance = -1;
            for (int index = 0; index < Aircraft.Count(); index++) {
                AircraftClass *aircraft = Aircraft[index];
                if (group == -2 || aircraft->unknown_1ac == group || Class->Recruiter) {
                    int distance = aircraft->Distance_Squared(center);
                    if (aircraft->unknown_1ac != group) {
                        distance += 0x3200;
                    }
                    if ((distance < best_distance || best_distance == -1) && unknown_func_6b8dc0(aircraft, &slot)) {
                        best = aircraft;
                        best_distance = distance;
                    }
                }
            }
            if (best != 0) {
                best->unknown_slot220(0);
                unknown_func_6b8cc0(best);
                added++;
            }
            break;
        }
        case 1:
        case 0x28: {
            UnitClass *best = 0;
            int best_distance = -1;
            for (int index = 0; index < Units.Count(); index++) {
                UnitClass *unit = Units[index];
                if (group == -2 || unit->unknown_1ac == group || Class->Recruiter) {
                    int distance = unit->Distance_Squared(center);
                    if (unit->unknown_1ac != group) {
                        distance += 0x3200;
                    }
                    if (unit->House == Owner && unit->Type == Class->TaskForce->Entries[slot].Type) {
                        if ((distance < best_distance || best_distance == -1) && unknown_func_6b8dc0(unit, &slot)) {
                            best = unit;
                            best_distance = distance;
                        }
                    }
                }
            }
            if (best != 0) {
                best->unknown_slot220(0);
                unknown_func_6b8cc0(best);
                added++;
                FootClass *passenger = (FootClass *)best->Cargo.unknown_468a10();
                while (passenger != 0) {
                    unknown_func_6b8cc0(passenger);
                    ObjectClass *next = passenger->unknown_30;
                    passenger = next != 0 && next->AbstractFlags.IsFoot ? (FootClass *)next : 0;
                }
            }
            break;
        }
        }
    }
    return added;
}
