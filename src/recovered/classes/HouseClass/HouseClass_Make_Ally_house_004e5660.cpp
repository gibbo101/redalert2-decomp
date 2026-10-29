// void HouseClass::Make_Ally(HouseClass *house, bool announce) (0x004E5660)
// RA's Make_Ally: when the alliance is allowed the house's bit is set, the
// threat map rebuilt and the anger at the house forgotten (0x004F33E0); it
// stops being the enemy. Outside a network replay (or in game mode 4) a
// paranoid human house makes the computers paranoid, this house's objects drop
// targets that are now allies, and a human house outside the campaign shows
// "TXT_HAS_ALLIED" and, with announce, plays the EVA alliance speech.
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/string_table.hpp"
#include "shared/uicmnds.hpp"
#include "shared/vox_class.hpp"
#include "shared/target.hpp"
#include "shared/unknown_list_832470.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
// @ref __real@8@4008e100000000000000=0079b608
// @ref ??_C@_0P@MBBL@TXT_HAS_ALLIED?$AA@=007da328
// @ref ??_C@_0BD@NECJ@EVA_AllianceFormed?$AA@=007da314
// @ref ??_C@_0BI@BEFK@EVA_EnemyAllianceFormed?$AA@=007da2fc
// @ref ??_C@_0BH@FHBI@EVA_RequestingAlliance?$AA@=007da2e4
// @ref ??_C@_0BG@GKLI@EVA_AllianceRequested?$AA@=007da2cc

void HouseClass::Make_Ally(HouseClass *house, bool announce)
{
    if (Is_Allowed_To_Ally(house)) {
        Map.Unknown_0049E000(false, false);
        Allies |= 1 << house->ArrayIndex;
        unknown_func_4f3420();
        unknown_func_4f33e0(house);
        if (unknown_54f0 == house->ArrayIndex) {
            unknown_54f0 = -1;
        }
        if (unknown_a40774) {
            unknown_120 |= 1 << house->ArrayIndex;
        }
        if (unknown_game_mode_a3d298 == 4 || !unknown_a40774) {
            if (Is_Human_Control() && Rules->Paranoid && !house->Type->MultiplayPassive && unknown_game_mode_a3d298 != 0) {
                unknown_func_4ec5e0();
            }
            for (int index = 0; index < unknown_list_832470.Count(); index++) {
                ObjectClass *object = unknown_list_832470[index];
                if (object != 0 && object->As_Techno() != 0 && !object->unknown_76 && object->Owner() == ArrayIndex) {
                    TargetClass target(((TechnoClass *)object)->unknown_228);
                    if (target.Is_Valid() && target.As_Techno() != 0) {
                        if (Is_Ally(target.As_Techno())) {
                            ((TechnoClass *)object)->unknown_slot220(0);
                        }
                    }
                }
            }
            if (Is_Human_Control() && unknown_game_mode_a3d298 != 0 && !house->Type->MultiplayPassive) {
                wchar_t buffer[80];
                swprintf(buffer, StringTable::Load_String("TXT_HAS_ALLIED", 0, "D:\\Ra2\\House.CPP", 3149), UIName, house->UIName);
                unknown_messages_a3dc70.Add_Message(0, 0, buffer, Type->Color, 0x4046, (int)(Rules->MessageDelay * 900.0), 0);
                if (announce) {
                    if (house->Is_Ally(this)) {
                        if (!unknown_int_a3d548) {
                            if (unknown_player_a35db4->Is_Ally(house) && unknown_player_a35db4->Is_Ally(this)) {
                                Speech_Play_Name("EVA_AllianceFormed", -1, -1);
                            } else {
                                Speech_Play_Name("EVA_EnemyAllianceFormed", -1, -1);
                            }
                        }
                    } else if (Is_Player_Control()) {
                        Speech_Play_Name("EVA_RequestingAlliance", -1, -1);
                    } else if (house->Is_Player_Control()) {
                        Speech_Play_Name("EVA_AllianceRequested", -1, -1);
                    }
                }
            }
            Map.Flag_To_Redraw(false);
        }
        Map.Unknown_0049DE00(false, false);
    }
}
