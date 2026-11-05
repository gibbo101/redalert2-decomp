// wlib Dictionary::add, the out-of-line instance (0x005ECC90 calls it): expands operator= and leaves Copy_List 0x00600460 out of line.
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/wol_dictionary.hpp"
template bool WolDictionary<unsigned int, OwnerDraw::UnknownControlRecord>::Add(unsigned int const &key, OwnerDraw::UnknownControlRecord const &value);
