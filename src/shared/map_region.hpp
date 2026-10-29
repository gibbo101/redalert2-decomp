// Original MapRegionClass identity: DynamicVectorClass<MapRegionClass *>
// RTTI007A5D90; constructor0056D870 registers itself in that list.
// Size0x50: original allocation0056E6F6; vector+28 and Rect+40 in constructor.
#ifndef RA2_SHARED_MAP_REGION_HPP
#define RA2_SHARED_MAP_REGION_HPP
#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/vector_class.hpp"
class MapRegionClass {
public:
    DynamicVectorClass<Cell> *Select_Separated_Cells_00576810(DynamicVectorClass<Cell> const &candidates); //operation/reference/constness hypotheses; EAXptr/RET4
    bool Place_Neutral_Building_00571db0(Rect const &area); // hypothesis name; caller establishes MapRegion receiver, RET4
    void unknown_0056eac0(int count,int mark);
    void Update_Cell_Marks_005707a0();
    DynamicVectorClass< ::Cell > *Collect_Boundary_Cells_0056ed10();
    bool Expand_Cells_005702b0();
    void Collect_Neighbor_Regions_005709c0();
    void *unknown_00;
    DynamicVectorClass<int> *NeighborRegionIndices; // +04, originalnew0x18/vptr79DA94 at5709E8
    int Index; // +08, assigned increasing ID by0056D870
    int CellCount;
    int unknown_10;
    unsigned char unknown_14;
    ::Cell Origin; // +16; one preceding padding byte
    bool unknown_1a,unknown_1b;
    int unknown_1c,unknown_20;
    bool unknown_24;
    DynamicVectorClass< ::Cell > Cells; // +28
    ::Rect Bounds; // +40
};
// A separate0x50-byte map-generation grid record; formal original name unknown.
struct UnknownMapGenerationCell {
    ::Cell Position;
    unsigned char unknown_04[0x1c];
    double unknown_20; // original585240 initializes,5852C0 compares as x87qword
    double unknown_28; // same; operational names remain unknown
    unsigned char unknown_30[8];
    int RegionIndex;
    int unknown_3c;
    int unknown_40;
    unsigned char Marked;
    unsigned char unknown_45[6];
    unsigned char unknown_4b;
    unsigned char unknown_4c[4];
};
typedef char MapRegionClass_size[(sizeof(MapRegionClass)==0x50)?1:-1];
typedef char MapRegionClass_origin[(((unsigned int)&(((MapRegionClass*)0)->Origin))==0x16)?1:-1];
typedef char MapRegionClass_cells[(((unsigned int)&(((MapRegionClass*)0)->Cells))==0x28)?1:-1];
typedef char MapRegionClass_bounds[(((unsigned int)&(((MapRegionClass*)0)->Bounds))==0x40)?1:-1];
typedef char UnknownMapGenerationCell_size[(sizeof(UnknownMapGenerationCell)==0x50)?1:-1];
extern int unknown_map_region_next_index_a70a28;
extern int unknown_map_cell_side_84e804;
extern int unknown_map_min_a70a1c,unknown_map_max_a70a20;
extern Cell const unknown_adjacent_851a70[8];
extern UnknownMapGenerationCell *unknown_map_cells_a70a24;
#endif
