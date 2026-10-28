// void BaseClass::Compute_CRC(WWCRCEngine &crc) const (0x0042C9F0)
// The node count, then each node's type and cell.
#include "shared/base.hpp"
#include "shared/wwcrc_engine.hpp"

void BaseClass::Compute_CRC(WWCRCEngine &crc) const
{
    crc((long)Nodes.Count());
    for (int index = 0; index < Nodes.Count(); index++) {
        crc((long)Nodes[index].Type);
        crc(Nodes[index].Cell.X);
        crc(Nodes[index].Cell.Y);
    }
}
