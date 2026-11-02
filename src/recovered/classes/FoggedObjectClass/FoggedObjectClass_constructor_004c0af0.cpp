// FoggedObjectClass::FoggedObjectClass(AnimClass *anim) (0x004C0AF0)
// A fogged copy of an animation: one draw record for its type, listed in Array and Index.
#include "shared/fogged_object.hpp"
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7FoggedObjectClass@@6BIPersistStream@@@=007a1148
// @ref ??_7FoggedObjectClass@@6BIRTTITypeInfo@@@=007a112c
// @ref ??_7FoggedObjectClass@@6BINoticeSink@@@=007a1124
// @ref ??_7FoggedObjectClass@@6BINoticeSource@@@=007a111c
// @ref ??_7?$DynamicVectorClass@UDrawRecord@FoggedObjectClass@@@@6B@=007a11b0
// @ref ?Array@FoggedObjectClass@@2V?$DynamicVectorClass@PAVFoggedObjectClass@@@@A=00865e90
// @ref ?Index@FoggedObjectClass@@=00865e40
// @ref ??0?$VectorClass@UDrawRecord@FoggedObjectClass@@@@QAE@IPBUDrawRecord@FoggedObjectClass@@@Z=004c2520
FoggedObjectClass::FoggedObjectClass(AnimClass *anim)
    : unknown_24(-1), unknown_28(0), unknown_2c(0), unknown_30(0x24), Coord(anim->Coord),
      unknown_50(Map[CoordStruct(anim->Coord)].unknown_11b), unknown_54(-1), unknown_58(0), unknown_74(true)
{
    unknown_40 = anim->unknown_slot73();
    unknown_40.X += unknown_tactical_83996c->TacPixelX;
    unknown_40.Y += unknown_tactical_83996c->TacPixelY;
    Array.Add(this);
    DrawRecord record;
    record.Type = anim->Class;
    DrawRecords.Add(record);
    Index.Add_Index(unknown_index_key(XY_Cell(Coord.X / 256, Coord.Y / 256), unknown_30), this);
}
