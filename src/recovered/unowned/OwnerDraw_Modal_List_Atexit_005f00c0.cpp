// The real atexit function registered at005EE685/005EE6A5 for the modal HWND list.
// OriginalCount/Capacity/Items are atA73918/A7391C/A73920.
// @ref _unknown_modal_windows_a73918=00a73918
#include "shared/win32_api.hpp"
#include "shared/wol_array_list.hpp"
typedef WolArrayList<HWND> ModalWindowList_5f00c0;
extern "C" ModalWindowList_5f00c0 unknown_modal_windows_a73918;
void unknown_modal_list_atexit_5f00c0()
{
    unknown_modal_windows_a73918.~ModalWindowList_5f00c0();
}
