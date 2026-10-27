// int TechnoTypeClass::unknown_slot34() const (0x006DAD10)
// Cost scaled by the rules factor at +0x13B0 and 0.9 (meaning unknown).
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __real@8@3ffee666666666666800=007ad028
// @ref __ftol=0077f110

int TechnoTypeClass::unknown_slot34() const
{
    return (int)(Cost * Rules->unknown_13b0 * 0.9);
}
