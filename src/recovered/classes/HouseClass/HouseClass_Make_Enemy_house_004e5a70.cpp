// void HouseClass::Make_Enemy(HouseClass *house, bool announce) (0x004E5A70)
// Ends an alliance (TS's Make_Enemy). Outside the campaign passive houses
// never change. The anger at the house rises; when it was an ally the
// alliance is dropped on both sides (each side's bits and +0x4F3420), the
// player's own house in a multiplayer game shows "TXT_AT_WAR", and with
// announce EVA reports the broken alliance when the player controls a side.
// The allied view is refreshed around it (0x0049E000 / 0x0049DE00).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/string_table.hpp"
#include "shared/uicmnds.hpp"
#include "shared/vox_class.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_func_4f3420@HouseClass@@QAEXXZ=004f3420
// @ref ?Unknown_00715B40@@YIHPBDHH@Z=00715b40
// @ref __real@8@4008e100000000000000=0079b608
// @ref ??_C@_0L@JHHB@TXT_AT_WAR?$AA@=007da34c
// @ref ??_C@_0BD@IDCM@EVA_AllianceBroken?$AA@=007da338

void HouseClass::Make_Enemy(HouseClass *house, bool announce)
{
    bool broken = false;
    if (unknown_game_mode_a3d298 != 0 && (house->Type->MultiplayPassive || Type->MultiplayPassive)) {
        return;
    }
    Map.Unknown_0049E000(false, false);
    unknown_func_4eeba0(1, house);
    if (Is_Ally(house)) {
        Allies &= ~(1 << house->ArrayIndex);
        if (unknown_a40774) {
            unknown_120 &= !(1 << house->ArrayIndex);
        }
        unknown_func_4f3420();
        if (house->Is_Ally(this)) {
            house->Allies &= ~(1 << ArrayIndex);
            broken = true;
            if (unknown_a40774) {
                unknown_120 &= ~(1 << ArrayIndex);
            }
            house->unknown_func_4f3420();
            house->unknown_func_4eeba0(1, house);
        }
        if (unknown_game_mode_a3d298 != 0 && !unknown_a40774 && unknown_134) {
            wchar_t buffer[80];
            swprintf(buffer, StringTable::Load_String("TXT_AT_WAR", 0, "D:\\Ra2\\House.CPP", 3272), UIName, house->UIName);
            unknown_messages_a3dc70.Add_Message(0, 0, buffer, Type->Color, 0x4046, (int)(Rules->MessageDelay * 900.0), 0);
            Map.Flag_To_Redraw(false);
            if (announce && broken && (Is_Player_Control() || house->Is_Player_Control())) {
                Unknown_00715B40("EVA_AllianceBroken", -1, -1);
            }
        }
    }
    Map.Unknown_0049DE00(false, false);
}
