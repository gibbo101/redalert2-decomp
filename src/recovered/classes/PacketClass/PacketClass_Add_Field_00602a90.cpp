// PacketClass::Add_Field() -- 00602A90, complete16+0 original bytes.
#include "shared/packet.hpp"
void PacketClass::Add_Field(PacketField_004BAD50 *field)
{
    field->Next = Head;
    Head = field;
}
