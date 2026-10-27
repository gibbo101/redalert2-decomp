// MapSelect::MapSelect() (0x005AFF10)
// Empty lists and the default text rectangle.
#include "shared/ms_choice.hpp"
// @ref ??_7?$DynamicVectorClass@PAVMapStage@@@@6B@=007a6ee8
// @ref ??_7?$DynamicVectorClass@PAVMSAnimEntry@@@@6B@=007a6ec8
// @ref ??_7?$DynamicVectorClass@PAVMSSfxEntry@@@@6B@=007a6ea8

MapSelect::MapSelect()
{
    Stages.Clear();
    Palette.Release();
    Anims.Clear();
}
