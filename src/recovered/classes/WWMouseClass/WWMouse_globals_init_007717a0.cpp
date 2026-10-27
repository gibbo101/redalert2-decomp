// Dynamic initializer of unknown_empty_rect (0x007717A0, _$E2), the file-local
// empty Rect that shared/wwmouse.hpp defines in every unit including it.
// This first source of the unit also defines the file's globals (0x00B2AF30-0x00B2AF68).
// Unresolved: the original names of the empty rect and of the unknown_ flags.
#include "shared/wwmouse.hpp"
// @ref _unknown_empty_rect=00b2af20

MouseThreadInfoStruct MouseThreadInfo;
HANDLE MouseThread;
DWORD MouseThreadID;
bool unknown_flag_b2af58;
WWMouseClass *_Mouse;
HANDLE MouseMutex;
int MouseThreadActive;
bool unknown_flag_b2af68;
