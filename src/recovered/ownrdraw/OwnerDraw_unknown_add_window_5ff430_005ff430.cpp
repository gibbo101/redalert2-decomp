#include "shared/win32_api.hpp"
#include "shared/crt_memory.hpp"
#include "shared/vector_class.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// A growable array of windows (an ArrayList<HWND> shape: count, capacity, items; grows to twice the count,
// at least 10). Filled by the EnumChildWindows callback 0x005FF430.
class UnknownWindowList {
public:
    int Count;      // +0x00
    int Capacity;   // +0x04
    HWND *Items;    // +0x08
    char Grow()
    {
        if (Count < Capacity) return 0;
        int capacity = Count * 2;
        if (capacity < 10) capacity = 10;
        HWND *items = (HWND *)(new unsigned char[capacity * sizeof(HWND)]);
        memset(items, 0, capacity * sizeof(HWND));
        if (Items != 0) memcpy(items, Items, Count * sizeof(HWND));
        delete [] (unsigned char *)Items;
        Items = items;
        Capacity = capacity;
        return 1;
    }
    char Add(HWND &window, int index)
    {
        if (index > Count) index = Count;
        if (index >= Capacity) Grow();
        if (Count >= Capacity) Grow();
        if (index < Count) memmove(Items + index + 1, Items + index, sizeof(HWND) * (Count - index));
        new ((void *)(Items + index)) HWND((HWND &)window);
        Count++;
        return 1;
    }
    int Length() const { return Count; }
};

// Adds window to the end of list (an EnumChildWindows callback).
BOOL __stdcall unknown_add_window_5ff430(HWND window, UnknownWindowList *list)
{
    if (list != 0) {
        list->Add(window, list->Length());
    }
    return TRUE;
}

}
