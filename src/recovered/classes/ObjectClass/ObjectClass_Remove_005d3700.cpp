// Existing ObjectClass removal interface, diagnostic only.
#include "shared/object_type.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_list_832470.hpp"
// Existing shape-file header supports a unit's own shared empty rectangle.
// Keep the actual Rect initializer; do not suppress emitted startup output.
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
extern bool unknown_flag_a40958;
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Remove@DisplayClass@@QAEXPAVObjectClass@@@Z=00499a90
// @ref ?Unknown_00405D50@UnknownAudioController@@QAEXXZ=00405d50
// @ref ?Unknown_00405FE0@UnknownAudioController@@QAEXXZ=00405fe0
// @ref ?Remove@UnknownList832470@@QAEXPAVObjectClass@@@Z=0053e370
// @ref ?Unknown_006A29D0@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref ?Unknown_006A3020@Tactical@@QAEXVRect@@H@Z=006a3020
// @ref _unknown_static_rect=00a72ed0
bool ObjectClass::unknown_slot52()
{
    if (!unknown_flag_a40958 || unknown_76) return false;
    unknown_slot81();
    unknown_slot54(true);
    unknown_slot71(0);
    Map.Remove(this);
    unknown_3c.Unknown_00405D50();
    unknown_50.Unknown_00405FE0();
    if (Class_Of() && Class_Of()->unknown_204) {
        if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5 ||
            Fetch_ID() != -2)
            unknown_list_832470.Remove(this);
    }
    if (Class_Of() && Class_Of()->unknown_ac) {
        Point2D pixel;
        CoordStruct location = Center_Coord();
        unknown_tactical_83996c->Unknown_006A29D0(location, pixel);
        ShapeFileStruct *shape = reinterpret_cast<ShapeFileStruct *>(Class_Of()->unknown_ac);
        Point2D half;
        half.X = shape->Width / 2;
        half.Y = shape->Height / 2;
        pixel.X = (int)((unsigned int)pixel.X - (unsigned int)half.X);
        pixel.Y = (int)((unsigned int)pixel.Y - (unsigned int)half.Y);
        unknown_tactical_83996c->Unknown_006A3020(
            Rect(pixel.X, pixel.Y, shape->Width, shape->Height), 1);
    }
    unknown_slot69();
    unknown_76 = true;
    unknown_75 = false;
    return true;
}
