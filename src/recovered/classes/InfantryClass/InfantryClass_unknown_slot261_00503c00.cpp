// bool InfantryClass::unknown_slot261(bool arg1, bool arg2) (0x00503C00, slot 261)
// FootClass's answer; unless slot 270 holds or the mission is 28, chooses
// a follow-up mission: with a target 1 (keeping 17 or 8), with +0x494 2
// (keeping 8 or 17); otherwise (not under missions 5 or 11 or a mission
// whose control has +0x05/+0x07; false then) 11 or 5 by owner, team, house
// +0x194 against the rules' +0x10A8, slot 163, Engineer, VehicleThief,
// 0x006D7910 (16) and DefaultToGuardArea. Queues it unless the current
// mission is 25 or 11.
#include "shared/infantry.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_slot261@FootClass@@UAE_N_N0@Z=004c6f10
// @ref ?unknown_4c8b00@FootClass@@QAEXXZ=004c8b00
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910

bool InfantryClass::unknown_slot261(bool arg1, bool arg2)
{
    bool result = FootClass::unknown_slot261(arg1, arg2);
    if (unknown_slot270()) {
        return result;
    }
    if (unknown_slot91() == 28) {
        return result;
    }
    int mission;
    if (unknown_228 != 0) {
        mission = 1;
        if (unknown_slot91() == 17) {
            mission = 17;
        }
        if (unknown_slot91() == 8) {
            mission = 8;
        }
    } else {
        unknown_4c8b00();
        if (unknown_494 != 0) {
            mission = 2;
            if (unknown_slot91() == 8) {
                mission = 8;
            }
            if (unknown_slot91() == 17) {
                mission = 17;
            }
        } else {
            if (unknown_slot91() == 5 || unknown_slot91() == 11) {
                return false;
            }
            if (unknown_slot91() != -1 && (Control()->unknown_05 || Control()->unknown_07)) {
                return false;
            }
            if (!House->Unknown_004F52F0() && Team == 0) {
                if (House->unknown_194 < Rules->unknown_10a8 && Mission != 11) {
                    mission = 5;
                } else if (!unknown_slot163() && !Type->Engineer && !Type->VehicleThief) {
                    mission = 5;
                } else {
                    mission = 11;
                }
            } else if (Mission != 11 && ((!unknown_6d7910(16) && !Type->DefaultToGuardArea) || Team != 0)) {
                mission = 5;
            } else {
                mission = 11;
            }
        }
    }
    if (Mission != 25 && Mission != 11 && mission != -1) {
        unknown_slot116(mission, false);
    }
    return result;
}
