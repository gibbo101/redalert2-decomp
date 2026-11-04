// bool MapClass::Unknown_00565EB0(CellClass &cell, int layer, DynamicVectorClass<unsigned short> *list, int arg4) (0x00565EB0)
// TibSun Build_Reachable_Subzones: floods the layer's (1 << (layer + 1)) square block of
// cells from the cell through the cells of the same subzone that the techno (arg4) can enter
// (slot 101 answers 0, or the cell's land is not impassable for its movement zone),
// collecting the other subzones it touches. True when a cell of the starting subzone in the
// block was not reached; otherwise every connection of the starting subzone that the flood
// did not touch is added to list.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/crt_memory.hpp"
#include "shared/zone_table.hpp"
// @ref ?_subzone_flood_stack@?1??Unknown_00565EB0@MapClass@@QAE_NPAVCellClass@@HABV?$DynamicVectorClass@G@@PBVObjectClass@@@Z@4PAPAV3@A=00a6f820
// @ref ?_subzone_flood_visited@?1??Unknown_00565EB0@MapClass@@QAE_NPAVCellClass@@HABV?$DynamicVectorClass@G@@PBVObjectClass@@@Z@4PAY07DA=00a6fbf0
// @ref _?_subzone_flood_stack@?1??Unknown_00565EB0@MapClass@@QAE_NPAVCellClass@@HABV?$DynamicVectorClass@G@@PBVObjectClass@@@Z@4PAPAV3@A=00a6f820
// @ref _?_subzone_flood_visited@?1??Unknown_00565EB0@MapClass@@QAE_NPAVCellClass@@HABV?$DynamicVectorClass@G@@PBVObjectClass@@@Z@4PAY07DA=00a6fbf0
// @ref ??_7?$DynamicVectorClass@G@@6B@=0079c554
// @ref ??_7?$VectorClass@G@@6B@=0079c534
// @ref ??0?$VectorClass@G@@QAE@IPBG@Z=0042b620
// @ref ??_E?$DynamicVectorClass@G@@UAEPAXI@Z=0042b4c0
// @ref ??_G?$DynamicVectorClass@G@@UAEPAXI@Z=0042b4c0
// @ref ??8?$VectorClass@G@@UBE_NABV0@@Z=0042b170
// @ref ?Resize@?$DynamicVectorClass@G@@UAE_NHPBG@Z=0042b2f0
// @ref ?Clear@?$DynamicVectorClass@G@@UAEXXZ=0042ae60
// @ref ?ID@?$DynamicVectorClass@G@@UAEHABG@Z=0042b3a0
// @ref ?ID@?$DynamicVectorClass@G@@UAEHPBG@Z=0042ae90
// @ref ?Fetch@?$VectorClass@G@@UBEGH@Z=0042aeb0
// @ref ??_E?$VectorClass@G@@UAEPAXI@Z=0042b470
// @ref ??_G?$VectorClass@G@@UAEPAXI@Z=0042b470
// @ref ?Resize@?$VectorClass@G@@UAE_NHPBG@Z=0042b1b0
// @ref ?Clear@?$VectorClass@G@@UAEXXZ=0042b260
// @ref ?ID@?$VectorClass@G@@UAEHABG@Z=0042b290
// @ref ?ID@?$VectorClass@G@@UAEHPBG@Z=0042b2d0
// @ref ?Unknown_00565EB0@MapClass@@QAE_NAAVCellClass@@HPAV?$DynamicVectorClass@G@@H@Z=00565eb0

inline unsigned short Cell_Subzone(MapClass *map, Cell const &cell, int layer)
{
    return ((short *)(map->unknown_6c + map->Unknown_0054FAB0(cell) * 10))[layer];
}

bool MapClass::Unknown_00565EB0(CellClass *cptr, int layer, DynamicVectorClass<unsigned short> const &connections, ObjectClass const *foot)
{
    static CellClass *_subzone_flood_stack[64];
    static char _subzone_flood_visited[8][8];

    int dim = 1 << (layer + 1);

    int facing;
    DynamicVectorClass<unsigned short> list;
    list.Clear();

    if (dim > 0) {
        for (facing = 0; facing < dim; facing++) {
            memset(_subzone_flood_visited[facing], 0, dim);
        }
    }

    unsigned short start_subzone = Cell_Subzone(this, cptr->MapCoords, layer);
    unsigned short other_subzone = 0;
    _subzone_flood_stack[0] = cptr;
    _subzone_flood_visited[(dim - 1) & cptr->MapCoords.X][(dim - 1) & cptr->MapCoords.Y] = 1;
    int count = 1;

    int *mzone_table = unknown_table_7e00c4[foot->unknown_slot32()->unknown_500];

    while (true) {

        facing = 0;
        count--;
        CellClass **slot = &_subzone_flood_stack[count];
        CellClass *cur = *slot;

        while (true) {

            CellClass *adj = &cur->Adjacent_Cell(facing);
            int ax = (dim - 1) & adj->MapCoords.X;
            int ay = (dim - 1) & adj->MapCoords.Y;
            unsigned short adj_subzone = Cell_Subzone(this, adj->MapCoords, layer);

            if (foot->unknown_slot101(adj, facing, adj->unknown_11b, 0, true) == 0 || mzone_table[adj->unknown_4c] != 1) {

                if (adj_subzone == start_subzone) {

                    if (!_subzone_flood_visited[ax][ay]) {
                        _subzone_flood_visited[ax][ay]++;
                        _subzone_flood_stack[count] = adj;
                        count++;
                    }

                } else if (adj_subzone != other_subzone) {

                    if (adj_subzone != 0) {
                        other_subzone = adj_subzone;

                        int j;
                        for (j = list.Count() - 1; j >= 0; j--) {
                            if (list[j] == adj_subzone) {
                                break;
                            }
                        }
                        if (j == -1) {
                            list.Add(adj_subzone);
                        }
                    }
                }
            }

            facing++;
            if (facing >= 8) {
                break;
            }
        }

        if (count <= 0) {
            break;
        }
    }

    int x = cptr->MapCoords.X;
    int y = cptr->MapCoords.Y;
    int bx = (dim - 1) & x;
    int by = (dim - 1) & y;

    for (facing = 0; facing < dim; facing++) {
        for (int col = 0; col < dim; col++) {

            Cell c = cptr->MapCoords + Cell(bx, by);

            if (Unknown_0055A660(c, true)) {
                if (start_subzone == ((unsigned short *)(unknown_6c + Unknown_0054FAB0(c) * 10))[layer] && !_subzone_flood_visited[facing][col]) {
                    return true;
                }
            }
        }
    }

    DynamicVectorClass<SubzoneConnectionStruct> &track = SubzoneTracking[layer][start_subzone].Connections;
    SubzoneConnectionStruct *vec = &track[0];
    for (int i = track.Count() - 1; i >= 0; i--) {
        SubzoneConnectionStruct &conn = vec[i];
        int sub = conn.unknown_00;
        int j;
        for (j = list.Count() - 1; j >= 0; j--) {
            if (list[j] == sub) {
                break;
            }
        }
        if (j == -1) {
            ((DynamicVectorClass<unsigned short> &)connections).Add(sub);
        }
    }

    return false;
}
