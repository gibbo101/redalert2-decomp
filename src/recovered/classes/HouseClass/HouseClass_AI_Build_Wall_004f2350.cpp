// AI_Build_Wall (TibSun twin): plan a perimeter of walls and gates around the base area, original 0x004F2350,
// 2,405 B body. The `buildings` check is reused as the soft-block flag (one byte slot) and the node initialization is an inline hypothesis.
// @ref ??_7?$DynamicVectorClass@VBaseNodeClass@@@@6B@=0079c5c0
// @ref ??_7?$VectorClass@VBaseNodeClass@@@@6B@=0079c600
// @ref ??_E?$DynamicVectorClass@VBaseNodeClass@@@@UAEPAXI@Z=0042d160
// @ref ??8?$VectorClass@VBaseNodeClass@@@@UBE_NABV0@@Z=0042cc80
// @ref ?Resize@?$DynamicVectorClass@VBaseNodeClass@@@@UAE_NHPBVBaseNodeClass@@@Z=0042cce0
// @ref ?Clear@?$DynamicVectorClass@VBaseNodeClass@@@@UAEXXZ=0042cb90
// @ref ?ID@?$DynamicVectorClass@VBaseNodeClass@@@@UAEHABVBaseNodeClass@@@Z=0042cdd0
// @ref ?ID@?$DynamicVectorClass@VBaseNodeClass@@@@UAEHPBVBaseNodeClass@@@Z=0042cbc0
// @ref ?Fetch@?$VectorClass@VBaseNodeClass@@@@UBE?AVBaseNodeClass@@H@Z=0042cbe0
// @ref ??_E?$VectorClass@VBaseNodeClass@@@@UAEPAXI@Z=0042d340
// @ref ?Resize@?$VectorClass@VBaseNodeClass@@@@UAE_NHPBVBaseNodeClass@@@Z=0042d1b0
// @ref ?Clear@?$VectorClass@VBaseNodeClass@@@@UAEXXZ=0042d2a0
// @ref ?ID@?$VectorClass@VBaseNodeClass@@@@UAEHABVBaseNodeClass@@@Z=0042d2d0
// @ref ?ID@?$VectorClass@VBaseNodeClass@@@@UAEHPBVBaseNodeClass@@@Z=0042d320
// @ref _wall_step_facings=007a2cd0
// @ref _wall_adjacent_facings=007a2ce0
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/cell_class.hpp"
#include "shared/house_adjacent.hpp"
#include "shared/crt_memory.hpp"
static FacingType const wall_step_facings[4] = {FACING_E,FACING_E,FACING_S,FACING_S};
static FacingType const wall_adjacent_facings[4] = {FACING_N,FACING_S,FACING_W,FACING_E};
void HouseClass::AI_Build_Wall()
{
    Rect &area = unknown_55f0.unknown_54;
    Rect perimeter=area;
    --perimeter.X; --perimeter.Y; perimeter.Width+=2; perimeter.Height+=2;
    unknown_55f0.unknown_64=perimeter;
    DynamicVectorClass<BaseNodeClass> walls;
    DynamicVectorClass<BaseNodeClass> gates;
    Cell starts[4] = {
        Cell(perimeter.X,perimeter.Y),
        Cell(perimeter.X,perimeter.Y+perimeter.Height-1),
        Cell(perimeter.X,perimeter.Y+1),
        Cell(perimeter.X+perimeter.Width-1,perimeter.Y+1)
    };
    Cell ends[4] = {
        Cell(perimeter.X+perimeter.Width,perimeter.Y),
        Cell(perimeter.X+perimeter.Width,perimeter.Y+perimeter.Height-1),
        Cell(perimeter.X,perimeter.Y+perimeter.Height-1),
        Cell(perimeter.X+perimeter.Width-1,perimeter.Y+perimeter.Height-1)
    };
    BuildingTypeClass *wall = unknown_func_4ef600(Rules->ConcreteWalls);
    BuildingTypeClass *east_west_gate = unknown_func_4ef600(Rules->EWGates);
    BuildingTypeClass *north_south_gate = unknown_func_4ef600(Rules->NSGates);
    BuildingTypeClass *gate_types[4] = {east_west_gate,east_west_gate,north_south_gate,north_south_gate};
    Cell beginning(0,0);
    int elevation = Map[unknown_55f0.unknown_50].unknown_11b;
    int side;
    for (side=0;side<4;++side) {
        FacingType direction=wall_step_facings[side];
        Cell cell=starts[side];
        int length=0;
        bool running=false;
        int soft_blocks=0;
        while (cell != ends[side]) {
            CellClass *current=&Map[cell];
            Cell adjacent=Adjacent_Cell(cell,wall_adjacent_facings[side]);
            CellClass *neighbor=&Map[adjacent];
            int land=current->unknown_ec;
            int adjacent_land=neighbor->unknown_ec;
            bool level=abs(current->unknown_11b-elevation)<=2;
            bool ground=land!=3 && land!=2 && land!=8 && adjacent_land!=3 && adjacent_land!=2 && adjacent_land!=8;
            bool overlay=current->OverlayIndex==-1;
            bool buildings=!current->unknown_4717b0() && !neighbor->unknown_4717b0();
            bool terrain=!current->Cell_Terrain() && !neighbor->Cell_Terrain();
            bool flat=current->unknown_11c==0;
            bool visible=Map.Unknown_0055A660(cell,true);
            if (level && ground && overlay && buildings && terrain && flat && visible) {
                if (!running) { running=true; length=1; beginning=cell; }
                else ++length;
            } else {
buildings=!(level && ground && buildings && terrain && visible);
 if (buildings) { if (soft_blocks>0) { buildings=false; soft_blocks=0; } } else ++soft_blocks;
                if (length>=5 || !buildings) {
                    Cell position=beginning;
                    int placed=0;
                    int middle=length/2-1;
                    while (placed<length) {
                        if (placed==middle && buildings) {
                            gates.Add(BaseNodeClass(gate_types[side]->ArrayIndex,position));
                            placed+=3;
                            position=Adjacent_Cell(Adjacent_Cell(Adjacent_Cell(position,direction),direction),direction);
                        } else {
                            walls.Add(BaseNodeClass(wall->ArrayIndex,position));
                            ++placed;
                            position=Adjacent_Cell(position,direction);
                        }
                    }
                }
                length=0;
                running=false;
            }
            cell=Adjacent_Cell(cell,direction);
        }
        if (length>=5) {
            Cell position=beginning;
            int placed=0;
            int middle=length/2-1;
            while (placed<length) {
                if (placed==middle) {
                    gates.Add(BaseNodeClass(gate_types[side]->ArrayIndex,position));
                    placed+=3;
                    position=Adjacent_Cell(Adjacent_Cell(Adjacent_Cell(position,direction),direction),direction);
                } else {
                    walls.Add(BaseNodeClass(wall->ArrayIndex,position));
                    ++placed;
                    position=Adjacent_Cell(position,direction);
                }
            }
        }
    }
    for (int w=0;w<walls.Count();++w) unknown_55f0.Nodes.Add(walls[w]);
    for (int g=0;g<gates.Count();++g) unknown_55f0.Nodes.Add(gates[g]);
    unknown_55f0.unknown_54=unknown_55f0.unknown_64;
}
