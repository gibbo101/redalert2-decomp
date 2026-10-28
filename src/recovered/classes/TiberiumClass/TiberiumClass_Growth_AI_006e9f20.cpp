// void TiberiumClass::Growth_AI() (0x006E9F20)
// While the scenario lets tiberium spread, each type whose growth timer has run out grows once and
// restarts the timer at its Growth rate (0.3 of it with the TiberiumGrows option).
#include "shared/tiberium.hpp"
#include "shared/special.hpp"
// @ref ?Process_Growth@TiberiumClass@@QAEXXZ=006ea1e0
// @ref __real@8@3ffd9999999999999800=0079dd50
// @ref __real@8@3fff8000000000000000=0079a708

void TiberiumClass::Growth_AI()
{
    if (unknown_id_source_a3d290->unknown_222a) {
        for (int index = 0; index < unknown_TiberiumClass_list_00ac0b30.Count(); index++) {
            if (unknown_TiberiumClass_list_00ac0b30[index]->GrowthTimer == 0) {
                unknown_TiberiumClass_list_00ac0b30[index]->Process_Growth();
                double factor = unknown_id_source_a3d290->Special().TiberiumGrows ? 0.3 : 1.0;
                unknown_TiberiumClass_list_00ac0b30[index]->GrowthTimer =
                    CDTimerClass<FrameTimerClass>(unknown_TiberiumClass_list_00ac0b30[index]->Growth * factor);
            }
        }
    }
}
