// bool TriggerClass::Spring(int event, ObjectClass *object, bool forced, bool persistent, int source) (0x006ED740)
// Unless disabled or already sprung: each event not yet marked must fire for event (in the trigger
// type's house, with the trigger's timer); events that fire and hold are marked. Any event that does
// not fire keeps the trigger from springing; forced skips the tests. A persistent spring restarts the
// timed events.
#include "shared/trigger.hpp"
#include "shared/house.hpp"
// @ref ?unknown_func_6e6050@TEventClass@@QAE_NHPAVHouseClass@@PAVObjectClass@@PAV?$CDTimerClass@VFrameTimerClass@@@@PA_NH@Z=006e6050
// @ref ?unknown_func_6e6cf0@TEventClass@@QBE_NXZ=006e6cf0

bool TriggerClass::Spring(int event, ObjectClass *object, bool forced, bool persistent, int source)
{
    if (!IsEnabled || unknown_2c) {
        return false;
    }
    bool sprung = true;
    if (!forced) {
        int index = 0;
        for (TEventClass *e = Class->Events; e != 0; e = e->Next) {
            if (!Is_Event_Marked(index) && !e->unknown_func_6e6050(event, HouseClass::As_Pointer(Class->unknown_a4->ArrayIndex),
                                                             object, &Timer, &persistent, source)) {
                sprung = false;
            } else if (persistent && e->unknown_func_6e6cf0() && e->unknown_func_6e6d50()) {
                Mark_Event(index);
            }
            index++;
        }
    }
    if (sprung && persistent) {
        Reset();
    }
    return sprung;
}
