// int MapSelect::Stage_Index(MapStage *stage) (0x005B0970)
#include "shared/ms_choice.hpp"

int MapSelect::Stage_Index(MapStage *stage)
{
    return Stages.ID(stage);
}
