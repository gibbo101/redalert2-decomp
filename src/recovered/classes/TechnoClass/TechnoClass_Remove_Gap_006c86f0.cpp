// Gap-generator registration/removal, with the original void return behavior.
#include "shared/techno.hpp"
#include "shared/techno_map.hpp"
#include "shared/cell.hpp"
void TechnoClass::unknown_slot236()
{
    if (unknown_player_a35db4 && unknown_1fd) {
        if (!unknown_200) unknown_200=unknown_slot32()->GapRadiusInCells;
        unknown_1fd=false;
        CoordStruct projected=Coord;
        projected.X+=(Unknown_006A2970(projected.Z)/-30)*256;
        projected.Y+=(Unknown_006A2970(projected.Z)/-30)*256;
        Cell center(projected);
        int radius=unknown_200;
        for (int x=-radius-2; x<radius+2; ++x) {
            for (int y=-radius-2; y<radius+2; ++y) {
                if (x*x+y*y<(radius+1)*(radius+1)) {
                    Cell cell=Cell(center.X+x,center.Y+y);
                    if (!Owning_House()->Unknown_004F52B0() && !House->Is_Ally(unknown_player_a35db4) && !unknown_player_a35db4->unknown_13d) {
                        --Map[cell].unknown_134;
                        if (unknown_player_a35db4->unknown_566a && Map[cell].unknown_134<=0) {
                            --Map[cell].unknown_130;
                            if (Map[cell].unknown_130<=0) {
                                Map[cell].unknown_12c|=0x08u;
                                Map[cell].unknown_12c|=0x10u;
                            }
                        }
                    }
                    if (Owning_House()->Unknown_004F52B0() || House->Is_Ally(unknown_player_a35db4) || unknown_player_a35db4->unknown_13d) {
                        --Map[cell].unknown_13c;
                    }
                }
            }
        }
        if (unknown_player_a35db4) unknown_player_a35db4->unknown_188=false;
        Map.Unknown_00634030();
        Map.Flag_To_Redraw(2);
    }
}
