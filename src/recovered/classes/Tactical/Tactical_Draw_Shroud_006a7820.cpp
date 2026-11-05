// @ref ??0?$TPoint3D@H@@QAE@HHH@Z=0041b630
// @ref ?Unknown_0041F5E0@@YIXABVRect@@@Z=0041f5e0
// Draw cell shroud/fog and then the alpha-shape layer (0x006A7820).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// Real unaccepted alpha-layer entry: area in ECX, no stack arguments, plain RET.
void __fastcall Unknown_0041F5E0(Rect const &area);

inline CoordStruct::CoordStruct(Point2D const &point,int z) : BASECLASS(point.X,point.Y,z) {}

void Tactical::Draw_Shroud(Rect const &area)
{
    Point2D const viewport(TacPixelX,TacPixelY);
    CoordStruct lepton(Unknown_006A2900(viewport+area.Top_Left()-unknown_rect_839630.Top_Left()),0);
    if(lepton.Y<0) lepton.Y=0;
    if(lepton.X<0) lepton.X=0;
    Cell origin=Map[lepton].MapCoords;
    int rows=area.Height/15+17;
    int columns=area.Width/60+4;
    Cell base=origin;
    base.X-=2;
    Cell scan=base;
    if(unknown_b263d8) {
        int x,y;
        for(y=0;y<rows;++y) {
            Cell step(y/2,(y+1)/2);
            scan=base+step;
            for(x=columns;x>0;--x) {
                if(Map.Unknown_0054AAB0(scan)) {
                    CellClass *cell=&Map[scan];
                    CoordStruct coord=Coord_Snap(Cell_Center(scan));
                    Point2D pixel;
                    Coord_To_Pixel(coord,pixel);
                    pixel.X-=30;
                    Rect cell_rect(pixel.X,unknown_rect_839630.Y+pixel.Y,60,30);
                    Rect intersection=cell_rect.Intersect(area);
                    Rect draw_rect=unknown_rect_839630.Intersect(intersection);
                    if(draw_rect.Is_Valid()) {
                        Point2D origin(unknown_rect_839630.X,unknown_rect_839630.Y);
                        cell->Draw_Shroud_And_Fog(pixel+origin,draw_rect);
                    }
                }
                scan+=Cell(1,-1);
            }
        }
    }
    Unknown_0041F5E0(area);
}
