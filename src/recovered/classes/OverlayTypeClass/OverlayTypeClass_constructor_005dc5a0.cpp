// OverlayTypeClass::OverlayTypeClass(char const *ini_name) (0x005DC5A0)
// Default overlay values, then registration in OverlayTypes.
#include "shared/overlay_type.hpp"
// @ref ??0ObjectTypeClass@@QAE@PBD@Z=005d57f0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ??_7OverlayTypeClass@@6BIPersistStream@@@=007a7a08
// @ref ??_7OverlayTypeClass@@6BIRTTITypeInfo@@@=007a79ec
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ??_7OverlayTypeClass@@6BINoticeSink@@@=007a79e4
// @ref ??_7OverlayTypeClass@@6BINoticeSource@@@=007a79dc

OverlayTypeClass::OverlayTypeClass(char const *ini_name) :
    ObjectTypeClass(ini_name),
    ArrayIndex(-1),
    Land(0),
    CellAnim(0),
    DamageLevels(1),
    Strength(1),
    Wall(false),
    Tiberium(false),
    Crate(false),
    CrateTrigger(false),
    NoUseTileLandType(true),
    IsVeinholeMonster(false),
    IsVeins(false),
    DemandLoad(false),
    Explodes(false),
    ChainReaction(false),
    Overrides(false),
    DrawFlat(true),
    IsRubble(false),
    IsARock(false)
{
    AbstractClass::Create_ID();
    unknown_1ff = true;
    unknown_200 = false;
    unknown_202 = true;
    unknown_205 = false;
    OverlayTypes.Add(this);
    ArrayIndex = OverlayTypes.ID(this);
}
