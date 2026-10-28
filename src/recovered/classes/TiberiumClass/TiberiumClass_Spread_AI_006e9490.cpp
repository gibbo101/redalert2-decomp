// void TiberiumClass::Spread_AI() (0x006E9490)
// While the scenario lets tiberium spread, each type whose spread timer has run out spreads once and
// restarts the timer at its Spread rate.
#include "shared/tiberium.hpp"
// @ref ?Process_Spread@TiberiumClass@@QAEXXZ=006e9720

void TiberiumClass::Spread_AI()
{
    if (unknown_id_source_a3d290->unknown_222a) {
        for (int index = 0; index < unknown_TiberiumClass_list_00ac0b30.Count(); index++) {
            if (unknown_TiberiumClass_list_00ac0b30[index]->SpreadTimer == 0) {
                unknown_TiberiumClass_list_00ac0b30[index]->Process_Spread();
                unknown_TiberiumClass_list_00ac0b30[index]->SpreadTimer =
                    CDTimerClass<FrameTimerClass>(unknown_TiberiumClass_list_00ac0b30[index]->Spread);
            }
        }
    }
}
