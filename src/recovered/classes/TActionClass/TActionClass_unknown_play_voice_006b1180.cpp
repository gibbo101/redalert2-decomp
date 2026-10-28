// bool TActionClass::unknown_play_voice(...) (0x006B1180)
// Plays the VoxClass Data through Speech_Play (type 2, its own priority); always true.
#include "shared/taction.hpp"
#include "shared/vox_class.hpp"

// @ref ?Speech_Play@@YIXHHH@Z=007158c0

bool TActionClass::unknown_play_voice(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Speech_Play(Data, 2, -1);
    return true;
}
