#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/tactical.hpp"
#include "shared/map_view.hpp"
extern Rect unknown_rect_839630;
extern "C" int __cdecl abs(int value);
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ??RRandom2Class@@QAEHXZ=00638840
// Recompute this vein connection and its cardinal neighbors, redrawing their old and new areas.
void CellClass::unknown_47a7a0()
{
    Rect dirty(0,0,0,0);
    dirty=Union(dirty,Union(unknown_474eb0(),unknown_475100()));
    OverlayData=0;
    int frame=unknown_47a5a0();
    if(frame==0 || unknown_11c) OverlayIndex=-1;
    else OverlayData=3*frame+abs(unknown_id_source_a3d290->Random()()%3);
    Map.Unknown_00631570(MapCoords);
    for(int direction=0;direction<8;direction+=2) {
        CellClass &adjacent=(CellClass&)((CellClass const*)this)->Adjacent_Cell(direction);
        if(adjacent.unknown_11c==0 && adjacent.OverlayIndex==126 && adjacent.OverlayData<48) {
            int neighbor_frame=adjacent.unknown_47a5a0();
            Rect area(0,0,0,0);
            area=Union(area,Union(adjacent.unknown_474eb0(),adjacent.unknown_475100()));
            if(neighbor_frame==0) adjacent.OverlayIndex=-1;
            else adjacent.OverlayData=3*neighbor_frame+abs(unknown_id_source_a3d290->Random()()%3);
            adjacent.Unknown_00472540(-1);
            area=Union(area,Union(adjacent.unknown_474eb0(),adjacent.unknown_475100()))-unknown_rect_839630.Top_Left();
            unknown_tactical_83996c->Register_Dirty_Area(area,false);
            Map.Unknown_00631570(adjacent.MapCoords);
        }
    }
    dirty=Union(dirty,Union(unknown_474eb0(),unknown_475100()))-unknown_rect_839630.Top_Left();
    unknown_tactical_83996c->Register_Dirty_Area(dirty,false);
    Unknown_00472540(-1);
}
