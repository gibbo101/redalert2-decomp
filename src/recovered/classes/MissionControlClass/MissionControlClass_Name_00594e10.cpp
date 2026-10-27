// char const *MissionControlClass::Name() const (0x00594E10): "<none>" for -1.
#include "shared/mission.hpp"
// @ref ?MissionNames@@3PAPBDA=007cd774
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc

char const *MissionControlClass::Name() const
{
    if (Mission == -1) {
        return "<none>";
    }
    return MissionNames[Mission];
}
