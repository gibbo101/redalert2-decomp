// Halves and rehashes the HWND-to-window-procedure tables (0x00602730).
// The shared template body is instantiated by the existing Restore_Window caller.
// This explicit instantiation records that original out-of-line copy.
#include "shared/wol_dictionary.hpp"
#include "shared/win32_api.hpp"
template void WolDictionary<HWND, WNDPROC>::Shrink_Table();
