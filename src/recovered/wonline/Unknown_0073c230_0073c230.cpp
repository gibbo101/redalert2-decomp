// void __fastcall Unknown_0073c230() (0x0073C230; fastcall: register setups before the pushes)
// Runs dialog 0xCF (procedure 0x007485D0) modally with the keyboard cleared around it, then
// restores the input flag from the scenario's pause state and redraws the map.
#include "shared/wol_sink.hpp"
#include "shared/dialog_create.hpp"
#include "shared/keyboard.hpp"
#include "shared/lobby.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_Dialog_Proc_007485d0@@YGHPAUHWND__@@IIJ@Z=007485d0
// @ref ?unknown_flag_a40d44@@3_NA=00a40d44
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref ?Unknown_007359e0@@YIHPAUHWND__@@P6A_NXZHHH@Z=007359e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

void __fastcall Unknown_0073c230()
{
    HWND dialog = unknown_create_dialog_5ff610(0xCF, Unknown_Dialog_Proc_007485d0, 0);
    unknown_flag_a40d44 = true;
    WWKeyboard->Clear();
    ShowWindow(dialog, 1);
    Unknown_007359e0(dialog, unknown_6000d0, 0, 1, 1);
    WWKeyboard->Clear();
    unknown_flag_a40d44 = unknown_id_source_a3d290->unknown_2306;
    Map.Flag_To_Redraw(2);
}
