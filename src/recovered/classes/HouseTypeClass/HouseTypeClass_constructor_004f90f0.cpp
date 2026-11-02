// HouseTypeClass::HouseTypeClass(char const *ini_name) (0x004F90F0)
// Defaults (no side, multipliers 1.0, prefix 'A', owns walls), then
// registration in HouseTypes; House and ArrayIndex are both its index there.
#include "shared/house_type.hpp"

HouseTypeClass::HouseTypeClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    ArrayIndex(-1),
    House(-1),
    Side(-1),
    Color(0),
    FirepowerMult(1.0),
    GroundspeedMult(1.0),
    AirspeedMult(1.0),
    ArmorMult(1.0),
    ROFMult(1.0),
    CostMult(1.0),
    BuildtimeMult(1.0),
    unknown_0x100(1.0f),
    unknown_0x104(1.0f),
    unknown_0x108(1.0f),
    unknown_0x10C(1.0f),
    unknown_0x110(1.0f),
    unknown_0x114(1.0f),
    unknown_0x118(1.0f),
    unknown_0x11C(1.0f),
    unknown_0x120(1.0f),
    unknown_0x124(1.0f),
    unknown_0x128(1.0f),
    unknown_0x12C(1.0f),
    unknown_0x130(1.0f),
    unknown_0x134(1.0f),
    unknown_0x138(1.0f),
    unknown_0x13C(1.0f),
    unknown_0x140(1.0f),
    unknown_0x144(1.0f),
    unknown_0x148(1.0f),
    Prefix('A'),
    Multiplay(false),
    MultiplayPassive(false),
    WallOwner(true),
    SmartAI(false)
{
    AbstractClass::Create_ID();
    Suffix[0] = '\0';
    HouseTypes.Add(this);
    House = HouseTypes.ID(this);
    ArrayIndex = HouseTypes.ID(this);
}
