// FoggedObjectClass::FoggedObjectClass(CoordStruct const &coord, int arg54, unsigned int arg58) (0x004C03B0)
// A fogged object of kind 0x1D standing at the cell's level height: a 60x30 redraw
// rectangle around its screen position, listed in Array and Index.
#include "shared/fogged_object.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7FoggedObjectClass@@6BIPersistStream@@@=007a1148
// @ref ??_7FoggedObjectClass@@6BIRTTITypeInfo@@@=007a112c
// @ref ??_7FoggedObjectClass@@6BINoticeSink@@@=007a1124
// @ref ??_7FoggedObjectClass@@6BINoticeSource@@@=007a111c
// @ref ??_7?$DynamicVectorClass@UDrawRecord@FoggedObjectClass@@@@6B@=007a11b0
// @ref ?Array@FoggedObjectClass@@2V?$DynamicVectorClass@PAVFoggedObjectClass@@@@A=00865e90
// @ref ?Index@FoggedObjectClass@@=00865e40
// @ref ??0?$VectorClass@UDrawRecord@FoggedObjectClass@@@@QAE@IPBUDrawRecord@FoggedObjectClass@@@Z=004c2520
FoggedObjectClass::FoggedObjectClass(CoordStruct const &coord, int arg54, unsigned int arg58)
    : unknown_24(-1), unknown_28(0), unknown_2c(0), unknown_30(0x1D),
      unknown_50(Map[coord].unknown_11b), unknown_54(arg54), unknown_58(arg58), unknown_74(true)
{
    CellClass &cell = Map[coord];
    CoordStruct position = coord;
    position.Z = cell.unknown_11b * unknown_geometry_g;
    CoordStruct &at = Coord;
    at = position;
    Point2D pixel;
    unknown_tactical_83996c->Unknown_006A29D0(position, pixel);
    pixel -= Point2D(30, 15);
    unknown_40 = Rect(pixel.X, pixel.Y, 60, 30);
    unknown_40.X += unknown_tactical_83996c->unknown_b0.X;
    unknown_40.Y += unknown_tactical_83996c->unknown_b0.Y;
    Array.Add(this);
    Index.Add_Index(unknown_index_key(XY_Cell(at.X / 256, at.Y / 256), unknown_30), this);
}
