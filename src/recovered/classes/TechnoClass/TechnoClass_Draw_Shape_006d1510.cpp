// Draw a techno shape with its visual state, lighting, composite bounds and shadow.
#include "shared/cell.hpp"
#include "shared/building_class.hpp"
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/palette.hpp"
#include "shared/light_convert.hpp"
#include "shared/tactical.hpp"
#include "shared/color_scheme.hpp"

extern Rect unknown_unit_composite_rect_ad0490;
extern ConvertClass *unknown_drawer_ad0608;
// @ref ?unknown_unit_composite_rect_ad0490@@3VRect@@A=00ad0490

void TechnoClass::unknown_6d1510(void const *shape, int frame, Point2D const *point, Rect const *bounds,
    int rotation, int scale, int z, int gradient, int zwrite, int brightness, int zshape, int zframe,
    Point2D offset, int negative_flags)
{
    if (shape) {
        ShapeFileStruct const *shape_file=static_cast<ShapeFileStruct const *>(shape);
        bool shadow=unknown_flag_7d88d5;
        int visual=unknown_slot25(false,0);
        unsigned int flags=0;
        if (!negative_flags) {
            switch (visual) {
            case 4:
                if (unknown_1bc.Fetch_Stage()) { flags=4; break; }
            case 1: flags=2; break;
            case 2:
            case 3: flags=4; break;
            case 5: return;
            }
        }
        if (unknown_slot111() || unknown_slot112()) flags|=4;
        ConvertClass *converter;
        if (Kind_Of()==6 && static_cast<BuildingClass *>(this)->Type->TerrainPalette) {
            CellClass *cell=&Map[Coord_Cell(Center_Coord())];
            converter=cell->unknown_34;
            if (!converter) {
                cell->Init_Drawer(0,0x10000,0,1000,1000,1000);
                converter=cell->unknown_34;
                if (!converter) return;
            }
            brightness=cell->unknown_10c;
        } else {
            if (Kind_Of()==1 && static_cast<UnitClass *>(this)->unknown_5bb) converter=unknown_drawer_ad0608;
            else converter=reinterpret_cast<ConvertClass *>(unknown_slot115());
        }
        Point2D draw_point=*point;
        int z_adjust=z;
        switch (Kind_Of()) {
        case 1:
            if (static_cast<UnitClass *>(this)->Type->SmallVisceroid || static_cast<UnitClass *>(this)->Type->LargeVisceroid) shadow=false;
        case 15:
            if (unknown_slot108()==0) z_adjust+=unknown_slot176();
            else { z_adjust-=Unknown_006A2970(unknown_slot110()); shadow=false; }
            break;
        case 2:
            draw_point.Y-=Unknown_006A2970(unknown_slot110());
            z_adjust-=Unknown_006A2970(unknown_slot110());
            break;
        }
        if (unknown_slot32()->NoShadow) shadow=false;
        if (!unknown_slot245(unknown_player_a35db4)) {
            if (unknown_slot50(true)->Kind_Of()!=21 && unknown_slot50(true)->Kind_Of()!=37) converter=ColorSchemes[unknown_slot51(true)->ColorSchemeIndex]->Converter;
            else {
                CellClass *cell=static_cast<CellClass *>(unknown_slot105());
                converter=cell->unknown_34;
                if (!converter) {
                    cell->Init_Drawer(0,0x10000,0,1000,1000,1000);
                    converter=cell->unknown_34;
                }
                brightness=cell->unknown_10c;
            }
            if (!converter) converter=ColorSchemes[unknown_player_a35db4->ColorSchemeIndex]->Converter;
        }
        if (gradient!=-1) flags|=0x2000;
        if ((unsigned char)zwrite) flags|=0x4000;
        flags|=0x800;
        if (Kind_Of()==1 && static_cast<UnitClass *>(this)->unknown_5bb) { flags|=0x20; shadow=false; }
        flags&=~negative_flags;
        if (Kind_Of()==1 && static_cast<UnitClass *>(this)->unknown_5bb) {
            Rect frame_rect=shape_file->Get_Frame_Rect(frame);
            Rect draw_rect;
            draw_rect.X=frame_rect.X+draw_point.X-shape_file->Get_Width()/2;
            draw_rect.Y=frame_rect.Y+draw_point.Y-shape_file->Get_Height()/2;
            draw_rect.Width=frame_rect.Width;
            draw_rect.Height=frame_rect.Height;
            unknown_unit_composite_rect_ad0490=Union(unknown_unit_composite_rect_ad0490,draw_rect);
        }
        if (House->Unknown_004F52B0() && unknown_slot48()) flags=unknown_slot244(flags);
        brightness=unknown_slot254(brightness);
        if (unknown_slot203()) brightness=unknown_6d86f0(brightness);
        switch (visual) {
        case 0:
            CC_Draw_Shape(unknown_surface_83995c,converter,shape_file,frame,draw_point,*bounds,flags|0x600,0,z_adjust-2,gradient,brightness,zshape,zframe,offset);
            if (shadow) {
                z_adjust=-2-Unknown_006A2970(unknown_slot110());
                if (unknown_37c) draw_point.Y-=14;
                flags&=~6;
                CC_Draw_Shape(unknown_surface_83995c,converter,shape_file,frame+shape_file->FrameCount/2,draw_point,*bounds,flags|0x601,0,z_adjust-2,0,1000,0,0,Point2D(0,0));
            }
            break;
        case 1:
            CC_Draw_Shape(unknown_surface_83995c,converter,shape_file,frame,draw_point,*bounds,flags|0x600,0,z_adjust-2,gradient,brightness,zshape,zframe,offset);
            if (shadow) {
                z_adjust=-2-Unknown_006A2970(unknown_slot110());
                flags&=~6;
                if (unknown_37c) draw_point.Y-=14;
                CC_Draw_Shape(unknown_surface_83995c,converter,shape_file,frame+shape_file->FrameCount/2,draw_point,*bounds,flags|0x601,0,z_adjust-2,0,1000,0,0,Point2D(0,0));
            }
            break;
        case 2:
        case 4:
            CC_Draw_Shape(unknown_surface_83995c,converter,shape_file,frame,draw_point,*bounds,flags|0x600,0,z_adjust-2,gradient,brightness,zshape,zframe,offset);
            break;
        case 3:
            CC_Draw_Shape(unknown_surface_83995c,converter,shape_file,frame,draw_point,*bounds,flags|0x600,0,z_adjust-2,gradient,brightness,zshape,zframe,offset);
            break;
        }
    }
}
