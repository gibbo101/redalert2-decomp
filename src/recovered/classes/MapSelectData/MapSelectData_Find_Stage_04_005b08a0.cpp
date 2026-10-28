// MapStage *MapSelectData::Find_Stage_04(Wstring const &name) const (0x005B08A0)
// As Find_Stage, matching the stage's scenario name (Scenario).
#include "shared/ms_choice.hpp"
// @ref ?To_Lower@Wstring@@QAEXXZ=0076ee20

MapStage *MapSelectData::Find_Stage_04(Wstring const &name) const
{
    if (name != 0) {
        for (int index = 0; index < Stages.Count(); index++) {
            Wstring wanted(name);
            wanted.To_Lower();
            Wstring stage(Stages[index]->Scenario);
            stage.To_Lower();
            if (wanted == stage) {
                return Stages[index];
            }
        }
    }
    return 0;
}
