// void TeamClass::AI() (0x006B7AD0; slot 23): Red Alert's/TS TeamClass::AI. Waits out a suspension,
// recalculates the strength flags after the roster changed, regroups or flags the team into action,
// recalculates its center, recruits, disbands an empty team (springing the leaves-map tags first),
// then advances and runs the script step (the handlers below; VC6 expands the small ones) or
// coordinates the regroup or the move.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/tag.hpp"
#include "shared/scenario_tags.hpp"
#include "shared/map_view.hpp"
#include "shared/theme.hpp"
#include "shared/debug_printf.hpp"
// @ref _unknown_geometry_k=00ac0050
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ??_C@_0DN@LCAF@A?5Transport?5just?5recieved?5orders@=007f6dc4

// @ref ?TMission_unknown_6bb5f0@TeamClass@@QAEXABVScriptMissionClass@@_N@Z=006bb5f0
// @ref ?TMission_unknown_6bcbb0@TeamClass@@QAEXABVScriptMissionClass@@_N@Z=006bcbb0
// @ref ?TMission_unknown_6bdaa0@TeamClass@@QAEXABVScriptMissionClass@@_N@Z=006bdaa0
// @ref ?TMission_unknown_6be010@TeamClass@@QAEXABVScriptMissionClass@@_N@Z=006be010
// @ref ?TMission_unknown_6be440@TeamClass@@QAEXABVScriptMissionClass@@_N@Z=006be440

// CDTimerClass::Value() for the timer type whose class is not recovered.
inline long Timer_Value(UnknownTimer423F60 const &timer)
{
    long remain = timer.DelayTime;
    if (timer.Started != -1) {
        long value = timer.Timer - timer.Started;
        if (value < remain) {
            return remain - value;
        } else {
            return 0;
        }
    }
    return remain;
}

