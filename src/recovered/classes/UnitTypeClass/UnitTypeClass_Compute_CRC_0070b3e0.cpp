// void UnitTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x0070B3E0)
#include "shared/unit_type.hpp"
// @ref ?Compute_CRC@TechnoTypeClass@@UBEXAAVWWCRCEngine@@@Z=006defd0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void UnitTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    TechnoTypeClass::Compute_CRC(crc);
    crc((long)MovementRestrictedTo);
    crc(Passive);
    crc(CrateGoodie);
    crc(Harvester);
    crc(Weeder);
    crc(unknown_ba8);
    crc(unknown_ba9);
    crc(IsTilter);
    crc(IsSimpleDeployer);
    crc(UseTurretShadow);
}
