// void InfantryTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x0050AA20)
#include "shared/infantry_type.hpp"
// @ref ?Compute_CRC@TechnoTypeClass@@UBEXAAVWWCRCEngine@@@Z=006defd0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEJPBXH@Z=00493fc0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void InfantryTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    TechnoTypeClass::Compute_CRC(crc);
    crc((long)Pip);
    crc(DoControls, 38 * sizeof(DoInfoStruct));
    crc((long)FireUp);
    crc((long)FireProne);
    crc((long)VoiceComment.Count());
    crc((long)DeadBodies.Count());
    crc((long)DeathAnims.Count());
    crc(Fearless);
    crc(Crawls);
    crc(Infiltrate);
    crc(Fraidycat);
    crc(TiberiumProof);
    crc(Civilian);
    crc(C4);
    crc(Engineer);
    crc(Agent);
    crc(Thief);
    crc(VehicleThief);
}
