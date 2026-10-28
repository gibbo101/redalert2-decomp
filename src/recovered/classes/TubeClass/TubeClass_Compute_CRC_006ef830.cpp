// void TubeClass::Compute_CRC(WWCRCEngine &crc) const (0x006EF830)
#include "shared/tube.hpp"
#include "shared/wwcrc_engine.hpp"

void TubeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc(EnterCell.X);
    crc(EnterCell.Y);
    crc(ExitCell.X);
    crc(ExitCell.Y);
    crc((long)Facing);
    for (int index = 0; index < 100; index++) {
        crc((long)Directions[index]);
    }
    crc((long)unknown_1c0);
}
