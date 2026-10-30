#include "shared/unknown_map_generator.hpp"
#include "shared/map_view.hpp"
// @ref ?Expand_High_Ground@MapClass@@=0055b210
bool UnknownMapGenerator::Expand_All_High_Ground_00583740()
{
    bool success=true;
    Map.Unknown_00498F10(0);
    Map.Unknown_0055A550();
    CellClass *cell=Map.Unknown_0055A490();
    while (cell!=0) {
        if (!success) break;
        success=Map.Expand_High_Ground(cell,-1);
        cell=Map.Unknown_0055A490();
    }
    return success;
}
