// TibSun Connect_Regions_With_Bridge: spans a low bridge across the gap between two regions.
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
bool __fastcall Can_Place_Paved_Road_00588a30(Rect const &area,bool overlap,bool end);
bool __fastcall Can_Place_Paved_Road_End_00588c20(Rect const &area,bool allowRoad);
void __fastcall Place_Tile_Footprint_005883f0(int tile,Cell const &position,int region=-1,int height=-1);
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
// Same-file form of the region cell pick (TibSun Pick_Random_Cell); this unit expands it.
inline Cell Pick_Region_Cell(MapRegionClass const *region)
{
    int count=unknown_map_cell_side_84e804*unknown_map_cell_side_84e804;
    unsigned index;
    do {
        index=Map_Random_Range_005797a0(0,count-1);
    } while(unknown_map_cells_a70a24[index].RegionIndex!=region->Index || (unsigned char)unknown_map_cells_a70a24[index].Position.Equal_004fef20(Cell(0,0)));
    return unknown_map_cells_a70a24[index].Position;
}

bool MapRegionClass::Connect_Regions_With_Bridge_00570bc0(MapRegionClass *region1,MapRegionClass *region2)
{
    int id1 = region1->Index;
    int id2 = region2->Index;

    int tries = 0;
    bool result = false;

    for (; tries < 200; tries++) {
        if (result) {
            break;
        }

        Cell cell = Pick_Region_Cell(this);

        Rect rect1(cell.X - 1, cell.Y, 3, 1);
        Rect rect2=rect1;
        Rect rect4(cell.X, cell.Y - 1, 1, 3);
        Rect rect3=rect4;

        bool allow_rect3 = true;
        bool allow_rect1 = true;

        while (!Can_Place_Paved_Road_00588a30(rect1, false, false)) {
            rect1.Y--;
            Cell cell1(rect1.X, rect1.Y);
            Cell cell2(rect1.X + 2, rect1.Y);
            CellClass * cptr1 = &Map[cell1];
            CellClass * cptr2 = &Map[cell2];
            if (!Map.Unknown_0055A660(cell1,true) || !Map.Unknown_0055A660(cell2,true) || cptr1->unknown_47b5e0() || cptr2->unknown_47b5e0()) {
                allow_rect1 = false;
                break;
            }
        }

        if (allow_rect1) {
            if (Can_Place_Paved_Road_00588a30(Rect(rect1.X, rect1.Y - 3, 3, 3), false, false)) {
                while (!Can_Place_Paved_Road_00588a30(rect2, false, false)) {
                    rect2.Y++;
                    Cell cell1(rect2.X, rect2.Y);
                    Cell cell2(rect2.X + 2, rect2.Y);
                    CellClass * cptr1 = &Map[cell1];
                    CellClass * cptr2 = &Map[cell2];
                    if (!Map.Unknown_0055A660(cell1,true) || !Map.Unknown_0055A660(cell2,true) || cptr1->unknown_47b5e0() || cptr2->unknown_47b5e0()) {
                        allow_rect1 = false;
                        break;
                    }
                }

                if (allow_rect1) {
                    if (!Can_Place_Paved_Road_00588a30(Rect(rect2.X, rect2.Y + 1, 3, 3), false, false)) {
                        allow_rect1 = false;
                    }
                }
            } else {
                allow_rect1 = false;
            }
        }

        while (!Can_Place_Paved_Road_00588a30(rect3, false, false)) {
            rect3.X--;
            Cell cell1(rect3.X, rect3.Y);
            Cell cell2(rect3.X, rect3.Y + 2);
            CellClass * cptr1 = &Map[cell1];
            CellClass * cptr2 = &Map[cell2];
            if (!Map.Unknown_0055A660(cell1,true) || !Map.Unknown_0055A660(cell2,true) || cptr1->unknown_47b5e0() || cptr2->unknown_47b5e0()) {
                allow_rect3 = false;
                break;
            }
        }

        if (allow_rect3) {
            if (Can_Place_Paved_Road_00588a30(Rect(rect3.X - 3, rect3.Y, 3, 3), false, false)) {
                while (!Can_Place_Paved_Road_00588a30(rect4, false, false)) {
                    rect4.X++;
                    Cell cell1(rect4.X, rect4.Y);
                    Cell cell2(rect4.X, rect4.Y + 2);
                    CellClass * cptr1 = &Map[cell1];
                    CellClass * cptr2 = &Map[cell2];
                    if (!Map.Unknown_0055A660(cell1,true) || !Map.Unknown_0055A660(cell2,true) || cptr1->unknown_47b5e0() || cptr2->unknown_47b5e0()) {
                        allow_rect3 = false;
                        break;
                    }
                }

                if (allow_rect3) {
                    if (!Can_Place_Paved_Road_00588a30(Rect(rect4.X + 1, rect4.Y, 3, 3), false, false)) {
                        allow_rect3 = false;
                    }
                }
            } else {
                allow_rect3 = false;
            }
        }

        int len1 = 999;
        int len2 = 999;
        int region_a = -1;
        int region_b = -1;
        int region_c = -1;
        int region_d = -1;

        if (allow_rect1) {
            len1 = abs(rect2.Y - rect1.Y);
            region_a = UnknownMapGenerationCell::Get_Region(Cell(rect1.X, rect1.Y));
            region_b = UnknownMapGenerationCell::Get_Region(Cell(rect2.X, rect2.Y));
        }

        if (allow_rect3) {
            len2 = abs(rect4.X - rect3.X);
            region_c = UnknownMapGenerationCell::Get_Region(Cell(rect4.X, rect4.Y));
            region_d = UnknownMapGenerationCell::Get_Region(Cell(rect3.X, rect3.Y));
        }

        if (allow_rect1) {
            if ((region_a != id1 || region_b != id2) && (region_a != id2 || region_b != id1)) {
                allow_rect1 = false;
            }
        }

        if (allow_rect3) {
            if ((region_c != id1 || region_d != id2) && (region_c != id2 || region_d != id1)) {
                allow_rect3 = false;
            }
            if (allow_rect3 && allow_rect1) {
                if (len1 < len2) {
                    allow_rect3 = false;
                } else {
                    allow_rect1 = false;
                }
            }
        }

        Rect bridge(0, 0, 0, 0);
        int max_len = tries / 25 + 8;

        if (allow_rect3 && len2 < max_len) {
            bridge = Rect(rect3.X, rect3.Y, rect4.X - rect3.X + 1, 3);
        } else if (allow_rect1 && len1 < max_len) {
            bridge = Rect(rect1.X, rect1.Y, 3, rect2.Y - rect1.Y + 1);
        }

        if (bridge.Is_Valid() && allow_rect3) {
            if (Is_Bridge_Allowed_00571bc0(bridge)) {
                for (int y = bridge.Y; y < bridge.Y + bridge.Height; y++) {
                    for (int x = bridge.X; x < bridge.X + bridge.Width; x++) {
                        if (x == bridge.X) {
                            Map[Cell(x, y)].OverlayIndex = 0x5e;
                        } else if (x == bridge.X + bridge.Width - 1) {
                            Map[Cell(x, y)].OverlayIndex = 0x5c;
                        } else {
                            Map[Cell(x, y)].OverlayIndex = 0x4a + (x % 4);
                        }
                        Map[Cell(x, y)].OverlayData = y - bridge.Y;
                    }
                }

                if (Can_Place_Paved_Road_End_00588c20(Rect(bridge.X + bridge.Width, bridge.Y - 2, 6, 6), false) && Map_Random_Range_005797a0(0,1)) {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+10, Cell(bridge.X + bridge.Width, bridge.Y));
                } else {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08, Cell(bridge.X + bridge.Width, bridge.Y));
                }

                if (Can_Place_Paved_Road_End_00588c20(Rect(bridge.X - 6, bridge.Y - 2, 6, 6), false) && Map_Random_Range_005797a0(0,1)) {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+9, Cell(bridge.X - 4, bridge.Y));
                } else {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08+2, Cell(bridge.X - 1, bridge.Y));
                }

                if (!Place_Neutral_Building_00571db0(Rect(bridge.X, bridge.Y - 1, 2, 5))) {
                    Place_Neutral_Building_00571db0(Rect(bridge.X - 1, bridge.Y - 2, 3, 7));
                }

                if (!Place_Neutral_Building_00571db0(Rect(bridge.X + bridge.Width - 2, bridge.Y - 1, 2, 5))) {
                    Place_Neutral_Building_00571db0(Rect(bridge.X + bridge.Width - 2, bridge.Y - 2, 3, 7));
                }

                result = true;
            }
        } else if (bridge.Is_Valid()) {
            if (allow_rect1 && Is_Bridge_Allowed_00571bc0(bridge)) {
                for (int y = bridge.Y; y < bridge.Y + bridge.Height; y++) {
                    for (int x = bridge.X; x < bridge.X + bridge.Width; x++) {
                        if (y == bridge.Y) {
                            Map[Cell(x, y)].OverlayIndex = 0x60;
                        } else if (y == bridge.Y + bridge.Height - 1) {
                            Map[Cell(x, y)].OverlayIndex = 0x62;
                        } else {
                            Map[Cell(x, y)].OverlayIndex = 0x53 + (y % 4);
                        }
                        Map[Cell(x, y)].OverlayData = x - bridge.X;
                    }
                }

                if (Can_Place_Paved_Road_End_00588c20(Rect(bridge.X - 2, bridge.Y - 6, 7, 6), false) && Map_Random_Range_005797a0(0,1)) {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+13, Cell(bridge.X, bridge.Y - 4));
                } else {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08+1, Cell(bridge.X, bridge.Y - 1));
                }

                if (Can_Place_Paved_Road_End_00588c20(Rect(bridge.X - 2, bridge.Y + bridge.Height, 7, 6), false) && Map_Random_Range_005797a0(0,1)) {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+12, Cell(bridge.X, bridge.Y + bridge.Height));
                } else {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08+3, Cell(bridge.X, bridge.Y + bridge.Height));
                }

                if (!Place_Neutral_Building_00571db0(Rect(bridge.X - 1, bridge.Y, 5, 2))) {
                    Place_Neutral_Building_00571db0(Rect(bridge.X - 2, bridge.Y - 1, 7, 3));
                }

                if (!Place_Neutral_Building_00571db0(Rect(bridge.X - 1, bridge.Y + bridge.Height - 2, 5, 2))) {
                    Place_Neutral_Building_00571db0(Rect(bridge.X - 2, bridge.Y + bridge.Height - 2, 7, 3));
                }

                result = true;
            }
        }

    }

    return(result);
}
