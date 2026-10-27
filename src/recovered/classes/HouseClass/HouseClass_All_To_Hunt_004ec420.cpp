// HRESULT __stdcall HouseClass::All_To_Hunt() (0x004EC420)
// Sends every active unit of the house to hunt (out of its team) and lets
// the buildings that can do so act on it (IHouse).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"


// TeamClass and FootClass as far as this unit calls them (views).
struct UnknownTeamView {
    void unknown_func_6b8fb0(TechnoClass *techno, int arg2, int arg3);   // 0x006B8FB0 (removes a member; hypothesis)
};
struct UnknownFootView : public TechnoClass {
    char unknown_0418[0x4C4 - 0x418];
    UnknownTeamView *Team;                  // +0x4C4
};

// AbstractClass flag bit 2: a FootClass (hypothesis).
inline bool Is_Foot_4ec420(AbstractClass const *object)
{
    return object->unknown_14_bit2;
}

HRESULT __stdcall HouseClass::All_To_Hunt()
{
    for (int index = Technos.Count() - 1; index >= 0; index--) {
        TechnoClass *techno = Technos[index];
        if (this == techno->House && techno->unknown_74 && !techno->unknown_76 && techno != 0) {
            bool is_foot = Is_Foot_4ec420(techno);
            if (is_foot) {
                UnknownFootView *foot = (UnknownFootView *)techno;
                if (foot->Team != 0) {
                    foot->Team->unknown_func_6b8fb0(foot, -1, 0);
                }
                foot->unknown_slot116(15, false);   // hunt (hypothesis)
            }
            if (!is_foot && techno->Kind_Of() == 6) {
                UnknownBuildingView *building = (UnknownBuildingView *)techno;
                if (building->unknown_func_4532f0() > 0) {
                    building->unknown_func_452f50(1);
                }
            }
        }
    }
    unknown_190 = true;
    return S_OK;
}
