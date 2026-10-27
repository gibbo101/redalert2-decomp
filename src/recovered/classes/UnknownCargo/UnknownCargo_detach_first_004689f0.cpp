#include "shared/techno.hpp"
ObjectClass *UnknownCargo::unknown_4689f0() {
    ObjectClass *passenger = Object;
    if (!passenger) return 0;
    Object = passenger->unknown_30;
    passenger->unknown_30 = 0;
    --Count;
    return passenger;
}
