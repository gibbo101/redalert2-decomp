// Wstring MapStage::Selection_Name(char key) const (0x005B1380)
// Name of the selection bound to a key, or a null string.
#include "shared/ms_choice.hpp"

Wstring MapStage::Selection_Name(char key) const
{
    for (int index = 0; index < Selections.Count(); index++) {
        if (key == Selections[index]->Key) {
            return Selections[index]->Name;
        }
    }
    return Wstring((char const *)0);
}
