// MapClass::Unknown_00564B60: registers the center and both side subzone pairs of a bridge or tube connection.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/tileset_index.hpp"
#include "shared/tube.hpp"
#include "shared/cell_subzone.hpp"
#include "shared/path_estimator.hpp"
extern int unknown_bridge_side_facings_7e0454[];
// @ref ?unknown_bridge_side_facings_7e0454@@3PAHA=007e0454
// @ref ?Unknown_0047A130@CellClass@@QAEPAVTubeClass@@XZ=0047a130
// @ref ?Unknown_00427060@UnknownPathEstimator@@SI?AVCell@@ABV2@HPBH@Z=00427060

inline int Zone_Pack32(int from, int to)
{
    return (from << 16) | to;
}

inline int Zone_Pack8(int from, int to)
{
    return ((from & 15) << 4) | (to & 15);
}

inline void Set_Zone_Record(HashObject<unsigned int, SubzoneConnectionStruct> &record, unsigned int key, SubzoneConnectionStruct const &value)
{
    record.Key = key;
    record.Value.unknown_00 = value.unknown_00;
    record.Value.unknown_04 = value.unknown_04;
}

void MapClass::Unknown_00564B60(ZoneConnectionClass *connection, int layer)
{
    HashObject<unsigned int, SubzoneConnectionStruct> record;
    HashTableClass<unsigned int, SubzoneConnectionStruct> *table = unknown_7c[layer];
    Cell from = connection->From;
    Cell to = connection->To;
    Cell enter1;
    Cell enter2;
    Cell exit1;
    Cell exit2;
    CellClass *from_cell = &Map[from];
    if (!from_cell->unknown_47b960() && !from_cell->unknown_47b980()) {
        TubeClass *tube = from_cell->Unknown_0047A130();
        int facing = tube->Facing;
        enter1 = Adjacent_Cell(from, facing + 2);
        enter2 = from + AdjacentCell[(facing - 2) & 7];
        CellClass *enterptr1 = &Map[enter1];
        TubeClass *tube1 = enterptr1->Unknown_0047A130();
        CellClass *enterptr2 = &Map[enter2];
        TubeClass *tube2 = enterptr2->Unknown_0047A130();
        if (!tube1 || !tube2) return;
        int count1 = tube1->unknown_1c0;
        exit1 = UnknownPathEstimator::Unknown_00427060(enter1, count1, tube1->Directions);
        int count2 = tube2->unknown_1c0;
        exit2 = UnknownPathEstimator::Unknown_00427060(enter2, count2, tube2->Directions);
    } else {
        bool is_bridge = from_cell->unknown_47b960();
        int tile_set = unknown_tileset_a52c74;
        int tile;
        if (!is_bridge) { tile = from_cell->IsoTileIndex; tile_set = unknown_tileset_a6cb68; }
        else tile = from_cell->IsoTileIndex;
        int facing = unknown_bridge_side_facings_7e0454[tile - tile_set];
        enter1 = Adjacent_Cell(from, facing);
        enter2 = Adjacent_Cell(from, facing - 4);
        exit1 = Adjacent_Cell(to, facing);
        exit2 = Adjacent_Cell(to, facing - 4);
    }
    {
        int from_id = ((CellSubzoneStruct *)unknown_6c)[Unknown_0054FAB0(from)].SubzoneID[layer];
        int to_id = ((CellSubzoneStruct *)unknown_6c)[Unknown_0054FAB0(to)].SubzoneID[layer];
        int value = Zone_Pack32(from_id, to_id);
        Set_Zone_Record(record, value, SubzoneConnectionStruct(value, false));
        table->Add_Object(Zone_Pack8(from_id, to_id), record);
    }
    {
        int from_id = ((CellSubzoneStruct *)unknown_6c)[Unknown_0054FAB0(enter1)].SubzoneID[layer];
        int to_id = ((CellSubzoneStruct *)unknown_6c)[Unknown_0054FAB0(exit1)].SubzoneID[layer];
        int value = Zone_Pack32(from_id, to_id);
        Set_Zone_Record(record, value, SubzoneConnectionStruct(value, false));
        table->Add_Object(Zone_Pack8(from_id, to_id), record);
    }
    {
        int from_id = ((CellSubzoneStruct *)unknown_6c)[Unknown_0054FAB0(enter2)].SubzoneID[layer];
        int to_id = ((CellSubzoneStruct *)unknown_6c)[Unknown_0054FAB0(exit2)].SubzoneID[layer];
        int value = Zone_Pack32(from_id, to_id);
        Set_Zone_Record(record, value, SubzoneConnectionStruct(value, false));
        table->Add_Object(Zone_Pack8(from_id, to_id), record);
    }
}
