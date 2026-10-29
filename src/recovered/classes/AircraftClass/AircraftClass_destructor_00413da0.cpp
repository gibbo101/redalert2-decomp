// AircraftClass::~AircraftClass() (0x00413DA0)
// While the game runs (0x00A40958) and the type is set: tells the house
// (flag +0x144 when it has none of the type left), leaves the team and the
// house, then forgets the type. Always leaves the aircraft list and the
// techno index.
#include "shared/aircraft.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?unknown_4e3660@HouseClass@@QAEHPBVTechnoTypeClass@@HH@Z=004e3660
// @ref ?unknown_6d3040@TechnoClass@@QAEXPAV1@@Z=006d3040
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?unknown_4ea800@HouseClass@@QAEXPAVTechnoClass@@@Z=004ea800
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?Aircraft@@3V?$DynamicVectorClass@PAVAircraftClass@@@@A=00a40398
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref _qsort=00781d46
// @ref ??1FootClass@@UAE@XZ=004c2cb0

AircraftClass::~AircraftClass()
{
    if (unknown_flag_a40958 && Type != 0) {
        if (House->unknown_4e3660(Type, 0, 0) == -1) {
            House->unknown_144 = true;
        }
        unknown_6d3040(0);
        if (Team != 0) {
            Team->Unknown_006B8FB0(this, -1, 0);
            Team = 0;
        }
        House->unknown_4ea800(this);
        FootClass::unknown_slot52();
        Type = 0;
    }
    Unknown_006ECB90(this, true);
    Aircraft.Delete(this);
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    unknown_7d = false;
}
