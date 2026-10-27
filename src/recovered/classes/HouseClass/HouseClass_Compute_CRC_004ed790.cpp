// void HouseClass::Compute_CRC(WWCRCEngine &crc) const (0x004ED790)
// Checksums the abstract part and the house's counters, doubles, flags and timers, then the base plan.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/house_type.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ?Compute_CRC@BaseClass@@UBEXAAVWWCRCEngine@@@Z=0042c9f0
// @ref ?Frame@@3HA=00a40d2c

void HouseClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc((long)unknown_c8);
    crc((long)Type->House);
    crc(unknown_d0);
    crc(unknown_d8);
    crc(unknown_e0);
    crc(unknown_e8);
    crc(unknown_f0);
    crc(unknown_f8);
    crc(unknown_100);
    crc(unknown_108);
    crc(unknown_110);
    crc(unknown_134);
    crc(unknown_136);
    crc(unknown_137);
    crc(unknown_13a);
    crc(unknown_13d);
    crc((long)unknown_194);
    crc((long)unknown_198);
    crc((long)unknown_1c4);
    crc(unknown_1c8.Value());
    crc(unknown_1d4.Value());
    crc(unknown_1e0.Value());
    crc((long)unknown_228);
    crc((long)CurBuildings);
    crc((long)unknown_234);
    crc((long)unknown_238);
    crc((long)Balance);
    crc((long)Capacity);
    crc((long)unknown_52b8);
    crc((long)unknown_52bc);
    crc((long)unknown_52c0);
    crc((long)unknown_52c8);
    crc((long)unknown_52c4);
    crc((long)unknown_52cc);
    crc((long)Power);
    crc((long)Drain);
    crc((long)unknown_53b8);
    crc((long)unknown_54f0);
    unknown_55f0.Compute_CRC(crc);
}
