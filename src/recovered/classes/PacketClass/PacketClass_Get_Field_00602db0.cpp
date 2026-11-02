// bool PacketClass::Get_Field(char const *id, short &data) (0x00602DB0; the inventory row starts at 0x00602DB2).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

bool PacketClass::Get_Field(char const *id, short &data)
{
    PacketField_004BAD50 *field = Find_Field(id);
    if (field) {
        data = *((short *)field->Data);
    }
    return (field) ? true : false;
}
