// void DisplayClass::unknown_slot35() (0x0049EBF0, slot 35)
// Aborts a drag select (Westwood's Abort_Drag_Select): the tactical view
// drops its band, both band flags clear, the flag 0x00A40D45 is set and the
// default mouse shape returns.
#include "shared/display.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006AA770@Tactical@@QAEXXZ=006aa770
// @ref ?unknown_flag_a40d45@@3_NA=00a40d45
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BO@HGAG@Display?3?5Abort_Drag_Select?$CI?$CJ?6?$AA@=007d5e7c

// Set when a drag select is aborted (0x00A40D45; hypothesis).
extern bool unknown_flag_a40d45;

void DisplayClass::unknown_slot35()
{
    if (unknown_tactical_83996c != 0) {
        unknown_tactical_83996c->Unknown_006AA770();
    }
    unknown_11cb = false;
    unknown_11cc = false;
    unknown_flag_a40d45 = true;
    Set_Default_Mouse(0, false);
    Debug_Printf("Display: Abort_Drag_Select()\n");
}
