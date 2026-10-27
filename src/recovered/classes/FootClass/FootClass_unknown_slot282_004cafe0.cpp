// bool FootClass::unknown_slot282() (0x004CAFE0)
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A7F0@MapClass@@QAE_NABUCoordStruct@@@Z=0055a7f0
// @ref ?Unknown_006BA990@TeamClass@@QAE_NXZ=006ba990

bool FootClass::unknown_slot282()
{
    if (!unknown_32d) {
        return false;
    }
    if (Team != 0 && !Team->Unknown_006BA990()) {
        return false;
    }
    if (unknown_slot32()->IsTrain && unknown_494 != 0) {
        if (Map.Unknown_0055A7F0(unknown_494->Center_Coord())) {
            return false;
        }
    }
    return true;
}
