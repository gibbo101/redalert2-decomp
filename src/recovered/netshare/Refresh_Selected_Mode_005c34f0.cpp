// void __fastcall Unknown_005c34f0() (0x005C34F0)
#include "shared/lobby.hpp"
// @ref ?Unknown_00735B10@@YIPAUHWND__@@XZ=00735b10

void __fastcall Unknown_005c34f0()
{
    if (Current_Dialog_Id_00735b20() == 0x6b) {
        HWND dialog = Unknown_00735B10();
        int index = SendDlgItemMessageA(dialog, 0x6eb, 0x188, 0, 0);
        if (index != -1) {
            UnknownSessionA3D29C *mode = (UnknownSessionA3D29C *)SendDlgItemMessageA(dialog, 0x6eb, 0x199, index, 0);
            if (mode != 0) {
                mode->unknown_slot31();
            }
        }
    } else if (unknown_session_a3d29c != 0) {
        unknown_session_a3d29c->unknown_slot31();
    }
}
