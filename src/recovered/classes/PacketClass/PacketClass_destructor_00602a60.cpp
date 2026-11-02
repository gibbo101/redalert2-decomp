// PacketClass::~PacketClass() (0x00602A60): deletes every field.
// Packet.cpp (0x00602A60-0x00602FD0; Tiberian Sun packet.cpp bodies). The field type is
// shared/packet_field.hpp's PacketField_004BAD50; Find_Field and five Get_Field overloads are declared for
// this unit only (RA2_PACKET_UNIT).
#define RA2_PACKET_UNIT
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"
// @ref ??1PacketField_004BAD50@@QAE@XZ=004bb060

PacketClass::~PacketClass()
{
    PacketField_004BAD50 *node = Head;
    while (node != 0) {
        PacketField_004BAD50 *next = node->Next;
        delete node;
        node = next;
    }
}
