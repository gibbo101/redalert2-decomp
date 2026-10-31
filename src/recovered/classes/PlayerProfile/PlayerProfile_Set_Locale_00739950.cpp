#include "shared/player_profile.hpp"
void PlayerProfile::Set_Locale_00739950(int locale, int source)
{
    bool permitted;
    if (locale == unknown_10) {
        if (source == 2 && !Verified) {
            Verified = true;
            unknown_08 = true;
            return;
        }
    } else {
        permitted = source >= unknown_18;
        if (unknown_10 == 0) permitted = true;
        else if (!permitted) return;
        if (locale != 0 && permitted) {
            if (source == 3) Verified = false;
            unknown_10 = locale;
            unknown_18 = source;
            unknown_08 = true;
        }
    }
}
