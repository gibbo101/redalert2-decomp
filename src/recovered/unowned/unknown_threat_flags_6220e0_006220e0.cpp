// ?unknown_threat_flags_6220e0@@YIHH@Z (0x006220E0)
// The threat flags (THREAT_*) a team mission's quarry (target category, see
// unknown_quarry_from_name 0x00622090) searches for; 0 for none/anything and
// base threats. quarry.cpp, after Name_From_Quarry 0x006220D0.

int __fastcall unknown_threat_flags_6220e0(int quarry)
{
    switch (quarry) {
    case 1:
        return 0;
    case 2:
        return 0x20;
    case 3:
        return 0x40;
    case 4:
        return 8;
    case 5:
        return 0x10;
    case 6:
        return 0x1000;
    case 7:
        return 0x2000;
    case 8:
        return 0;
    case 9:
        return 0x800;
    case 10:
        return 0x8000;
    case 11:
        return 0x10000;
    }
    return 0;
}
