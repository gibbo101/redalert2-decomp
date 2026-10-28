// bool MPCooperative::unknown_slot7(int country) -- 0x005A2CD0
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/house_type.hpp"
// @ref ?Find_Country_Index_004904A0@@YIHPBD@Z=004904a0

bool MPCooperative::unknown_slot7(int country)
{
    if (unknown_campaigns_40 == 0) {
        return true;
    }
    UnknownDescriptionRecord_00490E00 *record;
    unknown_campaigns_40->Get_Record_00490C50(unknown_340, &record);
    if (record == 0) {
        return true;
    }
    bool found = false;
    if (country == -2) {
        if (record->Players.Count() > 1) {
            return true;
        }
    } else if (country == -3) {
        return true;
    }
    for (int i = 0; i < record->Players.Count(); i++) {
        if (Find_Country_Index_004904A0(record->Players[i]) == country) {
            found = true;
            break;
        }
    }
    return found;
}
