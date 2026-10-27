// void __fastcall AudioCountedList::Enter() -- 0x00401F80
// Purpose: counts one more user changing the list.
#include "shared/audio.hpp"

void __fastcall AudioCountedList::Enter()
{
    Busy++;
}
