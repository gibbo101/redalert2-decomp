// bool HouseClass::Is_Allowed_To_Ally(HouseClass *house) (0x004EC4E0)
// Whether the house may ally with another: not already allied, not the
// civilian side in a multiplayer game, and not the last unallied player.
#include "shared/techno.hpp"

// SideClass as far as this unit calls it.
class SideClass {
public:
    static int __fastcall Find_Index(char const *name);   // 0x0067AF90
};
extern int unknown_a40774;                  // 0x00A40774

bool HouseClass::Is_Allowed_To_Ally(HouseClass *house)
{
    if (Is_Ally(house)) {
        return false;
    }
    if (house->Type->Side == SideClass::Find_Index("Civilian") && unknown_game_mode_a3d298 != 0) {
        return false;
    }
    if (unknown_a40774 != 0) {
        return true;
    }
    if (unknown_13d) {
        return false;
    }
    int players = 0;
    int allies = 0;
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *other = Houses[index];
        if (!other->unknown_13d && !other->Type->MultiplayPassive) {
            players++;
            if (Is_Ally(other)) {
                allies++;
            }
        }
    }
    if (players == allies + 1) {
        return false;
    }
    return true;
}
