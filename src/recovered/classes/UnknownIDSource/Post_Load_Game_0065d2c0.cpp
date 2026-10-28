// void __fastcall Post_Load_Game_0065d2c0() (0x0065D2C0)
// Called once, right after a saved game is read (0x00656AD5): refreshes the
// building types, loads the veinhole shapes for the scenario's theater,
// rebuilds the radar, stops unknown_timer_ac0178 (keeping what remained) and
// restarts it from the current frame,
// sizes the path estimator for the map, runs 0x00520770 and the tiberium
// animation palettes, redraws the screen and resets the sidebar placement
// state (name hypothesis).
// @ref ?Unknown_006EA9B0@@YAXXZ=006ea9b0
// @ref ?Unknown_00520770@@YAXXZ=00520770
// @ref ?Unknown_006F89E0@@YAXXZ=006f89e0
// @ref ?Unknown_0063C790@@YIXXZ=0063c790
// @ref ?unknown_timer_ac0178@@3V?$CDTimerClass@VFrameTimerClass@@@@A=00ac0178
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/map_view.hpp"
#include "shared/building_type_class.hpp"
#include "shared/veinhole.hpp"
#include "shared/cd_timer.hpp"
#include "shared/path_estimator.hpp"
#include "shared/anim.hpp"
#include "shared/win32_window.hpp"

void __fastcall Post_Load_Game_0065d2c0()
{
    BuildingTypeClass::unknown_func_45e170();
    Unknown_006EA9B0();
    VeinholeMonsterClass::Load_Shape(unknown_id_source_a3d290->Theater);
    Map.Unknown_00631ED0();
    CDTimerClass<FrameTimerClass> &timer = unknown_timer_ac0178;
    timer.Stop();
    timer.Started = timer.Timer;
    unknown_path_estimator_8315c8.Unknown_004284E0(Map.MapSize);
    Unknown_00520770();
    Unknown_00423C70();
    Map.Flag_To_Redraw(2);
    InvalidateRect(MainWindow, 0, false);
    Unknown_006F89E0();
    Unknown_006F8A20(0);
    Unknown_0063C790();
}

