// MapStage *MapSelectData::Get_Stage(unsigned short index) const (0x005B0950)
#include "shared/ms_choice.hpp"

MapStage *MapSelectData::Get_Stage(unsigned short index) const
{
    if (Stages.Count() <= index) {
        return 0;
    }
    return Stages[index];
}
