// A second window-keyed table of the unit at 0x00A73400 (wlib dictionary, same shape as 0x00A73688; the
// value type is a 4-byte hypothesis): its dynamic initializer (0x005DEB90) and atexit destructor
// (0x005DEC30, the next draft).
// @ref ?unknown_window_table_a73400@@3V?$WolDictionary@PAUHWND__@@H@@A=00a73400
// @ref ?unknown_hash_window_5de970@@YIIABQAUHWND__@@@Z=005de970
#include "shared/wol_dictionary.hpp"

unsigned int __fastcall unknown_hash_window_5de970(HWND const &key);

WolDictionary<HWND, int> unknown_window_table_a73400(unknown_hash_window_5de970);
