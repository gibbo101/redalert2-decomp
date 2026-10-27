// ObjectClass placement005D3890, original824+8; private typed candidate.
// Interface/source types remain explicit compatible hypotheses.
#include "shared/object_type.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/terrain_type.hpp"
#include "shared/unknown_list_832470.hpp"
#include "shared/alpha_shape.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
extern bool unknown_flag_a40958;
extern int unknown_a40774;
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Submit@UnknownList832470@@QAE_NPAVObjectClass@@_N@Z=0053e330
// @ref ?Submit@DisplayClass@@QAEXPAVObjectClass@@@Z=00499a40
// @ref ?Unknown_006A29D0@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref ?Unknown_006A3020@Tactical@@QAEXVRect@@H@Z=006a3020
// @ref ??0AlphaShapeClass@@=0041ebe0
// @ref ??0UnknownObject5394F0@@=005393e0
// @ref ?Unknown_00539510@UnknownObject5394F0@@=00539510
// @ref _unknown_static_rect=00a72ed0
static inline void Object_Placement_Add_Point(Point2D &point, Point2D const &offset)
{
    Point2D delta = offset;
    point.X = (int)((unsigned int)point.X + (unsigned int)delta.X);
    point.Y = (int)((unsigned int)point.Y + (unsigned int)delta.Y);
}

bool ObjectClass::unknown_slot53(CoordStruct const *coord, int direction)
{
    if (!unknown_flag_a40958 || !unknown_76 || unknown_74) return false;
    if (!unknown_a40774 && unknown_slot101(&Map[*coord], -1, -1, 0, 0))
        return false;
    unknown_76 = false;
    unknown_75 = false;
    ObjectTypeClass *type = Class_Of();
    CoordStruct placed = *coord;
    if (type) placed = type->unknown_slot27(*coord);
    unknown_slot103(placed);
    if (unknown_slot71(1)) {
        if (unknown_7d) {
            if (unknown_slot29() != -1) Map.Submit(this);
            if (type) {
                if (type->unknown_204 &&
                    (Kind_Of() != 0x24 ||
                     (Kind_Of() == 0x24 && static_cast<TerrainTypeClass *>(type)->SpawnsTiberium)) &&
                    (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5 || Fetch_ID() != -2))
                    unknown_list_832470.Submit(this, false);
                if (type->unknown_ac) {
                    CoordStruct location = Center_Coord();
                    Point2D pixel;
                    unknown_tactical_83996c->Unknown_006A29D0(location, pixel);
                    Object_Placement_Add_Point(pixel, unknown_tactical_83996c->unknown_b0);
                    ShapeFileStruct *shape = reinterpret_cast<ShapeFileStruct *>(Class_Of()->unknown_ac);
                    Point2D half;
                    half.X = shape->Width / 2;
                    half.Y = shape->Height / 2;
                    pixel.X = (int)((unsigned int)pixel.X - (unsigned int)half.X);
                    pixel.Y = (int)((unsigned int)pixel.Y - (unsigned int)half.Y);
                    new AlphaShapeClass(this, pixel.X, pixel.Y);
                    if (!unknown_a40774) {
                        unknown_tactical_83996c->Unknown_006A3020(Rect(
                            (int)((unsigned int)pixel.X - (unsigned int)unknown_tactical_83996c->unknown_b0.X),
                            (int)((unsigned int)pixel.Y - (unsigned int)unknown_tactical_83996c->unknown_b0.Y),
                            shape->Width, shape->Height), 1);
                    }
                }
            }
            if (Class_Of()->unknown_20a) {
                unknown_94 = new UnknownObject5394F0();
                if (unknown_94) {
                    RGBClass override_color = Rules->LineTrailColorOverride;
                    if (override_color == RGBClass(0, 0, 0)) {
                        RGBClass color = Class_Of()->LineTrailColor;
                        unknown_94->Color = color;
                    } else {
                        RGBClass color = Rules->LineTrailColorOverride;
                        unknown_94->Color = color;
                    }
                    unknown_94->Unknown_00539510(Class_Of()->unknown_210);
                    unknown_94->Owner = this;
                }
            }
            return true;
        }
        return true;
    }
    unknown_76 = true;
    return false;
}
