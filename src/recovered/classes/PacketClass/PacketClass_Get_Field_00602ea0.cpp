// bool PacketClass::Get_Field(char const *id, char *data) (0x00602EA0; strcpy).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

bool PacketClass::Get_Field(char const *id, char *data)
{
    PacketField_004BAD50 *field = Find_Field(id);
    if (field) {
        strcpy(data, (char *)field->Data);
    }
    return (field) ? true : false;
}
