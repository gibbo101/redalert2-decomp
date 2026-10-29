// IndexClass<int, CommandClass *>::Increase_Table_Size (0x0051E760): the hotkey table's
// template member, emitted in this unit for Load_Keyboard_Hotkeys (0x00519240).
// Layout and behaviour: shared/ini_class.hpp.
#include "shared/command.hpp"

template bool IndexClass<int, CommandClass *>::Increase_Table_Size(int amount);
