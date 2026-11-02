// 0x0051FC90: adds a storm cloud over cell: a random WeatherConClouds anim,
// raised by half the height of the first WeatherConBolts image (in leptons),
// joins the manifesting clouds and the present clouds. Nothing happens at the
// zero coordinate.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
#include "shared/anim.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?CloudsPresent@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51880
// @ref ?CloudsManifesting@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51908
// @ref _unknown_geometry_g=00a51930
// @ref _unknown_geometry_j=00a51920
// @ref _unknown_geometry_l=00a518e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_006A29B0@@YIHH@Z=006a29b0
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ??2@YAPAXI@Z=00782017

void __stdcall Unknown_0051FC90(Cell cell)
{
    CellClass &cellptr = Map[cell];
    int half = ((ShapeFileStruct *)Rules->WeatherConBolts[0]->unknown_slot39())->Height / 2;
    int height = Unknown_006A29B0(half);
    CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128,
        cellptr.unknown_11b * unknown_geometry_g + height + ((cellptr.unknown_140 & 0x100) ? unknown_geometry_j : 0));
    if (coord == unknown_geometry_l) {
        return;
    }
    int pick = unknown_id_source_a3d290->Random()();
    AnimTypeClass *type = Rules->WeatherConClouds[(unsigned)pick % Rules->WeatherConClouds.Count()];
    AnimClass *anim = new AnimClass(type, coord, 0, 1, 0x600, 0);
    IonStormClass::CloudsManifesting.Add(anim);
    IonStormClass::CloudsPresent.Add(anim);
}
