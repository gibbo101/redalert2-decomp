// HRESULT __stdcall CDownloadEventSink::OnProgressUpdate(int bytes_read, int total_size, int time_taken, int time_left) (0x00766910, slot 5)
// Moves the progress bar (control 0x5C6) and, at most once a second,
// shows the byte counts (and the time left when known) in control 0x5C8.
#include "shared/wol_sink.hpp"
// @ref ?Unknown_00735B10@@YIPAUHWND__@@XZ=00735b10
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref _time=0078387f
// @ref ?unknown_b2acc8@@3JA=00b2acc8

HRESULT __stdcall CDownloadEventSink::OnProgressUpdate(int bytes_read, int total_size, int time_taken, int time_left)
{
    wchar_t text[200];
    text[0] = 0;
    SendDlgItemMessageA(Unknown_00735B10(), 0x5C6, 0x402, (unsigned)(bytes_read * 100) / (unsigned)total_size, 0);
    if (time_left > 0) {
        swprintf(text, StringTable::Load_String("TXT_BYTES_W_TIME", 0, "D:\\Ra2\\wonline.cpp", 3981), bytes_read, total_size, time_left);
    } else {
        swprintf(text, StringTable::Load_String("TXT_BYTES_WO_TIME", 0, "D:\\Ra2\\wonline.cpp", 3986), bytes_read, total_size);
    }
    if (time(0) - unknown_b2acc8) {
        HWND window = GetDlgItem(Unknown_00735B10(), 0x5C8);
        SendMessageA(window, 0x4B2, 0, (LPARAM)text);
        unknown_b2acc8 = time(0);
    }
    return S_OK;
}
// @ref ??_C@_0BB@NHOD@TXT_BYTES_W_TIME?$AA@=00800484
// @ref ??_C@_0BC@JLDO@TXT_BYTES_WO_TIME?$AA@=00800470
