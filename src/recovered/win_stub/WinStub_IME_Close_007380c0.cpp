// void IME_Close_007380c0() (0x007380C0)
// Closes the input method of the game window's IME context (ImmSetOpenStatus FALSE). The window
// unit has two functions with this body (0x007380C0, 0x007380E0).
#include "shared/win_stub.hpp"

extern "C" BOOL __stdcall ImmSetOpenStatus(HIMC context, BOOL open);   // 0x00781C38
void IME_Close_007380c0();
// @ref _ImmSetOpenStatus@8=00781c38
// @ref ?IMEContext@@3PAUHIMC__@@A=00b263e4

void IME_Close_007380c0()
{
    if (IMEContext) {
        ImmSetOpenStatus(IMEContext, 0);
    }
}
