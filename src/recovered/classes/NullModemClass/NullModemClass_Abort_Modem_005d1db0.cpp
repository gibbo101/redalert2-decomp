// int NullModemClass::Abort_Modem() (0x005D1DB0)
// The serial port's abort function: services the game, and returns -1000
// once ESC was pressed (it stays set).
#include "shared/null_modem.hpp"
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?Unknown_005B5EE0@@YAXXZ=005b5ee0
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Check@WWKeyboardClass@@QAEGXZ=005322d0
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref ?unknown_modem_aborted_a72ec4@@3_NA=00a72ec4

int NullModemClass::Abort_Modem()
{
    Service_Game_IO_00481fb0();
    Unknown_005B5EE0();
    int key = WWKeyboard->Check();
    if (key) {
        WWKeyboard->Clear();
        if (key == 0x1B) {
            unknown_modem_aborted_a72ec4 = true;
            return -1000;
        }
    }
    return unknown_modem_aborted_a72ec4 ? -1000 : 0;
}
