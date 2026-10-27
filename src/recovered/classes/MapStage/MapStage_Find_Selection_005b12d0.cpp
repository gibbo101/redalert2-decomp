// MapSelection *MapStage::Find_Selection(char const *name) const (0x005B12D0)
// Selection of that name, ignoring case; null when absent.
#include "shared/ms_choice.hpp"
// @ref ?To_Lower@Wstring@@QAEXXZ=0076ee20

MapSelection *MapStage::Find_Selection(char const *name) const
{
    Wstring wanted(name);
    wanted.To_Lower();
    for (int index = 0; index < Selections.Count(); index++) {
        if (Selections[index]->Name != 0) {
            Wstring selection(Selections[index]->Name);
            selection.To_Lower();
            if (wanted == selection) {
                return Selections[index];
            }
        }
    }
    return 0;
}
