// int __fastcall unknown_script_mission_6eafe0(int mission) -- 0x006EAFE0
// Maps a script action number to a value (most actions give 0); no callers by direct call
// (name, argument and result types are hypotheses).

int __fastcall unknown_script_mission_6eafe0(int mission)
{
    switch (mission) {
    case 0:
    case 57:
        return 15;
    case 4:
        return 19;
    case 34:
        return 32;
    case 12:
    case 38:
        return 22;
    case 39:
    case 40:
        return 29;
    case 5:
    case 6:
    case 13:
    case 32:
    case 42:
    case 50:
        return 10;
    case 1:
    case 3:
    case 15:
    case 16:
        return 9;
    case 20:
        return 13;
    case 11:
        return 18;
    case 17:
        return 20;
    case 18:
        return 12;
    case 24:
        return 4;
    case 25:
        return 3;
    case 26:
        return 2;
    case 27:
        return 1;
    case 46:
    case 47:
    case 56:
    case 58:
        return 36;
    case 8:
        return 37;
    case 51:
        return 41;
    case 52:
        return 42;
    default:
        return 0;
    }
}
