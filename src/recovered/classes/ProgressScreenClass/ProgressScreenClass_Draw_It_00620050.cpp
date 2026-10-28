// void ProgressScreenClass::Draw_It(Point2D xy) (0x00620050)
// With a window, draws the first player's bar into its control 0x639 on
// the background surface. Otherwise draws a row per player from xy
// (Position when xy is -1,-1): a single player shows Name (empty without
// one) in the side's colours in a skirmish, else the first player's name and
// colours. Then shows the screen.
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/abstract_type.hpp"
#include "shared/win32_window.hpp"
#include "shared/gscreen.hpp"
// @ref ?Draw_Player@ProgressScreenClass@@QAEXPAVColorScheme@@PBGAAUPoint2D@@H_N@Z=0061fc20

void ProgressScreenClass::Draw_It(Point2D xy)
{
    if (unknown_60 && Shape != 0) {
        Point2D point;
        if (Window != 0) {
            RECT rect;
            HWND control = GetDlgItem(Window, 0x639);
            Window_Rect_In_Main_Client(control, &rect);
            point = Point2D(rect.left, rect.top);
            Draw_Bar(point, Get_Progress(0), unknown_surface_839958, 0);
            return;
        }
        point = xy;
        if (point.X == -1 && point.Y == -1) {
            point = Position;
        }
        wchar_t const *name = Name;
        if (Count == 1) {
            ColorScheme *scheme;
            if (unknown_game_mode_a3d298 == 0) {
                if (name == 0) {
                    name = unknown_empty_wide_839d4c;
                }
                scheme = Side_Color_Scheme();
            } else {
                if (name == 0) {
                    name = unknown_players_a3fa7c[0]->Name;
                }
                scheme = Player_Color_Scheme(0);
            }
            Draw_Player(scheme, name, point, 0, ShowFlags);
        } else {
            for (int player = 0; player < Count; player++) {
                ColorScheme *scheme = Player_Color_Scheme(player);
                Draw_Player(scheme, unknown_players_a3fa7c[player]->Name, point, player, ShowFlags);
            }
        }
        GScreenClass::Blit(true, unknown_surface_839954);
    }
}
