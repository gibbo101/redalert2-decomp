// Register a keyboard accelerator with its window (0x005B6130).
#include "shared/msgloop.hpp"

// Append the accelerator/window pair, growing owned storage by the configured
// step through Resize when necessary. Keep the capacity as a named local.
template <>
inline bool DynamicVectorClass<AcceleratorTracker>::Add(AcceleratorTracker const &object)
{
    if (ActiveCount >= Length()) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            int new_length = Length();
            new_length += GrowthStep;
            if (!Resize(new_length)) {
                return false;
            }
        } else {
            return false;
        }
    }
    (*this)[ActiveCount++] = object;
    return true;
}

void __fastcall Add_Accelerator(HWND window, HACCEL accelerator)
{
    AcceleratorTracker entry;
    entry.unknown_00 = (int)accelerator;
    entry.unknown_04 = (int)window;
    _Accelerators.Add(entry);
}
