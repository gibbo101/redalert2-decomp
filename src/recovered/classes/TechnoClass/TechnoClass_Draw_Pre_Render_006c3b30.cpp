// TechnoClass slot 65 0x006C3B30: Draw_Pre_Render (TibSun techno.cpp). Draws the rear edges of a
// selected building's selection box before the building body.
#include "shared/techno.hpp"
#include "shared/selection_coord.hpp"
#include "shared/convert.hpp"
// @ref ??0CoordStruct@@QAE@HHH@Z=0041b630
void TechnoClass::unknown_slot65(int point, int cliprect)
{
    if (Kind_Of() == 6 && unknown_77 && Kind_Of() != 15) {
        int color = 15;
        if (unknown_slot108() < -4) {
            color = 12;
        }
        CoordStruct const &lepton = unknown_slot32()->unknown_slot31();
        ::Coord dim = lepton;
        dim.X /= 2;
        dim.Y /= 2;
        int x = dim.X;
        int y = dim.Y;
        color = unknown_drawer_8323c4->Convert(color);
        CoordStruct const &position = Center_Coord();
        ::Coord center = position;
        Draw_Double_Selection_Bracket_006c3950(center + ::Coord(-x, -y, 0), center + ::Coord(-x, -y, dim.Z), color);
        Draw_Double_Selection_Bracket_006c3950(center + ::Coord(-x, -y, 0), center + ::Coord(x, -y, 0), color);
        Draw_Double_Selection_Bracket_006c3950(center + ::Coord(-x, -y, 0), center + ::Coord(-x, y, 0), color);
        Draw_Double_Selection_Bracket_006c3950(center + ::Coord(-x, -y, dim.Z), center + ::Coord(-x, y, dim.Z), color);
        Draw_Double_Selection_Bracket_006c3950(center + ::Coord(-x, -y, dim.Z), center + ::Coord(x, -y, dim.Z), color);
    }
}
