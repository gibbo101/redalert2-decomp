#include "shared/progress_screen.hpp"
#include "shared/shape_file.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/dsurface.hpp"
void ProgressScreenClass::Draw_Player(ColorScheme *scheme, wchar_t const *name, Point2D &xy, int player, bool flag)
{
    double fraction = Get_Progress(player);
    int y = Row_Y(xy.Y, player, flag);
    int width = 0, height = 0;
    Box_Size(&width, &height, 1, flag);
    if (NameWidth != -1) width = NameWidth;
    if (unknown_71) {
        Rect shadow(xy.X, y, width, height);
        Unknown_005feb60(&shadow, unknown_surface_839954, 0, 0x9f);
    }
    int shape_width = 0, shape_height = 0;
    Shape_Size(&shape_width, &shape_height);
    Point2D bar = xy;
    int bar_offset = Shape_Offset(flag);
    bar.X += 5;
    bar.Y = y + bar_offset;
    Point2D item = xy;
    item.X += shape_width + 15;
    Point2D flag_point = item;
    if (flag) flag_point.Y = y + Flag_Offset(flag);
    Point2D name_point = item;
    int text_offset = Text_Offset(flag);
    if (flag) {
        int flag_width = 0, flag_height = 0;
        Flag_Size(&flag_width, &flag_height);
        name_point.X += flag_width + 10;
    }
    name_point.Y = y + text_offset;
    Draw_Bar(bar, fraction, unknown_surface_839954, scheme);
    if (flag) {
        int country = unknown_players_a3fa7c[player]->unknown_66e290();
        if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && unknown_players_a3fa7c[player]->Team == -1) country = -3;
        Surface *image = Country_Flag_004d1120(country);
        if (image) Draw_Flag(flag_point, image);
    }
    Draw_Name(name_point, name, scheme, xy.X - name_point.X - 3 + width);
}
