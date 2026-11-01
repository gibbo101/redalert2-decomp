// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Process_Landing_004bdfb0@FlyLocomotionClass@@QAE_NXZ=004bdfb0
// @ref ?Process_Take_Off_004bddf0@FlyLocomotionClass@@QAE_NXZ=004bddf0
// @ref ?Remove@DisplayClass@@QAEXPAVObjectClass@@@Z=00499a90
// @ref ?Submit@DisplayClass@@QAEXPAVObjectClass@@@Z=00499a40
// @ref ?Unknown_0054A550@MapClass@@QAEXABUCoordStruct@@HHH@Z=0054a550
#include "shared/fly_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/techno_type.hpp"
bool FlyLocomotionClass::unknown_4bca00()
{
    FootClass *initial=LinkedTo;
    if (initial && initial->Kind_Of()==2 && !static_cast<AircraftClass *>(initial)->Type->Landable) {
        unknown_5c=true;
        unknown_51=false;
        unknown_50=false;
        unknown_38=LinkedTo->unknown_slot32()->Flight_Level();
        return false;
    }
    if (LinkedTo->Strength>0 && (unknown_51 || unknown_50)) {
        int layer=LinkedTo->unknown_slot29();
        LinkedTo->unknown_slot71(0);
        Map.Remove(LinkedTo);
        if (unknown_51) Process_Landing_004bdfb0();
        if (unknown_50) Process_Take_Off_004bddf0();
        if (layer!=LinkedTo->unknown_slot29()) {
            bool ok=true;
            if (LinkedTo->unknown_slot29()==2 && !unknown_50) {
                if (!LinkedTo->unknown_slot309(&Map[Object_Coord(LinkedTo)])) {
                    unknown_50=true;
                    LinkedTo->unknown_79=false;
                    LinkedTo->unknown_slot71(0);
                    LinkedTo->unknown_slot109(LinkedTo->unknown_slot108()+10);
                    LinkedTo->unknown_slot71(1);
                    ok=false;
                }
            }
            if (ok) {
                if (LinkedTo->unknown_slot29()==2) {
                    LinkedTo->unknown_slot260(0,1);
                    LinkedTo->unknown_slot149(0x18);
                    LinkedTo->unknown_slot263(0,0,0,0);
                    LinkedTo->unknown_slot262(0,0,0,0);
                    Map.Unknown_0054A550(Object_Coord(LinkedTo),LinkedTo->unknown_1f4-3,LinkedTo->unknown_1f4+3,0);
                } else {
                    LinkedTo->unknown_slot149(0x19);
                    if (LinkedTo->In_Radio_Contact() && LinkedTo->unknown_494 && LinkedTo->unknown_494!=LinkedTo->Contact(0))
                        LinkedTo->unknown_slot149(3);
                }
            }
        }
        Map.Submit(LinkedTo);
        LinkedTo->unknown_slot71(1);
    }
    return false;
}
