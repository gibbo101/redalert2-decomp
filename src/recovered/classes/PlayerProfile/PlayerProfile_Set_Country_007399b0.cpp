#include "shared/player_profile.hpp"
unsigned int PlayerProfile::Set_Country_007399b0(unsigned int country)
{
    if (country != (unsigned int)Country) {
        Country = country;
        unknown_08 = true;
    }
    return country;
}
