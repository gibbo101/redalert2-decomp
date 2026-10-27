// Whether a foot object may join the team, and the task force slot it would fill (written to *slot): it must be a live object of the team's house that is not in radio contact (aircraft only airport-bound ones), recruitable, outranking its current team, and its type must be in the task force with room left.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/techno_type.hpp"
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?unknown_594db0@MissionClass@@SI_NH@Z=00594db0
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10

bool TeamClass::unknown_func_6b8dc0(FootClass *member, int *slot)
{
    if (this != member->Team && unknown_func_6bdd80(member) && member->House == Owner) {
        if (!member->In_Radio_Contact() || (member->Kind_Of() == 2 && ((AircraftClass *)member)->Type->AirportBound)) {
            if (member->unknown_slot91() == -1 || MissionClass::unknown_594db0(member->unknown_slot91())) {
                if (member->unknown_379 || Class->Autocreate) {
                    bool aircraft_or_waiting = false;
                    if (Script != 0) {
                        if (Script->Get_Current_Mission().Mission == 8) {
                            aircraft_or_waiting = true;
                        }
                    }
                    if (member->Kind_Of() == 2) {
                        aircraft_or_waiting = true;
                    }
                    if (member->unknown_37a || !Class->Autocreate || aircraft_or_waiting) {
                        if (member->Team == 0 || member->Team->Class->Priority < Class->Priority) {
                            if (member->Kind_Of() != 2 || member->unknown_slot231(0)->WeaponType == 0 || member->unknown_254 != 0) {
                                for (*slot = 0; *slot < Class->TaskForce->CountEntries; (*slot)++) {
                                    if (Class->TaskForce->Entries[*slot].Type == member->Class_Of()) {
                                        break;
                                    }
                                }
                                if (*slot != Class->TaskForce->CountEntries) {
                                    return unknown_84[*slot] < Class->TaskForce->Entries[*slot].Amount ? true : false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
