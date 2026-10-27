// int HouseClass::unknown_func_4e63f0(int kind, int index, bool naval) (0x004E63F0)
// Suspends the house's factory for a type (3 when it has none); the
// player's house also refreshes the type's sidebar entry (hypothesis).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

int HouseClass::unknown_func_4e63f0(int kind, int index, bool naval)
{
    UnknownFactoryView *factory = (UnknownFactoryView *)unknown_func_4eb580(kind, naval, unknown_func_4eb550(kind, index));
    if (factory == 0) {
        return 3;
    }
    factory->unknown_func_4b9630(true);
    if (unknown_player_a35db4 == this) {
        Map.Unknown_0067C2D0(Unknown_006818D0(kind, index, 0));
    }
    return 0;
}
