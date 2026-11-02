// IndexClass<int, CommandClass *>::Add_Index (0x0051E3B0): the hotkey table's template member,
// emitted in this unit for unknown_init_commands_5173c0 (0x005173C0), its only caller.
// Layout and behaviour: shared/ini_class.hpp.
#include "shared/command.hpp"

template bool IndexClass<int, CommandClass *>::Add_Index(int const &id, CommandClass *const &data);
