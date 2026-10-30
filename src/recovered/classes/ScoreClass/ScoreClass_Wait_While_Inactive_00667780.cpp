// void ScoreClass::Wait_While_Inactive() (0x00667780)
// While the game window is inactive: pauses every animation, idles until
// it is active again, then resumes them (ScoreDelay inlines it).
#include "shared/score.hpp"
#include "shared/ms_engine.hpp"
#include "shared/win32_api.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref ?unknown_5b5ee0@@YAXXZ=005b5ee0
// @ref __imp__Sleep@4=0079a1e4

void ScoreClass::Wait_While_Inactive()
{
    if (unknown_flag_a40d28 != true) {
        for (int index = 0; index < Anims.Count(); index++) {
            Anims[index]->Pause();
        }
        while (!unknown_flag_a40d28) {
            Sleep(500);
            unknown_5b5ee0();
        }
        for (int index2 = 0; index2 < Anims.Count(); index2++) {
            Anims[index2]->Resume();
        }
    }
}
