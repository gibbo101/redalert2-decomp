// bool TActionClass::unknown_queue_theme(...) (0x006B1160)
// Queues theme Data on the music player; always true.
#include "shared/taction.hpp"
#include "shared/theme.hpp"
// @ref ?Queue_Song@ThemeClass@@QAEXH@Z=006e7e20
// @ref ?Theme@@3VThemeClass@@A=00a35d78

bool TActionClass::unknown_queue_theme(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Theme.Queue_Song(Data);
    return true;
}
