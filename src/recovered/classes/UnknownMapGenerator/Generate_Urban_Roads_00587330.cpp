// TibSun Generate_Urban_Roads: east-west bands, then north-south bands with medians.
#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/cell_class.hpp"
#include "shared/tileset_index.hpp"
#include "shared/unknown_map_generator.hpp"
Rect __fastcall Bounding_Rectangle_00588e20(DynamicVectorClass<Cell> const &cells);
bool __fastcall Can_Place_Paved_Road_00588a30(Rect const &area,bool overlap,bool end);
bool __fastcall Can_Place_Paved_Road_Junction_00588ec0(Rect &area);
void UnknownMapGenerator::Generate_Urban_Roads_00587330(DynamicVectorClass<Cell> &cells)
{
    Cell start;
    Rect bounds=Bounding_Rectangle_00588e20(cells);

    if(bounds.Height>5) {
        start.Y=bounds.Y+2;
        start.X=bounds.X;
        int remaining=bounds.Height-2;

        while(remaining>3) {
            Cell junction=Plan_Paved_Road_Junction_00588560(start,bounds,2);
            Cell end=Plan_Paved_Road_00588850(junction,bounds,2);

            bool valid=false;
            int first;

            if(end!=Cell(0,0) && start!=Cell(0,0)) {
                first=start.X;
                valid=true;
            }

            if(valid && end.X-first>=6) {
                if(Can_Place_Paved_Road_00588a30(Rect(junction.X-4,junction.Y,4,3),false,false) && Map_Random_Range_005797a0(0,1)) {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+9,junction-Cell(3,0));
                } else {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08+2,junction);
                }

                for(int x=0;x<end.X-junction.X-1;x++) {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c,junction+Cell(x+1,0));
                }

                if(Can_Place_Paved_Road_00588a30(Rect(end.X,end.Y,4,3),false,false) && Map_Random_Range_005797a0(0,1)) {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+10,end);
                } else {
                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08,end);
                }

                remaining-=10;
                start.Y+=10;
            } else {
                start.Y+=2;
                remaining-=2;
            }
        }
    }

    if(bounds.Width>8) {
        int remaining=bounds.Height-5;
        start.X=bounds.X+5;
        start.Y=bounds.Y;

        while(remaining>3) {
            Cell cursor=Plan_Paved_Road_Junction_00588560(start,bounds,4);
            Cell end=Plan_Paved_Road_00588850(cursor,bounds,4);

            if(end!=Cell(0,0) && start!=Cell(0,0) && end.Y-start.Y>=6) {
                bool in_segment=false;
                bool initial=true;
                bool median_pending=false;
                bool median_flip=false;
                bool skip_tail=false;

                while(cursor.Y<end.Y) {
                    if(!in_segment) {
                        Rect road_rect;
                        Rect junction_rect;
                        road_rect=Rect(cursor.X,cursor.Y,3,2);
                        junction_rect=Rect(cursor.X,cursor.Y-3,3,4);

                        if(end.Y-cursor.Y<2) {
                            skip_tail=true;
                            break;
                        }

                        if(initial && Can_Place_Paved_Road_00588a30(Rect(cursor.X,cursor.Y-3,3,4),false,false) && Map_Random_Range_005797a0(0,1)) {
                            Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+13,cursor-Cell(0,3));
                            in_segment=true;
                        } else if(Can_Place_Paved_Road_Junction_00588ec0(junction_rect)) {
                            Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+5,cursor-Cell(0,3));
                            Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+1,cursor);
                            in_segment=true;
                        } else if(Can_Place_Paved_Road_00588a30(road_rect,false,false)) {
                            Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08+1,cursor);
                            in_segment=true;
                        }
                    } else {
                        if(Can_Place_Paved_Road_00588a30(Rect(cursor.X,cursor.Y,3,1),false,false)) {
                            Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+1,cursor);

                            if(median_pending) {
                                if(median_flip) {
                                    Place_Tile_Footprint_005883f0(unknown_tileset_a52c68+5,cursor+Cell(1,0));
                                    median_flip=false;
                                } else {
                                    Place_Tile_Footprint_005883f0(unknown_tileset_a52c68+4,cursor+Cell(1,0));
                                }
                            }
                        } else {
                            Rect junction_rect(cursor.X,cursor.Y,3,4);

                            if(median_pending) {
                                Place_Tile_Footprint_005883f0(unknown_tileset_a52c68+3,cursor+Cell(1,-1));
                                median_pending=false;
                            }

                            if(Can_Place_Paved_Road_Junction_00588ec0(junction_rect)) {
                                int bottom=end.Y;

                                if(bottom-cursor.Y<4) {
                                    Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+7,cursor);
                                    skip_tail=true;
                                    break;
                                }

                                if(Can_Place_Paved_Road_00588a30(Rect(cursor.X,cursor.Y+3,3,2),false,false)) {
                                    if(bottom-cursor.Y>5) {
                                        median_pending=true;
                                        median_flip=true;
                                    }
                                }

                                Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+3,cursor);

                                if(Can_Place_Paved_Road_00588a30(Rect(cursor.X-1,cursor.Y,1,3),true,false)) {
                                    Place_Tile_Footprint_005883f0(unknown_tileset_a52c68+12,cursor-Cell(1,0));
                                }

                                if(Can_Place_Paved_Road_00588a30(Rect(cursor.X+3,cursor.Y,1,3),true,false)) {
                                    Place_Tile_Footprint_005883f0(unknown_tileset_a52c68+12,cursor+Cell(3,0));
                                }

                                cursor.Y+=2;
                            } else {
                                Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08+3,cursor-Cell(0,1));

                                CellClass *cellptr=&Map[cursor+Cell(1,-2)];

                                if(cellptr->unknown_47b940()) {
                                    while(cellptr->unknown_47b940()) {
                                        cellptr->IsoTileIndex=unknown_tileset_a6dd0c+1;
                                        cellptr->unknown_11a=1;
                                        cellptr=&cellptr->Adjacent_Cell(0);
                                    }
                                }

                                in_segment=false;
                            }
                        }
                    }

                    initial=false;
                    cursor.Y++;
                }

                if(!skip_tail) {
                    if(median_pending) {
                        Place_Tile_Footprint_005883f0(unknown_tileset_a52c68+3,cursor+Cell(1,-1));
                    }

                    if(Can_Place_Paved_Road_00588a30(Rect(cursor.X,cursor.Y,3,4),false,false) && Map_Random_Range_005797a0(0,1)) {
                        Place_Tile_Footprint_005883f0(unknown_tileset_a6dd0c+12,cursor);
                    } else {
                        Place_Tile_Footprint_005883f0(unknown_tileset_a6dd08+3,cursor);
                    }
                }

                remaining-=10;
                start.X+=10;
            } else {
                start.X+=2;
                remaining-=2;
            }
        }
    }
}
