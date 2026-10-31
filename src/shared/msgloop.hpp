// Westwood's msgloop.cpp (wwlib; TS reconstruction names): the window message pump and the modeless
// dialog / accelerator lists it consults (0x005B5DE0-0x005B6830 with their vector instantiations).
#ifndef RA2_SHARED_MSGLOOP_HPP
#define RA2_SHARED_MSGLOOP_HPP

#include "shared/win32_api.hpp"
#include "shared/vector_class.hpp"
#include "shared/vector_elements.hpp"

typedef struct HACCEL__ *HACCEL;

// The modeless dialogs (0x00A71900), the accelerators (0x00A71928; AcceleratorTracker unknown_00 is the
// HACCEL, unknown_04 its window) and the message intercept (0x00A719A4).
extern DynamicVectorClass<HWND> _ModelessDialogs;
extern DynamicVectorClass<AcceleratorTracker> _Accelerators;
extern bool (__fastcall *Message_Intercept_Handler)(MSG &message);
// Called with every message before the tooltips (0x004919B0, not yet recovered).
void __fastcall unknown_message_4919b0(MSG *message);
// Dispatches every pending window message (0x005B5EE0).
void Windows_Message_Handler();

#endif
