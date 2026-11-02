// PacketClass::~PacketClass() -- 00602A60, complete41+7 original bytes.
// @ref ??1PacketField_004BAD50@@QAE@XZ=004bb060
// @ref ??3@YAXPAX@Z=00781d3b
#include "shared/packet.hpp"
PacketClass::~PacketClass()
{
    PacketField_004BAD50 *node = Head;
    while (node != 0) {
        PacketField_004BAD50 *next = node->Next;
        delete node;
        node = next;
    }
}
