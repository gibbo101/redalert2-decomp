// int TechnoClass::unknown_6d6750() (0x006D6750)
// The ID plus unknown_1e0, modulo 400.
#include "shared/techno.hpp"

int TechnoClass::unknown_6d6750()
{
    return (Fetch_ID() + (int)unknown_1e0) % 400;
}
