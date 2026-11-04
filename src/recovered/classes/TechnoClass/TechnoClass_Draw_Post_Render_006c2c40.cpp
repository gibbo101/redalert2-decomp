// TechnoClass slot 66 0x006C2C40: Draw_Post_Render (TibSun techno.cpp 1225).
// @ref ??0CoordStruct@@QAE@HHH@Z=0041b630
// @ref ??HCoordStruct@@QBE?AU0@ABU0@@Z=0069ecf0
#include "shared/techno.hpp"
#include "shared/cell.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/tactical.hpp"
#include "shared/palette.hpp"
#include "shared/gadget.hpp"
#include "shared/options.hpp"
#include "shared/rules.hpp"
#include "shared/selection_coord.hpp"
extern void *unknown_convert_8323c8;
extern Rect unknown_rect_839630;
void __fastcall Draw_Double_Selection_Bracket_006c3950(::Coord const &,::Coord const &,int);
// @ref ?unknown_47cb50@CellClass@@QAE_NXZ=0047cb50
// @ref ?Value@?$CDTimerClass@VSystemTimerClass@@@@QBEJXZ=004de200
// @ref ?unknown_slot66@ObjectClass@@UAEXABUPoint2D@@ABVRect@@@Z=00423dd0
// @ref ?unknown_convert_8323c8@@3PAXA=008323c8
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// 0x006C3A90: the last infantry site refuses it, so this unit emits the out-of-line copy (TibSun techno.cpp).
inline void __fastcall Draw_Single_Selection_Bracket(::Coord const &from, ::Coord const &to, int color)
{
    ::Coord quarter = (from + from + from + to) / 4;
    if (from.Z > quarter.Z) {
        unknown_tactical_83996c->unknown_slot24(from, quarter, color, 0);
    } else {
        unknown_tactical_83996c->unknown_slot24(quarter, from, color, 0);
    }
}
// Read accessors of the tail tests (their sites decide the bracket refusals above).
inline bool Flag_380(TechnoClass const *techno) { return techno->unknown_380; }
inline bool Is_Selected(TechnoClass const *techno) { return techno->unknown_77; }
inline TechnoClass *Talk_Owner() { return unknown_talk_techno_ac01c4; }
void TechnoClass::unknown_slot66(Point2D const &point, Rect const &window)
{
    bool sensed_underground = false;
    if (!unknown_325) {
        CellClass *cell = static_cast<CellClass *>(unknown_slot105());
        if (!unknown_77 && unknown_slot108() < -20 && cell && cell->unknown_47c2e0(unknown_player_a35db4->ArrayIndex)) {
            sensed_underground = true;
        }
        if (unknown_68 && unknown_38 && !Map[unknown_slot104()].unknown_47cb50()) {
            Point2D bomb_point;
            unknown_tactical_83996c->Coord_To_Pixel(unknown_slot42(), bomb_point);
            CC_Draw_Shape(unknown_surface_83995c, static_cast<ConvertClass *>(unknown_convert_8323c8),
                static_cast<ShapeFileStruct const *>(Rules->BombCursorShape), unknown_38->Unknown_00436000(),
                bomb_point, unknown_rect_839630, 0xe00, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        }
        if (this && Kind_Of() == 6) {
            BuildingClass *building = Kind_Of() == 6 ? static_cast<BuildingClass *>(this) : 0;
            if (building->unknown_5b8 && !Map[unknown_slot104()].unknown_47cb50()) {
                Point2D repair_point;
                unknown_tactical_83996c->Coord_To_Pixel(unknown_slot42(), repair_point);
                int delay = Options.Normalize_Delay(14) / 4;
                if (delay < 2) delay = 2;
                CC_Draw_Shape(unknown_surface_83995c, static_cast<ConvertClass *>(unknown_convert_8323c8),
                    static_cast<ShapeFileStruct const *>(unknown_wrench_shape_8502a8),
                    ((Frame % delay) * 6) / (delay - 1), repair_point, window, 0xe00, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            }
        }
        if (!unknown_slot49(unknown_player_a35db4) && unknown_slot25(false, 0) != 5) {
            unknown_slot250(point, window);
        }
        if (unknown_77 || sensed_underground) {
            if (Kind_Of() == 6) {
                int color = 15;
                if (unknown_slot108() < -4) {
                    color = 12;
                }
                CoordStruct const &lepton = unknown_slot32()->unknown_slot31();
                ::Coord dim = lepton;
                int x = dim.X / 2;
                dim.Y /= 2;
                int y = dim.Y;
                color = unknown_drawer_8323c4->Convert(color);
                CoordStruct const &position = Center_Coord();
                ::Coord center = position;
                if (Kind_Of() != 15) {
                    Draw_Double_Selection_Bracket_006c3950(center + ::Coord(x, y, 0), center + ::Coord(-x, y, 0), color);
                    Draw_Double_Selection_Bracket_006c3950(center + ::Coord(x, y, 0), center + ::Coord(x, -y, 0), color);
                    Draw_Double_Selection_Bracket_006c3950(center + ::Coord(-x, y, 0), center + ::Coord(-x, y, dim.Z), color);
                    Draw_Double_Selection_Bracket_006c3950(center + ::Coord(x, -y, 0), center + ::Coord(x, -y, dim.Z), color);
                }
                if (Strength > 0 && (House->Is_Ally(unknown_player_a35db4) || Rules->EnemyHealth)) {
                    unknown_slot247(reinterpret_cast<int>(&point), reinterpret_cast<int>(&window));
                }
                if (Kind_Of() != 15) {
                    Draw_Single_Selection_Bracket(center + ::Coord(x, y, 0), center + ::Coord(x, y, dim.Z), color);
                    Draw_Single_Selection_Bracket(center + ::Coord(x, -y, dim.Z), center + ::Coord(x, y, dim.Z), color);
                    Draw_Single_Selection_Bracket(center + ::Coord(-x, y, dim.Z), center + ::Coord(x, y, dim.Z), color);
                } else {
                    Draw_Single_Selection_Bracket(center + ::Coord(-x, y, 0), center + ::Coord(x, y, 0), color);
                    Draw_Single_Selection_Bracket(center + ::Coord(-x, y, 0), center + ::Coord(-x, y, dim.Z), color);
                    Draw_Single_Selection_Bracket(center + ::Coord(x, -y, dim.Z), center + ::Coord(x, -y, 0), color);
                    Draw_Single_Selection_Bracket(center + ::Coord(x, -y, dim.Z), center + ::Coord(-x, -y, dim.Z), color);
                }
            }
            unknown_slot248(point, window, sensed_underground);
        }
        if (Flag_380(this) && !Is_Selected(this)) {
            if (unknown_slot49(unknown_player_a35db4)) {
                if (unknown_slot51(true)) {
                    unknown_slot248(point, window, true);
                }
            } else {
                unknown_slot248(point, window, true);
            }
        }




        if (Talk_Owner() == this && unknown_talk_value_ac01c8 > 0 && (long)TalkBubbleTimer > 0) {
            CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4,
                static_cast<ShapeFileStruct const *>(unknown_talkbubl_shapes_a72fec), unknown_talk_value_ac01c8 - 1,
                point, window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        }
    }
}
