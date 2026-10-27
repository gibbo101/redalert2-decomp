// void HouseClass::unknown_func_4ec5e0() (0x004EC5E0)
// When the game object at 0x00A3D29C asks for it (slot 1) or the rules set
// +0x111D: every computer house allies with every other computer house and
// becomes the enemy of every human one (hypothesis).
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

// The object at 0x00A3D29C (view).
class UnknownA3D29CView {
public:
    virtual void unknown_slot0();
    virtual bool unknown_slot1();
};
extern UnknownA3D29CView *unknown_a3d29c;   // 0x00A3D29C

inline bool Is_Controlled_4ec5e0(HouseClass const *house)
{
    if (house->unknown_134 || house->unknown_135) {
        return true;
    }
    return false;
}

// A house a player controls (+0x134; outside multiplayer also +0x135).
inline bool Is_Human_4ec5e0(HouseClass const *house)
{
    if (unknown_game_mode_a3d298 != 0) {
        return house->unknown_134;
    }
    return Is_Controlled_4ec5e0(house);
}

void HouseClass::unknown_func_4ec5e0()
{
    bool forced = Rules->unknown_111d;
    if ((unknown_a3d29c != 0 && unknown_a3d29c->unknown_slot1()) || forced) {
        for (int index = 0; index < Houses.Count(); index++) {
            HouseClass *house = Houses[index];
            if (house != 0 && !house->unknown_13d && !Is_Human_4ec5e0(house)) {
                house->unknown_191 = true;
                for (int other_index = 0; other_index < Houses.Count(); other_index++) {
                    HouseClass *other = Houses[other_index];
                    if (other != 0 && !other->unknown_13d) {
                        if (Is_Human_4ec5e0(other)) {
                            house->Make_Enemy(other, false);
                        } else {
                            house->Make_Ally(other, false);
                        }
                    }
                }
            }
        }
    }
}
