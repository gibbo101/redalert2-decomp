// @ref ??0UnknownCoord434820@@QAE@HHH@Z=00434820
// Tactical tile-shadow scan (006A8240); two original inverse projections are evidenced.
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"

void Tactical::Draw_Tile_Shadows(Rect const &area,Rect const &cliprect)
{
    Point2D const viewport(TacPixelX,TacPixelY);
    CoordStruct lepton(Unknown_006A2900(viewport+area.Top_Left()-unknown_rect_839630.Top_Left()),0);
    Cell origin=lepton.As_Cell();
    Cell base=origin;
    base.X-=2;
    Cell scan=base;
    lepton=CoordStruct(Unknown_006A2900(Point2D(area.Top_Left())+Point2D(TacPixelX,TacPixelY)-unknown_rect_839630.Top_Left()),0);
    origin=Map[lepton].MapCoords;
    base=origin;
    int rows=area.Height/15+20;
    int columns=area.Width/60+7;
    base.X-=2;
    base.Y+=3;
    int y,x;
    for(y=0;y<rows;++y) {
        Cell step(y/2,(y+1)/2);
        scan=base+step;
        for(x=columns;x>0;--x) {
            if(Map.Unknown_0054AAB0(scan)) {
                int x=scan.X*256+128;
                int y=scan.Y*256+128;
                CoordStruct coord=UnknownCoord434820(x/256*256,y/256*256,0);
                Point2D pixel;
                Coord_To_Pixel(coord,pixel);
                pixel.X-=30;
                Map[scan].Draw_Shadow_Cast(pixel,cliprect);
            }
            scan+=Cell(1,-1);
        }
    }
}
