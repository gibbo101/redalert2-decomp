// void __fastcall unknown_disable_ok_and_send(UnknownDialogOwner_005974f0 *) -- 0x005974F0
// Purpose: disables control 1 (IDOK) of the owner's dialog window (+0x00),
// then hands a zeroed 250-byte message of type 0x74 to the object at
// 0x00A40A28 (0x005D05F0 with the size and a flag of 1). No direct callers.
// Bound by linear sweep to the final ret (the frozen bound stops before the
// epilogue).
#include "shared/win32_api.hpp"
#include "shared/crt_memory.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__EnableWindow@8=0079a490
// @ref ?unknown_send_5d05f0@UnknownMessageSink_005974f0@@QAEXPAXHH@Z=005d05f0
// @ref ?unknown_message_sink_a40a28@@3VUnknownMessageSink_005974f0@@A=00a40a28

WIN32_IMPORT HWND __stdcall GetDlgItem(HWND dialog, int id);
WIN32_IMPORT BOOL __stdcall EnableWindow(HWND window, BOOL enable);

#pragma pack(push, 2)
struct UnknownMessage_005974f0 {
    int Type;                        // +0x00
    char unknown_04[0xfa - 4];
};
#pragma pack(pop)

class UnknownMessageSink_005974f0 {
public:
    void unknown_send_5d05f0(void *message, int size, int flag);
};

extern UnknownMessageSink_005974f0 unknown_message_sink_a40a28;

struct UnknownDialogOwner_005974f0 {
    HWND Window;                     // +0x00
};

void __fastcall unknown_disable_ok_and_send_005974f0(UnknownDialogOwner_005974f0 *owner)
{
    HWND button = GetDlgItem(owner->Window, 1);
    if (button != 0) {
        EnableWindow(button, 0);
    }
    UnknownMessage_005974f0 message;
    memset(&message, 0, sizeof(message));
    message.Type = 0x74;
    unknown_message_sink_a40a28.unknown_send_5d05f0(&message, sizeof(message), 1);
}
