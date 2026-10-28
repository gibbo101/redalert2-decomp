// int MPCooperative::unknown_slot10() -- 0x005A34B0
// The country of the selected campaign record's single player entry, or -2 (none, or more than one).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/house_type.hpp"

int MPCooperative::unknown_slot10()
{
    UnknownDescriptionRecord_00490E00 *record;
    unknown_campaigns_40->Get_Record_00490C50(unknown_340, &record);
    if (record == 0) {
        return -2;
    }
    if (record->Players.Count() == 0) {
        return -2;
    }
    if (record->Players.Count() > 1) {
        return -2;
    }
    return Find_Country_Index_004904A0(record->Players[0]);
}
