// bool MPCooperative::unknown_slot39(DynamicVectorClass<int> unknown_list, int *unknown_result) -- 0x005A6230
// Clears the result; true while a campaign exists.
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

bool MPCooperative::unknown_slot39(DynamicVectorClass<int> unknown_list, int *unknown_result)
{
    *unknown_result = 0;
    if (unknown_campaign_44 != 0) {
        return true;
    }
    return false;
}
