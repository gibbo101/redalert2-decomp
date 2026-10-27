// ObjectTypeClass *VeinholeMonsterClass::Class_Of() const (0x007122F0, slot 33)
// The type named by the rules (+0xCB4).
#include "shared/veinhole.hpp"
#include "shared/terrain_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

ObjectTypeClass *VeinholeMonsterClass::Class_Of() const
{
    return Rules->unknown_cb4;
}
