// The modem guest's setup dialog (ModemGuest.ReadDialog, 0x00596D50; names from its debug output).
#ifndef RA2_SHARED_MODEM_GUEST_HPP
#define RA2_SHARED_MODEM_GUEST_HPP

#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"

// The modem guest record: the dialog window is its first member (hypothesis: the class around the
// "ModemGuest.ReadDialog" debug text).
struct UnknownModemGuest {
    // Reads the guest's name and colour choices from the dialog (0x00596D50).
    void ReadDialog_00596d50();
    HWND Window;                    // +0x00
};

// Narrows a wide string into dst, stopping at the terminator or after limit characters (-1: none; 0x006FA0F0).
void __fastcall Unknown_006FA0F0(char *dst, unsigned short const *src, int limit);

#endif
