// void PacketClass::Add_Field(PacketField *field) (0x00602A90): pushes the field on the list head.
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

void PacketClass::Add_Field(PacketField_004BAD50 *field)
{
    field->Next = Head;
    Head = field;
}
