// static int __fastcall TActionClass::Action_Flags(int type) (0x006B2DF0)
// 2 for the action types that need a waypoint (hypothesis), else 0.
#include "shared/object.hpp"
#include "shared/taction.hpp"

int __fastcall TActionClass::Action_Flags(int type)
{
    int flags = 0;
    switch (type) {
        case 14:
        case 32:
        case 60:
        case 61:
        case 62:
        case 91:
        case 111:
            flags = 2;
            break;
    }
    return flags;
}


