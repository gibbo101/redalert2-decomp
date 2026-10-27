#include "shared/command.hpp"
// Tests modified-key acceptance through the existing CommandClass slot5 predicate.
bool __fastcall Command_Allows_Modified_Key_00480b20(CommandClass const &command,unsigned int key)
{
    key &= 0xfffff7ff; // remove the key-release flag
    if (key!=(key & 0xffffe8ff)) return !command.unknown_slot5(key);
    return true;
}
