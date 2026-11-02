// PacketField *PacketClass::Find_Field(char const *id) (0x00602CD0; was UnknownChunkList_602cd0::Find): the first field whose four-character ID matches.
#include "shared/packet.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/crt_memory.hpp"
// @ref _strncmp=00783810
extern "C" int __cdecl strncmp(char const *left, char const *right, unsigned int count);

PacketField_004BAD50 *PacketClass::Find_Field(char const *id)
{
    for (PacketField_004BAD50 *current = Head; current; current = current->Next) {
        if (strncmp(id, current->Name, 4) == 0) {
            return current;
        }
    }
    return 0;
}
