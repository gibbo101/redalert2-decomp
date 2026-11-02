// void TeamClass::unknown_func_6ba1a0() (0x006BA1A0; Red Alert's Coordinate_Move)
// Moves the team toward its target (+0x40, else the mission target +0x3C) once no member lags:
// conscripts each member, sends the playing ones farther than the stray distance (doubled for slot 21)
// or still to climb/descend toward it, idles the arrived ones, and completes the step (StepCompleted) when
// every playing member arrived while the team is moving.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?Get_Next_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=006688b0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_func_6ba600@TeamClass@@QAE_NXZ=006ba600

void TeamClass::unknown_func_6ba1a0()
{
    FootClass *unit = Member;
    bool finished = true;
    bool found = false;
    if (unit == 0) {
        return;
    }
    if (unknown_40 == 0) {
        unknown_40 = unknown_3c;
    }
    if (unknown_40 != 0) {
        if (!unknown_func_6ba600()) {
            for (; unit != 0; unit = (FootClass *)unit->unknown_4c8) {
                if (unknown_func_6ba7d0(unit)) {
                    finished = false;
                }
                if (unit->unknown_slot91() == 0x10 || unit->MissionQueue == 0x10) {
                    finished = false;
                }
                if (unknown_func_6bdd80(unit) && (unit->unknown_579 || unit->Kind_Of() == 2)
                    && unit->unknown_slot91() != 0x10 && unit->MissionQueue != 0x10) {
                    int stray = Unknown_006BE6A0();
                    if (unit->unknown_slot21()) {
                        stray *= 2;
                    }
                    found = true;
                    int distance = unit->unknown_5d4c00(unknown_40);
                    if (distance > stray
                        || (unit->unknown_slot108() < 0 && Script->Get_Next_Mission().Mission != 3)
                        || (unit->Kind_Of() == 2 && unit->unknown_slot110() > 0
                            && &Map[unit->Center_Coord()] != unknown_40
                            && Script->Get_Next_Mission().Mission != 3)) {
                        if (Class->Aggressive && unit->unknown_228 != 0) {
                            continue;
                        }
                        if (unit->unknown_slot91() != 2) {
                            unit->unknown_slot116(2, false);
                            if (unit->unknown_slot122()) {
                                unit->unknown_slot117();
                            }
                        }
                        if (unit->unknown_494 == 0) {
                            unit->unknown_slot260(unknown_40, 1);
                        }
                        AbstractClass *navcom = unit->unknown_494;
                        if (navcom != unknown_40) {
                            if (unit->unknown_slot32()->BalloonHover
                                || (navcom != unknown_40 && unit->Kind_Of() == 2 && navcom == unit->unknown_slot105())) {
                                unit->unknown_slot260(unknown_40, 1);
                            }
                        }
                        finished = false;
                    } else {
                        if (unit->unknown_slot91() == 2
                            && (unit->unknown_494 == 0
                                || (unit->unknown_5d4c00(unit->unknown_494) <= Rules->unknown_1380 && !unit->Locomotor.Checked()->Is_Moving()))
                            && unit->unknown_228 == 0) {
                            unit->unknown_slot260(0, 1);
                            unit->unknown_slot261(false, true);
                        }
                    }
                    bool arrived = unit->Kind_Of() == 2 && unit->unknown_494 == unit->unknown_slot105();
                    bool hovering = unit->AbstractFlags.IsTechno && unit->unknown_slot32()->BalloonHover && distance < stray;
                    if (unit->unknown_494 != 0 && !arrived && !hovering) {
                        finished = false;
                    }
                }
            }
        } else {
            finished = false;
        }
    }
    if (!found) {
        finished = false;
    }
    if (finished && IsMoving) {
        StepCompleted = true;
    }
}
