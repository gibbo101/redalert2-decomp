// bool TriggerTypeClass::Read_INI(CCINIClass &ini) (0x006EE470, slot 25)
// The trigger's [Triggers] line (house, next trigger, name, disabled, easy,
// normal, hard and the +0xA0 flag), then its event and action lists from
// [Events] and [Actions] (a count, then each entry's own fields). Events are
// pushed on the front of the list, actions appended in order.
// @ref ?Read_INI@TActionClass@@QAEXXZ=006ad860
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?Find_Index@HouseTypeClass@@SIHPBD@Z=004f94d0
// @ref ?HouseTypes@@3V?$DynamicVectorClass@PAVHouseTypeClass@@@@A=00a35d08
#include "shared/object.hpp"
#include "shared/trigger_type.hpp"
#include "shared/taction.hpp"
#include "shared/house_type.hpp"

bool TriggerTypeClass::Read_INI(CCINIClass &ini)
{
    char buffer[512];
    if (ini.Get_String(unknown_triggers_section_7ada50, ID, "", buffer, sizeof(buffer))) {
        char *token = strtok(buffer, ",");
        if (_stricmp(token, "<none>") == 0) {
            unknown_a4 = HouseTypes[0];
        } else {
            unknown_a4 = HouseTypes[HouseTypeClass::Find_Index(token)];
        }

        token = strtok(0, ",");
        Next = 0;
        if (_stricmp(token, "<none>") != 0) {
            Next = Find_Or_Make(token);
        }

        token = strtok(0, ",");
        Name = FixedString<49>(token);

        token = strtok(0, ",");
        if (token != 0 && atoi(token) == 0) {
            IsEnabled = true;
        } else {
            IsEnabled = false;
        }
        token = strtok(0, ",");
        if (token != 0 && atoi(token) != 0) {
            IsEasy = true;
        } else {
            IsEasy = false;
        }
        token = strtok(0, ",");
        if (token != 0 && atoi(token) != 0) {
            IsNormal = true;
        } else {
            IsNormal = false;
        }
        token = strtok(0, ",");
        if (token != 0 && atoi(token) != 0) {
            IsHard = true;
        } else {
            IsHard = false;
        }
        token = strtok(0, ",");
        if (token != 0 && atoi(token) != 0) {
            unknown_a0 = true;
        }

        if (ini.Get_String(unknown_events_section_7ada58, ID, "", buffer, sizeof(buffer))) {
            int count = atoi(strtok(buffer, ","));
            for (; count != 0; count--) {
                TEventClass *event = new TEventClass();
                event->Read_INI();
                event->Next = Events;
                Events = event;
            }
        }

        if (ini.Get_String(unknown_actions_section_7ada54, ID, "", buffer, sizeof(buffer))) {
            int count = atoi(strtok(buffer, ","));
            TActionClass *last = 0;
            Actions = 0;
            for (; count != 0; count--) {
                TActionClass *action = new TActionClass();
                action->Read_INI();
                if (Actions == 0) {
                    Actions = action;
                } else {
                    last->Next = action;
                }
                last = action;
            }
        }
        return true;
    }
    return false;
}
