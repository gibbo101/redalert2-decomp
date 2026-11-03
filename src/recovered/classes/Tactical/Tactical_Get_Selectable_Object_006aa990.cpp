// ObjectClass *Tactical::Get_Selectable_Object_006aa990(Point2D const &point) (0x006AA990): of the objects drawn this frame
// (the table at 0x00ABE5F8), the nearest to the view point within 200 (distance x*x + y*y/2) that may be picked:
// a techno that is active and not in limbo, the player's own, uncloaked or over a cell the player senses, or a
// veinhole terrain; failing that, the occupier of the cell under the point (TibSun Tactical::Get_Selectable_Object;
// the view pixel is two ints and the cell fallback sits under `if (best == 0)`: both set the original frame slots).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/object.hpp"
#include "shared/techno_map.hpp"
#include "shared/terrain_type.hpp"
#include "shared/house_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_tactical_pixels_abe5f8@@3PAUTacticalObjectPixel@@A=00abe5f8
// @ref ?Infantry_As_Techno_0040dbd0@@YIPAVTechnoClass@@PAVObjectClass@@@Z=0040dbd0
// @ref ?unknown_47c2e0@UnknownCellClass@@QAE_NH@Z=0047c2e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Map@@3VMapClass@@A=008324e0
// @ref ?Unknown_006A6BD0@Tactical@@QAE?AVCell@@ABUPoint2D@@@Z=006a6bd0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref __real@8@3ffe8000000000000000=0079a728

// Original RTTI-kind checked conversion: kinds 1, 2, 6 and 15, all TechnoClass descendants.
TechnoClass *__fastcall Infantry_As_Techno_0040dbd0(ObjectClass *object);

ObjectClass *Tactical::Get_Selectable_Object_006aa990(Point2D const &point)
{
    ObjectClass *best = 0;
    unsigned int bestdist = (unsigned int)-1;

    int pixelx = point.X + TacPixelX;
    int pixely = point.Y + TacPixelY;

    for (int index = 0; index < unknown_db0; index++) {
        TacticalObjectPixel &sel = unknown_tactical_pixels_abe5f8[index];
        ObjectClass *obj = sel.Object;

        if (obj != 0) {
            TechnoClass *tech = Infantry_As_Techno_0040dbd0(obj);
            bool pass = false;

            if (tech != 0) {
                if (obj->unknown_7d && !tech->unknown_76) {
                    if (tech->unknown_372 || tech->unknown_1b8 != 2 || ((UnknownCellClass *)&Map[tech->Center_Coord()])->unknown_47c2e0(unknown_player_a35db4->ArrayIndex)) {
                        pass = true;
                    }
                }
            }

            if (tech == 0) {
                if (obj->Class_Of() != 0 && obj->Class_Of()->Kind_Of() == 0x25) {
                    TerrainTypeClass *type = (TerrainTypeClass *)obj->Class_Of();
                    if (type->IsVeinhole) {
                        pass = true;
                    }
                }
            }

            if (pass) {
                Point2D pos = sel.Pixel - Point2D(pixelx, pixely);
                unsigned int dist = int(double(pos.X * pos.X) + double(pos.Y * pos.Y) * 0.5);
                if (dist < bestdist && dist < 200) {
                    bestdist = dist;
                    best = obj;
                }
            }
        }
    }
    if (best == 0) {
        Cell cell = Unknown_006A6BD0(Point2D(unknown_rect_839630.X, unknown_rect_839630.Y) + point);
        best = Map[cell].OccupierPtr;
    }
    return best;
}
