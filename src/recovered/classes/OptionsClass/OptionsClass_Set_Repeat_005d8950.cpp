// void OptionsClass::Set_Repeat(bool on) (0x005D8950)
// @ref ??_C@_02HAKO@ON?$AA@=007e1f40
// @ref ??_C@_03CMJG@OFF?$AA@=007e1f3c
// @ref ??_C@_0BD@OCJK@ScoreRepeat?5is?5?$CFs?6?$AA@=007e8688
#include "shared/options.hpp"
#include "shared/debug_printf.hpp"
#include "shared/theme.hpp"
#include "shared/audio.hpp"
#include "shared/rules.hpp"
#include "shared/techno.hpp"
#include "shared/vox_class.hpp"

void OptionsClass::Set_Repeat(bool on)
{
    IsScoreRepeat = on;
    Theme.IsRepeat = on;
    Debug_Printf("ScoreRepeat is %s\n", IsScoreRepeat == true ? "ON" : "OFF");
}
