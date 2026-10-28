// void __fastcall IME_Send_Result(HWND window) (0x00737F20)
// Sends each character of the IME's result string to window as message 0x4D9.
#include "shared/win_stub.hpp"
#include "shared/crt_tokens.hpp"

// @ref _ImmGetCompositionStringA@16=00781c32
// @ref ?IMEContext@@3PAUHIMC__@@A=00b263e4

void __fastcall IME_Send_Result(HWND window)
{
    char buffer[0x204];
    unsigned short text[0x102];
    if (IMEContext != 0) {
        int length = ImmGetCompositionStringA(IMEContext, 0x800, buffer, 0x200);
        if (length > 0) {
            buffer[length] = 0;
            int count = MultiByteToWideChar(0, 0, buffer, strlen(buffer), text, 0x100);
            if (count < 0) {
                count = 0;
            }
            text[count] = 0;
            for (int index = 0; index < count; index++) {
                SendMessageA(window, 0x4D9, text[index], text[index]);
            }
        }
    }
}
