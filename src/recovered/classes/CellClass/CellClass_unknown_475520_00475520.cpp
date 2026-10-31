// void CellClass::Draw_Shroud_And_Fog(Point2D const &point, Rect const &clip) (0x00475520; TibSun name)
// Refreshes the cell's shroud frame (+0x120, layer 0) and draws it, then its
// fog frame (+0x121, layer 1), drawn only when the scenario has fog of war
// (+0x000 bit 0x1000) and the player's house does not see everything
// (+0x13D). Frame -2 draws as 15, -1 as 0.
#include "shared/cell.hpp"
#include "shared/tactical.hpp"
// @ref ?Draw_Shroud_Or_Fog_Shape@CellClass@@QAEXABUPoint2D@@ABVRect@@H@Z=00474260
// @ref ?Draw_Fog_Shape@CellClass@@QAEXABUPoint2D@@ABVRect@@H@Z=00474510
#include "shared/id_source.hpp"
#include "shared/house.hpp"

void CellClass::Draw_Shroud_And_Fog(Point2D const &point, Rect const &clip)
{
    unknown_120 = unknown_tactical_83996c->Cell_Shadow(MapCoords, 0);
    int frame = unknown_120;
    if (frame == -2) {
        frame = 15;
    } else if (frame == -1) {
        frame = 0;
    }
    Draw_Shroud_Or_Fog_Shape(point, clip, frame);
    unknown_121 = unknown_tactical_83996c->Cell_Shadow(MapCoords, 1);
    if ((unknown_id_source_a3d290->unknown_000 & 0x1000) && !unknown_player_a35db4->unknown_13d) {
        frame = unknown_121;
        if (frame == -2) {
            frame = 15;
        } else if (frame == -1) {
            frame = 0;
        }
        Draw_Fog_Shape(point, clip, frame);
    }
}
