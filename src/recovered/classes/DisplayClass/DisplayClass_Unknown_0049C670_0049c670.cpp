#include "shared/display.hpp"
#include "shared/house_screen.hpp"
#include "shared/techno.hpp"
#include "shared/id_source.hpp"
#include "shared/tactical.hpp"
#include "shared/locomotion.hpp"
void DisplayClass::Unknown_0049C670()
{
    CoordStruct center(0,0,0);
    int count=0;
    for (int i=0;i<Technos.Count();i++) {
        TechnoClass *tech=Technos[i];
        if (!tech->unknown_76 && tech->unknown_372) {
            center += Object_Coord(tech);
            count++;
        }
    }
    center.Z=0;
    if (count) center/=count;
    else {
        center.X=unknown_player_a35db4->BaseCenter.X;
        center.Y=unknown_player_a35db4->BaseCenter.Y;
    }
    unknown_id_source_a3d290->Views[0]=unknown_id_source_a3d290->Views[1]=unknown_id_source_a3d290->Views[2]=unknown_id_source_a3d290->Views[3]=Cell(center);
    unknown_id_source_a3d290->AltHomeCell=unknown_id_source_a3d290->HomeCell;
    if (unknown_tactical_83996c) unknown_tactical_83996c->Unknown_006A66B0(center);
}