void TeamClass::AI()
{
    if (IsLeavingMap) {
        if (Timer_Value(unknown_64) != 0) {
            return;
        }
        IsLeavingMap = false;
    }
    if (NeedsToDisappear) {
        if (!unknown_func_6b8bb0()) {
            return;
        }
    }
    if (IsMoving && IsUnderStrength) {
        unknown_func_6b88b0();
    }
    if (!IsMoving && (IsFullStrength || IsForcedActive)) {
        unknown_func_6b8860();
    }
    if (IsReforming || IsMoving || unknown_34 == 0 || unknown_38 == 0) {
        unknown_func_6b9610(&unknown_34, &unknown_38);
    }
    if ((!IsMoving || (!IsFullStrength && Class->Reinforce)) && (!Owner->Unknown_004F52F0() || !IsHasBeen)) {
        for (int index = 0; index < Class->TaskForce->CountEntries; index++) {
            if (unknown_84[index] < Class->TaskForce->Entries[index].Amount) {
                unknown_func_6b91c0(index);
            }
        }
    }
    if (Member == 0 && (IsHasBeen || (unknown_game_mode_a3d298 != 0 && Frame - unknown_50 > Rules->DissolveUnfilledTeamDelay))) {
        if (TargetNotAssigned) {
            for (int index = 0; index < unknown_tags_866160.Count(); index++) {
                TagClass *tag = unknown_tags_866160[index];
                if (tag->Spring(0x17, 0, unknown_geometry_k)) {
                    index--;
                    if (unknown_tags_866160.Count() == 0) {
                        break;
                    }
                }
            }
        }
        delete this;
        return;
    }
    bool leaving = Member != 0 && Member->unknown_slot112();
    if (IsMoving && !IsReforming && !IsUnderStrength && !leaving) {
        bool is_next = false;
        if (StepCompleted) {
            is_next = true;
            StepCompleted = false;
            Script->Next_Mission();
            for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
                if (Class->TransportsReturnOnUnload && member->unknown_slot32()->Passengers > 0) {
                    if (member->unknown_1b0 != 0) {
                        Debug_Printf("A Transport just recieved orders to go home after unloading\n");
                    }
                } else {
                    member->unknown_6d6e50(0);
                }
            }
            if (Script->Has_Mission()) {
                unknown_func_6b79e0(0);
                unknown_40 = 0;
            } else {
                delete this;
                return;
            }
        }
        if (!is_next) {
            if (unknown_40 == 0) {
                unknown_40 = unknown_3c;
            }
        }
        ScriptMissionClass mission = Script->Get_Current_Mission();
        switch (mission.Mission) {
        case 0x2C: TMission_unknown_6bc5f0(mission, is_next); break;
        case 0x18: TMission_unknown_6bc250(mission, is_next); break;
        case 0x2D: TMission_unknown_6bc660(mission, is_next); break;
        case 0x26: TMission_unknown_6bbe90(mission, is_next); break;
        case 0x25: TMission_unknown_6bc410(mission, is_next); break;
        case 0x16: TMission_unknown_6badc0(mission, is_next); break;
        case 0x04: TMission_unknown_6bae00(mission, is_next); break;
        case 0x03: TMission_unknown_6bae60(mission, is_next); break;
        case 0x01: TMission_unknown_6bb020(mission, is_next); break;
        case 0x10: TMission_unknown_6bb0f0(mission, is_next); break;
        case 0x0F: TMission_unknown_6bb260(mission, is_next); break;
        case 0x15: TMission_unknown_6bb310(mission, is_next); break;
        case 0x14: TMission_unknown_6bb350(mission, is_next); break;
        case 0x12: TMission_unknown_6bb3b0(mission, is_next); break;
        case 0x11: TMission_unknown_6bb420(mission, is_next); break;
        case 0x00: TMission_unknown_6bb480(mission, is_next); break;
        case 0x0E: TMission_unknown_6bb5f0(mission, is_next); break;
        case 0x09: TMission_unknown_6bb8b0(mission, is_next); break;
        case 0x05: TMission_unknown_6bbb40(mission, is_next); break;
        case 0x0B: TMission_unknown_6bbbb0(mission, is_next); break;
        case 0x0C: TMission_unknown_6bbe60(mission, is_next); break;
        case 0x0A: TMission_unknown_6bbf20(mission, is_next); break;
        case 0x13: TMission_unknown_6bc130(mission, is_next); break;
        case 0x0D: TMission_unknown_6bc190(mission, is_next); break;
        case 0x06: TMission_unknown_6bc1e0(mission, is_next); break;
        case 0x07:
            unknown_player_a35db4->Flag_To_Win(false);
            StepCompleted = true;
            break;
        case 0x17:
            unknown_player_a35db4->Flag_To_Lose(false);
            StepCompleted = true;
            break;
        case 0x19: TMission_unknown_6bc260(mission, is_next); break;
        case 0x1A: TMission_unknown_6bc290(mission, is_next); break;
        case 0x1B:
            Theme.Queue_Song((ThemeType)mission.Data);
            StepCompleted = true;
            break;
        case 0x1C: TMission_unknown_6bc2e0(mission, is_next); break;
        case 0x1D: TMission_unknown_6bc360(mission, is_next); break;
        case 0x1E: TMission_unknown_6bc380(mission, is_next); break;
        case 0x1F: TMission_unknown_6bc3a0(mission, is_next); break;
        case 0x20: TMission_unknown_6bc460(mission, is_next); break;
        case 0x21: TMission_unknown_6bc4a0(mission, is_next); break;
        case 0x22: TMission_unknown_6bc4c0(mission, is_next); break;
        case 0x23:
            Map.Unknown_00559FD0();
            StepCompleted = true;
            break;
        case 0x24:
            Map.Unknown_0055A1F0();
            StepCompleted = true;
            break;
        case 0x27: TMission_unknown_6bbec0(mission, is_next); break;
        case 0x28: TMission_unknown_6bbef0(mission, is_next); break;
        case 0x29: TMission_unknown_6bc040(mission, is_next); break;
        case 0x2A: TMission_unknown_6bc070(mission, is_next); break;
        case 0x2B: TMission_unknown_6bc5b0(mission, is_next); break;
        case 0x2E: TMission_unknown_6bc6d0(mission, is_next); break;
        case 0x2F: TMission_unknown_6bc7b0(mission, is_next); break;
        case 0x3A: TMission_unknown_6bc980(mission, is_next); break;
        case 0x30: TMission_unknown_6bcbb0(mission, is_next); break;
        case 0x08: TMission_unknown_6bd4b0(mission, is_next); break;
        case 0x31: TMission_unknown_6bd7f0(mission, is_next); break;
        case 0x32:
            if (is_next) {
                unknown_func_6bd990(mission.Data);
                StepCompleted = true;
            }
            break;
        case 0x33: TMission_unknown_6bd9b0(mission, is_next); break;
        case 0x34: TMission_unknown_6bda70(mission, is_next); break;
        case 0x35: TMission_unknown_6bdaa0(mission, is_next); break;
        case 0x36: TMission_unknown_6bddb0(mission, is_next); break;
        case 0x37: TMission_unknown_6be010(mission, is_next); break;
        case 0x38: TMission_unknown_6be1c0(mission, is_next); break;
        case 0x39: TMission_unknown_6be440(mission, is_next); break;
        default:
            break;
        }
    } else {
        if (IsMoving) {
            IsReforming = !unknown_func_6b9f40();
        } else {
            unknown_func_6ba1a0();
        }
    }
}
