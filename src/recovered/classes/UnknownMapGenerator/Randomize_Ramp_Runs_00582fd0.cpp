// Replaces ramp tiles on sloped runs with a random variant, looking one cell south and east of each cell. Operation name is a hypothesis.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/cell_class.hpp"
#include "shared/map_region.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/tileset_index.hpp"
void __fastcall Place_Tile_Footprint_005883f0(int tile,Cell const &position,int region,int height);
void UnknownMapGenerator::unknown_00582fd0()
{
    Map.Unknown_0055A550();
    CellClass *cellptr=Map.Unknown_0055A490();

    while(cellptr!=0) {
        if(cellptr->IsoTileIndex>=unknown_tileset_a52e68 && cellptr->IsoTileIndex<unknown_tileset_a52e68+40) {
            CellClass &south=cellptr->Adjacent_Cell(4);
            CellClass &east=cellptr->Adjacent_Cell(2);

            if(cellptr->IsoTileIndex==south.IsoTileIndex && (unsigned char)cellptr->unknown_11a>(unsigned char)south.unknown_11a) {
                int tile=Randomize_Ramp_Tile_00582b30(cellptr->IsoTileIndex);

                if(tile!=cellptr->IsoTileIndex) {
                    int subtile=(unsigned char)south.unknown_11a;
                    IsometricTileTypeClass *type=IsoTileTypes[cellptr->IsoTileIndex];
                    Cell origin=south.MapCoords-Cell(subtile%type->unknown_2b4,subtile/type->unknown_2b4);
                    Place_Tile_Footprint_005883f0(tile,origin,UnknownMapGenerationCell::Get_Region(origin),-1);
                }
            }

            if(cellptr->IsoTileIndex==east.IsoTileIndex && (unsigned char)cellptr->unknown_11a>(unsigned char)east.unknown_11a) {
                int tile=Randomize_Ramp_Tile_00582b30(cellptr->IsoTileIndex);

                if(tile!=cellptr->IsoTileIndex) {
                    IsometricTileTypeClass *type=IsoTileTypes[cellptr->IsoTileIndex];
                    int subtile=(unsigned char)east.unknown_11a;
                    Cell origin=east.MapCoords-Cell(subtile%type->unknown_2b4,subtile/type->unknown_2b4);
                    Place_Tile_Footprint_005883f0(tile,origin,UnknownMapGenerationCell::Get_Region(origin),-1);
                }
            }
        }

        cellptr=Map.Unknown_0055A490();
    }
}
