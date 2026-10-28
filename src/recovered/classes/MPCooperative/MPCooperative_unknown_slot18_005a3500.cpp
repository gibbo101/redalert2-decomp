// bool MPCooperative::unknown_slot18(int index, DynamicVectorClass<int> choices, char const *second_name, char const *first_name) -- 0x005A3500
// Makes the campaign when there is none, then stores the campaign information for the record index
// (a changed campaign type marks the side combos for a refresh).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_E?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"

bool MPCooperative::unknown_slot18(int index, DynamicVectorClass<int> choices, char const *second_name, char const *first_name)
{
    if (unknown_campaign_44 == 0) {
        Unknown_005A4F20();
        unknown_344 = true;
    }
    if (unknown_campaign_44 != 0 && unknown_campaigns_40 != 0) {
        int type;
        unknown_campaign_44->Get_Campaign_Type_0048e6b0(&type);
        if (type != index) {
            unknown_344 = true;
        }
        unknown_campaign_44->Set_Campaign_Info_0048f7d0(*unknown_campaigns_40, index, choices, second_name, first_name);
        unknown_340 = index;
        return true;
    }
    return false;
}
