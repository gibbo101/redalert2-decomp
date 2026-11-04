// UnitClass::~UnitClass() (0x006FA7C0)
// Releases the object at +0x5C4. While the game runs (0x00A40958) and the type
// is set: tells the house (flag +0x144 when it has none of the type left),
// leaves the team and the house, destroys the passengers (unless 0x00A40774),
// and takes off the map (FootClass slot 52; a recorded house hears of the
// cell). Always leaves the unit list and the techno index.
#include "shared/unit.hpp"
#include "shared/house.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Can_Build@HouseClass@@QAEHPBVTechnoTypeClass@@_N1@Z=004e3660
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?unknown_4ea800@HouseClass@@QAEXPAVTechnoClass@@@Z=004ea800
// @ref ?unknown_4689f0@UnknownCargo@@QAEPAVObjectClass@@XZ=004689f0
// @ref ?unknown_slot52@FootClass@@UAE_NXZ=004c9bd0
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?unknown_4e76a0@HouseClass@@QAE_NABVCell@@_N@Z=004e76a0
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?Units@@3V?$DynamicVectorClass@PAVUnitClass@@@@A=00866198
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_4b25c0@UnknownUnit5C4@@QAEXXZ=004b25c0
// @ref ??1FootClass@@UAE@XZ=004c2cb0

UnitClass::~UnitClass()
{
    if (unknown_5c4) {
        unknown_5c4->unknown_4b25c0();
        unknown_5c4 = 0;
    }
    if (unknown_flag_a40958 && Type != 0) {
        if (House->Can_Build(Type, 0, 0) == -1) {
            House->unknown_144 = true;
        }
        if (Team != 0) {
            Team->Unknown_006B8FB0(this, -1, 0);
            Team = 0;
        }
        House->unknown_4ea800(this);
        if (unknown_a40774 == 0) {
            while (Cargo.Object != 0) {
                ObjectClass *passenger = Cargo.unknown_4689f0();
                if (passenger != 0) {
                    delete passenger;
                }
            }
        }
        if (FootClass::unknown_slot52() && unknown_5b4 != -1) {
            ObjectClass *object = this;   // (the call below stays virtual, as in the original)
            Houses[unknown_5b4]->unknown_4e76a0(object->unknown_slot104(), 0);
            unknown_5b4 = -1;
        }
    }
    Unknown_006ECB90(this, true);
    Units.Delete(this);
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    unknown_7d = false;
}
