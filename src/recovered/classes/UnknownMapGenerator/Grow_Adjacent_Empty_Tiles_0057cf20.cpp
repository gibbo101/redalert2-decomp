#include "shared/unknown_map_generator.hpp"
// Map tile-growth operation/name hypotheses; original controller passes its owner in ECX, unused here.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tileset_index.hpp"
#include "shared/vector_class.hpp"
#include "shared/random2.hpp"
#include "shared/map_random.hpp"
// @ref ?unknown_map_random_a705c0@@=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ?unknown_tileset_a52c60@@=00a52c60
// @ref ??0?$VectorClass@PAVCellClass@@@@=0058f040
// @ref ??_7?$DynamicVectorClass@PAVCellClass@@@@6B@=007a5efc
// @ref ??_7?$VectorClass@PAVCellClass@@@@6B@=007a59b8
// @ref __real@8@3fdf8000000080000000=007a5dd0
// @ref __ftol=0077f110
void UnknownMapGenerator::Grow_Adjacent_Empty_Tiles_0057cf20()
{
    DynamicVectorClass<CellClass *> candidates;
    candidates.Set_Growth_Step(10000);
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        if(cell->unknown_47b9c0()) {
            for(int facing=0;facing<8;facing+=2) {
                CellClass *adjacent=&cell->Adjacent_Cell(facing);
                if(adjacent->unknown_47b590())candidates.Add(adjacent);
            }
        }
    }
    int remaining=candidates.Count()/3;
    remaining=remaining>1000?1000:remaining;
    for(int step=0;step<remaining;++step) {
        unsigned maximum=(unsigned)candidates.Count()-1;
        struct Range { double Span; };
        Range range={(unsigned)(maximum+1)};
        unsigned index;
        do {
            index=(unsigned)((unsigned)unknown_map_random_a705c0()*range.Span*(1.0/4294967295.0));
        } while(index>maximum);
        CellClass *cell=candidates[index];
        candidates.Delete((int)index);
        cell->IsoTileIndex=unknown_tileset_a52c60;
        for(int facing=0;facing<8;facing+=2) {
            CellClass *adjacent=&cell->Adjacent_Cell(facing);
            if(adjacent->unknown_47b590())candidates.Add(adjacent);
        }
    }
}
