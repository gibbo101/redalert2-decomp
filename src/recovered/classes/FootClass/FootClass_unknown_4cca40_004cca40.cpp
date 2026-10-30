// Cell FootClass::unknown_4cca40(Cell const &cell, bool arg2) (0x004CCA40)
// The cell to head for when ordered to cell (slot 77; arg2 is passed on to
// slot 27, which gives the action): no cell (unknown_geometry_k) when the
// cell's ground (bridge height included) is shrouded and the type may not
// move to shroud; otherwise the cell itself, or a nearby cell (0x005502E0)
// when it is off the visible map, shrouded or in another movement zone; a
// type that moves anywhere looks for a nearby cell only on action 2 (in the
// same zone as the slot 19 destination's cell otherwise). Teleporter types
// skip the zone check unless the action is 2. The movement zone maps 6 to
// 0 and 9 to 7 while the house's 0x0051FC80 holds; jumpjet infantry move
// anywhere only while it does not.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_type.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/house.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_k=00865f00
// @ref _unknown_geometry_j=00865f60

Cell FootClass::unknown_4cca40(Cell const &cell, bool arg2)
{
    int action = unknown_slot27(&cell, arg2, false);
    bool in_radar = Map.Unknown_0055A660(cell, true);

    CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
    coord.Z = Map.Unknown_0055A280(coord);
    if (((UnknownCellClass *)&Map[coord])->Flags & 0x100) {
        coord.Z += unknown_geometry_j;
    }
    if (unknown_slot32()->MoveToShroud || !Map.Unknown_00568140(coord)) {

        Cell nearby = cell;
        UnknownCellClass *cptr = (UnknownCellClass *)&Map[unknown_slot19(0)];
        int mzone = unknown_slot32()->MovementZone;
        if (mzone == 6) mzone = 0;
        else if (mzone == 9 && House->Unknown_0051FC80()) mzone = 7;

        bool moveanywhere = unknown_slot21() || unknown_slot32()->unknown_af5 || (Kind_Of() == 15 && ((InfantryClass *)this)->Type->JumpJet && !House->Unknown_0051FC80()) || Kind_Of() == 2;

        bool ontobridge = unknown_slot46(0);
        CoordStruct center = Cell_Coord(cell);
        center.Z = Map.Unknown_0055A280(center);
        if (((UnknownCellClass *)&Map[center])->Flags & 0x100) {
            center.Z += unknown_geometry_j;
        }
        bool shrouded = Map.Unknown_00568140(center);

        if (moveanywhere && action == 2) {
            nearby = Map.Unknown_005502E0(cell, unknown_slot32()->SpeedType, -1, mzone, ((UnknownCellClass *)&Map[cell])->Flags >> 8 & 1, Point2D(1, 1), 0, 1, unknown_slot32()->unknown_af5 && unknown_slot108() < 0, 1, Cell(0, 0), 0);
        } else {
            if (!in_radar || shrouded || !moveanywhere && (!unknown_slot32()->Teleporter || action == 2) && !Map.Unknown_0054F7C0(cptr->unknown_24, nearby, mzone, ontobridge, ((UnknownCellClass *)&Map[cell])->Flags >> 8 & 1, false)) {
                nearby = Map.Unknown_005502E0(cell, unknown_slot32()->SpeedType, Map.Zone(cptr->unknown_24, mzone, ontobridge), mzone, ((UnknownCellClass *)&Map[cell])->Flags >> 8 & 1, Point2D(1, 1), 0, 1, 0, 1, Cell(0, 0), 0);
            }
        }

        if (nearby != unknown_geometry_k) {
            return nearby;
        }
    }
    return unknown_geometry_k;
}
