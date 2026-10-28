// void IME_Reset() (0x00737D90)
// Clears the composition and result text and cancels the IME's composition.
#include "shared/win_stub.hpp"

// @ref _ImmNotifyIME@16=00781c26
// @ref ?IMEContext@@3PAUHIMC__@@A=00b263e4
// @ref ?IMECompositionString@@3PAGA=00b261a8
// @ref ?IMECompositionLength@@3HA=00b263ec
// @ref ?IMECursorPosition@@3HA=00b263f0
// @ref ?IMEComposing@@3HA=00b263f4
// @ref ?IMEResultString@@3PAGA=00b25f7c

void IME_Reset()
{
    IMECompositionString[0] = 0;
    IMECompositionLength = 0;
    IMECursorPosition = 0;
    IMEComposing = 0;
    IMEResultString[0] = 0;
    if (IMEContext != 0) {
        ImmNotifyIME(IMEContext, 0x15, 4, 0);
    }
}
