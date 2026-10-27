// AnimClass::AnimClass() (0x004208E0)
// An empty animation (no type) registered in Anims.
#include "shared/anim.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ??0UnknownQuaternion@@QAE@MMMM@Z=00622160
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?Frame@@3HA=00a40d2c
// @ref ??_7AnimClass@@6BIPersistStream@@@=0079c084
// @ref ??_7AnimClass@@6BIRTTITypeInfo@@@=0079c068
// @ref ??_7AnimClass@@6BINoticeSink@@@=0079c060
// @ref ??_7AnimClass@@6BINoticeSource@@@=0079c058

AnimClass::AnimClass() :
    Class(0),
    unknown_b4(0),
    unknown_b8(-1),
    unknown_bc(0),
    unknown_c0(-1),
    unknown_e4(1000),
    ZAdjust(0),
    YSortAdjust(0),
    unknown_100(false),
    unknown_101(false),
    unknown_102(false),
    unknown_103(false),
    unknown_104(0),
    unknown_138(0.0f, 0.0f, 0.0f, 1.0f),
    unknown_148(0.0f, 0.0f, 0.0f, 1.0f),
    unknown_159(false),
    LoopDelay(0),
    unknown_168(0),
    unknown_174(false),
    Loops(1),
    unknown_176(false),
    unknown_177(false),
    unknown_17b(false),
    unknown_17c(true),
    unknown_17d(false),
    unknown_17e(false)
{
    Anims.Add(this);
    unknown_180.Init();
    unknown_194.Init();
    unknown_7d = true;
}
