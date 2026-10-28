// FoggedObjectClass::FoggedObjectClass(CoordStruct const &coord, int arg24, int arg2c) (0x004C00F0)
// A fogged object of kind 0x14 at a coordinate: its redraw rectangle is the union of the
// cell's two bounds moved into view coordinates, and it is listed in Array and Index.
#include "shared/fogged_object.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/tactical.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7FoggedObjectClass@@6BIPersistStream@@@=007a1148
// @ref ??_7FoggedObjectClass@@6BIRTTITypeInfo@@@=007a112c
// @ref ??_7FoggedObjectClass@@6BINoticeSink@@@=007a1124
// @ref ??_7FoggedObjectClass@@6BINoticeSource@@@=007a111c
// @ref ??_7?$DynamicVectorClass@UDrawRecord@FoggedObjectClass@@@@6B@=007a11b0
// @ref ?Array@FoggedObjectClass@@2V?$DynamicVectorClass@PAVFoggedObjectClass@@@@A=00865e90
// @ref ?Index@FoggedObjectClass@@=00865e40
// @ref ?unknown_474eb0@CellClass@@QBE?AVRect@@XZ=00474eb0
// @ref ?unknown_475100@CellClass@@QBE?AVRect@@XZ=00475100
// @ref ??0?$VectorClass@UDrawRecord@FoggedObjectClass@@@@QAE@IPBUDrawRecord@FoggedObjectClass@@@Z=004c2520
FoggedObjectClass::FoggedObjectClass(CoordStruct const &coord, int arg24, int arg2c)
    : unknown_24(arg24), unknown_28(0), unknown_2c(arg2c), unknown_30(0x14), Coord(coord),
      unknown_50(Map[coord].unknown_11b), unknown_54(-1), unknown_58(0), unknown_74(true)
{
    CellClass &cell = Map[coord];
    unknown_40 = Union(cell.unknown_474eb0(), cell.unknown_475100());
    unknown_40.X += unknown_tactical_83996c->unknown_b0.X;
    unknown_40.Y += unknown_tactical_83996c->unknown_b0.Y;
    unknown_40 -= Point2D(unknown_int_839630, unknown_int_839634);
    Array.Add(this);
    Index.Add_Index(unknown_index_key(unknown_coord_cell(Coord), unknown_30), this);
}
