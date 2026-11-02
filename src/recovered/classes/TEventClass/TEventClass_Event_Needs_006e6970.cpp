// int Event_Needs(int type) (0x006E6970)
// What data an event type needs (TibSun tevent.cpp's Event_Needs: house,
// number, global, local, structure, unit, infantry, aircraft, team and
// waypoint, in that order; the returned codes are RA2's need values, names
// from the TS order and hypotheses). No callers in the image.
#include "shared/tevent.hpp"

int __fastcall Event_Needs(int type)
{
    switch (type) {
        case 1:
        case 3:
        case 5:
        case 9:
        case 10:
        case 11:
        case 24:
        case 25:
        case 26:
        case 30:
        case 44:
        case 53:
        case 55:
        case 56:
            return 13;   // house

        case 12:
        case 13:
        case 15:
        case 16:
        case 45:
        case 46:
        case 47:
        case 51:
        case 52:
            return 10;   // number

        case 27:
        case 28:
            return 22;   // global

        case 36:
        case 37:
            return 29;   // local

        case 19:
        case 32:
        case 57:
            return 8;   // structure

        case 20:
            return 6;   // unit

        case 21:
        case 54:
            return 5;   // infantry

        case 22:
            return 7;   // aircraft

        case 23:
            return 12;   // team

        case 34:
            return 9;   // waypoint

        default:
            break;
    }
    return 0;
}
