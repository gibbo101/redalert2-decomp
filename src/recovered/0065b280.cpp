// IStream *UnknownComPtr<IStream>::Checked() const (0x0065B280)
// comip's checked access (E_POINTER when empty), emitted out of line where
// SavegameInformation::Load 0x00659A90 runs out of inline budget
// (shared/com_ptr.hpp).
#include "shared/savegame_info.hpp"
#include "shared/com_ptr.hpp"
