// Unlinks only: original65-bytebody leaves Count and removed-next unchanged.
#include "shared/foot.hpp"
void UnknownCargo::Unknown_00468A70(FootClass *passenger)
{
    if (passenger && Object) {
        if (Object == passenger) Object = Object->unknown_30;
        else {
            ObjectClass *previous = Object;
            while (previous->unknown_30) {
                if (passenger == previous->unknown_30) {
                    previous->unknown_30 = previous->unknown_30->unknown_30;
                    break;
                }
                previous = previous->unknown_30;
            }
        }
    }
}
