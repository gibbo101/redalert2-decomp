// void MissionClass::AI() (0x00594790, slot 23)
// ObjectClass's part; then, for a live object (+0x7D) whose mission timer
// has run out and that has strength left, the slot of the current mission
// (123-148, each returning the frames until the next step) restarts the
// timer. Unknown missions (and 3) use slot 123.
#include "shared/mission.hpp"
// @ref ?AI@ObjectClass@@UAEXXZ=005d27f0
// @ref ?Frame@@3HA=00a40d2c

void MissionClass::AI()
{
    ObjectClass::AI();
    if (unknown_7d && Timer.Value() == 0 && Strength > 0) {
        switch (Mission) {
        case 0:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot123());
            break;
        case 23:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot124());
            break;
        case 7:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot138());
            break;
        case 18:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot139());
            break;
        case 19:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot140());
            break;
        case 1:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot126());
            break;
        case 4:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot134());
            break;
        case 10:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot131());
            break;
        case 11:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot130());
            break;
        case 12:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot135());
            break;
        case 13:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot136());
            break;
        case 14:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot125());
            break;
        case 16:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot137());
            break;
        case 20:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot141());
            break;
        case 24:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot143());
            break;
        case 22:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot142());
            break;
        case 5:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot129());
            break;
        case 8:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot127());
            break;
        case 9:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot128());
            break;
        case 2:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot133());
            break;
        case 15:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot132());
            break;
        case 21:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot144());
            break;
        case 25:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot145());
            break;
        case 26:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot146());
            break;
        case 27:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot147());
            break;
        case 28:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot148());
            break;
        case 6:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot129());
            break;
        case 17:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot127());
            break;
        default:
            Timer = CDTimerClass<FrameTimerClass>(unknown_slot123());
            break;
        }
    }
}
