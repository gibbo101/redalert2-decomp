#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
bool MapRegionClass::Is_Rectangle_Clear_00575910(Rect const &area,int allowedRegion)
{
    if(Map.Unknown_0055A660(Cell(area.X,area.Y),true)) {
       int right=area.Width+area.X-1;
       if(Map.Unknown_0055A660(Cell(right,area.Y),true)) {
       int bottom=area.Y;
       bottom+=area.Height-1;
       if(Map.Unknown_0055A660(Cell(area.X,bottom),true)) {
       right=area.Width+area.X-1;
       bottom=area.Y;
       bottom+=area.Height-1;
       if(Map.Unknown_0055A660(Cell(right,bottom),true)) {
    for(int y=area.Y;y<area.Height+area.Y;++y) {
        for(int x=area.X;x<area.Width+area.X;++x) {
            Cell position(x,y);
            int region=UnknownMapGenerationCell::Get_Region(position);
            if(region!=Index && region!=allowedRegion)return false;
            if(!Map[position].unknown_47b590())return false;
        }
    }
    return true;
    }
    }
    }
    }
    return false;
}
