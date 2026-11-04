// InfantryClass::~InfantryClass() (0x004FF980)
// While the game runs (0x00A40958) and the type is set: tells the house
// (flag +0x144 when it has none of the type left), leaves the team and the
// house, stops the locomotor's animation and resets the infantry state.
// Always leaves the infantry list and the techno index.
#include "shared/infantry.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Can_Build@HouseClass@@QAEHPBVTechnoTypeClass@@_N1@Z=004e3660
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?unknown_4ea800@HouseClass@@QAEXPAVTechnoClass@@@Z=004ea800
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_slot52@FootClass@@UAE_NXZ=004c9bd0
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref _qsort=00781d46
// @ref ?search_compfunc@?$IndexClass@JPAVAbstractClass@@@@CAHPBX0@Z=0041ba10
// @ref ??1FootClass@@UAE@XZ=004c2cb0

InfantryClass::~InfantryClass()
{
    if (unknown_flag_a40958 && Type != 0) {
        if (House->Can_Build(Type, 0, 0) == -1) {
            House->unknown_144 = true;
        }
        if (Team != 0) {
            Team->Unknown_006B8FB0(this, -1, 0);
            Team = 0;
        }
        House->unknown_4ea800(this);
        InfantryClass::unknown_slot52();
    }
    Unknown_006ECB90(this, true);
    Infantry.Delete(this);
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    unknown_7d = false;
}
