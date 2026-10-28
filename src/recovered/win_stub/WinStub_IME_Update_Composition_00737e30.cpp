// void IME_Update_Composition() (0x00737E30)
// Reads the IME's composition string (wide) and caret position (in characters).
#include "shared/win_stub.hpp"
#include "shared/msfont.hpp"
#include "shared/crt_tokens.hpp"

// @ref _ImmGetCompositionStringA@16=00781c32
// @ref __mbsnbcnt=00784d8d
// @ref ?IMEContext@@3PAUHIMC__@@A=00b263e4
// @ref ?IMECompositionString@@3PAGA=00b261a8
// @ref ?IMECompositionLength@@3HA=00b263ec
// @ref ?IMECursorPosition@@3HA=00b263f0
// @ref ?unknown_b263a8@@3GA=00b263a8

void IME_Update_Composition()
{
    char buffer[0x204];
    IMECompositionString[0] = 0;
    IMECompositionLength = 0;
    IMECursorPosition = 0;
    if (IMEContext != 0) {
        int length = ImmGetCompositionStringA(IMEContext, 8, buffer, 0x200);
        if (length > 0) {
            buffer[length] = 0;
            int count = MultiByteToWideChar(0, 0, buffer, -1, IMECompositionString, 0x100);
            unknown_b263a8 = 0;
            if (count < 0) {
                count = 0;
            } else {
                IMECursorPosition = ImmGetCompositionStringA(IMEContext, 0x80, 0, 0) & 0xFFFF;
                count = wcslen(IMECompositionString);
            }
            IMECursorPosition = _mbsnbcnt((unsigned char *)buffer, IMECursorPosition);
            IMECompositionString[count] = 0;
            IMECompositionLength = count;
            if (IMECursorPosition > count) {
                IMECursorPosition = count;
            } else if (IMECursorPosition < 0) {
                IMECursorPosition = 0;
            }
        }
    }
}
