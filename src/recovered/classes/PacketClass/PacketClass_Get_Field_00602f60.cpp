// bool PacketClass::Get_Field(char const *id, void *data, int &length) (0x00602F60; copies at most length bytes, returns the field size in length).
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"

bool PacketClass::Get_Field(char const *id, void *data, int &length)
{
    PacketField_004BAD50 *field = Find_Field(id);
    if (field) {
        memcpy(data, field->Data, field->Length < length ? field->Length : length);
        length = (int)field->Length;
    }
    return (field) ? true : false;
}
