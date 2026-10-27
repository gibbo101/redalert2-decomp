// void __fastcall TagClass::unknown_func_6b4220(int value) (0x006B4220)
// Passes value to the first trigger of every tag.
#include "shared/object.hpp"

void __fastcall TagClass::unknown_func_6b4220(int value)
{
    for (int index = 0; index < unknown_TagClass_list_00abfe48.Count(); index++) {
        unknown_TagClass_list_00abfe48[index]->AttachedTrigger->unknown_func_6ed620(value);
    }
}
