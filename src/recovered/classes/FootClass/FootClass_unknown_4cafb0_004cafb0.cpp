// double FootClass::unknown_4cafb0() const (0x004CAFB0)
#include "shared/foot.hpp"
#include "shared/team_type.hpp"

double FootClass::unknown_4cafb0() const
{
    if (Team != 0 && Team->Class->AvoidThreats) {
        return 1.0;
    }
    return unknown_428;
}
