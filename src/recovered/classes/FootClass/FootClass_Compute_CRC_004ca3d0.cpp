// void FootClass::Compute_CRC(WWCRCEngine &crc) const (0x004CA3D0)
// Hashes the movement state: distances as lengths, timers by their
// remaining time, the referenced objects by ID.
#include "shared/foot.hpp"
// @ref ?Compute_CRC@TechnoClass@@UBEXAAVWWCRCEngine@@@Z=006d6aa0
// @ref ??RWWCRCEngine@@QAEXD@Z=00493df0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXF@Z=00493f10
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70

void FootClass::Compute_CRC(WWCRCEngine &crc) const
{
    TechnoClass::Compute_CRC(crc);
    crc(unknown_428);
    crc((short)Short_Length(unknown_450.X, unknown_450.Y));
    crc((long)Coord_Length(unknown_45c));
    crc(unknown_468);
    crc(unknown_470);
    if (unknown_494 != 0) {
        crc(unknown_494->Fetch_ID());
    }
    if (unknown_498 != 0) {
        crc(unknown_498->Fetch_ID());
    }
    if (Team != 0) {
        crc(Team->Fetch_ID());
    }
    if (unknown_4c8 != 0) {
        crc(unknown_4c8->Fetch_ID());
    }
    crc(unknown_530.Value());
    crc((long)unknown_53c);
    crc(unknown_540.Value());
    crc((long)Coord_Length(unknown_568));
    crc((char)unknown_574);
    crc((char)unknown_575);
    crc(unknown_578);
    crc(unknown_579);
    crc(unknown_57a);
    crc(unknown_57b);
    crc(unknown_57c);
    crc(unknown_57d);
    crc(unknown_599);
    crc(unknown_59a);
    crc(unknown_59b);
    crc(unknown_59c);
    crc(unknown_59d);
    crc((char)unknown_59e);
}
