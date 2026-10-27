// void HouseClass::unknown_func_4e4ef0() (0x004E4EF0)
// Updates the super weapons; for the player's house, refreshes the sidebar
// entry of each one that changed (hypothesis).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void HouseClass::unknown_func_4e4ef0()
{
    for (int index = 0; index < Supers.Count(); index++) {
        UnknownSuperView *super = (UnknownSuperView *)Supers[index];
        if (super->unknown_55 && super->unknown_func_69d390(this == unknown_player_a35db4) &&
            this == unknown_player_a35db4) {
            int id = super->Type->unknown_slot16();
            Map.Unknown_0067C2D0(Unknown_006818D0(0x39, id, 0));
        }
    }
}
