// void MSEngine::Check_Focus() (0x005B3670)
// While the application is inactive: pauses every animation and sleeps in
// 500 ms steps, then resumes them.
#include "shared/ms_engine.hpp"
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref __imp__Sleep@4=0079a1e4
// @ref ??_C@_0BF@OABI@MSEngine?5?9?5Sleeping?6?$AA@=007e5d38
// @ref ??_C@_0BP@KHHC@MSEngine?5?9?5Pausing?5animations?6?$AA@=007e5d50
// @ref ??_C@_0CA@GOJB@MSEngine?5?9?5Resuming?5animations?6?$AA@=007e5d18
// @ref ?unknown_5b5ee0@@YAXXZ=005b5ee0

void MSEngine::Check_Focus()
{
    if (unknown_flag_a40d28 != true) {
        Debug_Printf("MSEngine - Pausing animations\n");
        int index;
        for (index = 0; index < Anims.Count(); index++) {
            Anims[index]->Pause();
        }
        while (!unknown_flag_a40d28) {
            Debug_Printf("MSEngine - Sleeping\n");
            Sleep(500);
            unknown_5b5ee0();
        }
        Debug_Printf("MSEngine - Resuming animations\n");
        for (index = 0; index < Anims.Count(); index++) {
            Anims[index]->Resume();
        }
    }
}
