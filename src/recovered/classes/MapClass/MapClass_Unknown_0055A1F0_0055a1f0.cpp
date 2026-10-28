// void MapClass::Unknown_0055A1F0() (0x0055A1F0)
// Once per game (player +0x188 clear): passes every cell of the global Map
// with the player to DisplayClass slot 39, then redraws.
#include "shared/map.hpp"
// @ref ?unknown_slot39@DisplayClass@@UAE_NABVCell@@H@Z=0049a370

void MapClass::Unknown_0055A1F0()
{
    if (!unknown_player_a35db4->unknown_188) {
        unknown_player_a35db4->unknown_188 = true;
        Map.Unknown_0055A550();
        for (CellClass *cell = Map.Unknown_0055A490(); cell != 0; cell = Map.Unknown_0055A490()) {
            Map.unknown_slot39(cell->MapCoords, (int)unknown_player_a35db4);
        }
        Map.Unknown_00634030();
        Map.Flag_To_Redraw(1);
    }
}
