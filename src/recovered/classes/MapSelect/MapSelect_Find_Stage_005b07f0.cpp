// MapStage *MapSelect::Find_Stage(Wstring const &name) const (0x005B07F0)
// Stage whose Name matches, ignoring case; null when absent.
#include "shared/ms_choice.hpp"
// @ref ?To_Lower@Wstring@@QAEXXZ=0076ee20

MapStage *MapSelect::Find_Stage(Wstring const &name) const
{
    if (name != 0) {
        for (int index = 0; index < Stages.Count(); index++) {
            Wstring wanted(name);
            wanted.To_Lower();
            Wstring stage(Stages[index]->Name);
            stage.To_Lower();
            if (wanted == stage) {
                return Stages[index];
            }
        }
    }
    return 0;
}
