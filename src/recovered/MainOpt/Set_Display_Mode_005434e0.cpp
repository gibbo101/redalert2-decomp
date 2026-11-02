// bool __fastcall Set_Display_Mode(int width, int height) (0x005434E0)
// Changes the screen mode: windowed it only resizes the visible rectangle; full screen it drops the mouse
// and the primary surface, sets the video mode (restoring both on failure), then deletes the off-screen
// surfaces, resizes the main window, reallocates the surfaces and rebuilds the remap tables, the mouse,
// the map view, the tabs and the open dialogs.
#include "shared/main_opt.hpp"
#include "shared/debug_printf.hpp"
#include "shared/hicolor.hpp"
#include "shared/wwmouse.hpp"
#include "shared/dsurface.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/lobby.hpp"
#include "shared/win32_window.hpp"
// @ref ??_C@_0BE@KPL@VisibleRect?3?5?$CFdx?$CFd?6?$AA@=007e001c
// @ref ??_C@_0BG@PLCA@Deleting?5TileSurface?6?$AA@=007dd828
// @ref ??_C@_0BH@DKEN@Mode?5change?5complete?4?6?$AA@=007dff0c
// @ref ??_C@_0BI@BHJ@Set_Video_Mode?5failed?4?6?$AA@=007dffd0
// @ref ??_C@_0BI@GOMM@Deleting?5HiddenSurface?6?$AA@=007dd85c
// @ref ??_C@_0BI@HBJI@Removing?5mouse?5handler?6?$AA@=007e0004
// @ref ??_C@_0BI@LBEK@Mode?5apparently?5set?5OK?6?$AA@=007dff80
// @ref ??_C@_0BJ@GNMK@Deleting?5SidebarSurface?6?$AA@=007dd80c
// @ref ??_C@_0BJ@HFOH@About?5to?5set?5video?5mode?6?$AA@=007e0030
// @ref ??_C@_0BJ@LHDL@Restoring?5mouse?5handler?6?$AA@=007dff98
// @ref ??_C@_0BK@HIPO@Deleting?5primary?5surface?6?$AA@=007dffe8
// @ref ??_C@_0BK@KENL@Creating?5primary?5surface?6?$AA@=007dff40
// @ref ??_C@_0BL@BPEP@Deleting?5CompositeSurface?6?$AA@=007dd840
// @ref ??_C@_0BL@GPOC@Restoring?5primary?5surface?6?$AA@=007dffb4
// @ref ??_C@_0BL@JIDJ@Recalc?5color?5remap?5tables?6?$AA@=007dff24
// @ref ??_C@_0BL@PKEH@Deleting?5AlternateSurface?6?$AA@=007dd874
// @ref ??_C@_0CC@OGBJ@Setting?5new?5window?5size?5to?5?$CFdx?$CFd@=007dff5c
// @ref ?Unknown_00486010@@YIXHHHHHH@Z=00486010
// @ref ?Unknown_005E9F00@@YIXPAUHWND__@@PAUPoint2D@@@Z=005e9f00
// @ref ?Unknown_005FF380@@YIXPAUHWND__@@@Z=005ff380
// @ref ??_C@_09JKEA@MOUSE?4SHP?$AA@=007db964
// @ref ?Allocate_Surfaces@@YI_NPAVRect@@000_N@Z=00519500
// @ref ?Set_Video_Mode@@YI_NPAUHWND__@@HHH@Z=00495c90

bool __fastcall Set_Display_Mode(int width, int height)
{
    Debug_Printf("About to set video mode\n");
    Point2D old_size(unknown_8523e0, unknown_8523e4);
    int red_right = Get_Red_Right();
    int red_left = Get_Red_Left();
    int green_right = Get_Green_Right();
    int green_left = Get_Green_Left();
    int blue_right = Get_Blue_Right();
    int blue_left = Get_Blue_Left();
    WWMouse->Hide_Mouse();
    Wait_For_Surface_Blit_004961d0();
    if (unknown_flag_851cb0 == true) {
        unknown_window_839640 = Rect(0, 0, width, height);
        unknown_8523e0 = width;
        unknown_8523e4 = height;
        Debug_Printf("VisibleRect: %dx%d\n", width, height);
    } else {
        if (WWMouse) {
            Debug_Printf("Removing mouse handler\n");
            delete WWMouse;
            WWMouse = 0;
        }
        if (unknown_surface_839950) {
            Debug_Printf("Deleting primary surface\n");
            delete unknown_surface_839950;
            unknown_surface_839950 = 0;
        }
        if (!Set_Video_Mode(MainWindow, width, height, 16)) {
            Debug_Printf("Set_Video_Mode failed.\n");
            Debug_Printf("Restoring primary surface\n");
            unknown_surface_839950 = DSurface::Create_Primary(0);
            Debug_Printf("Restoring mouse handler\n");
            WWMouse = new WWMouseClass(unknown_surface_839950, MainWindow);
            void const *shape = MixFileClass::Retrieve("MOUSE.SHP");
            if (shape) {
                Point2D hotspot = Point2D(0, 0);
                WWMouse->Set_Cursor(hotspot, (ShapeFileStruct const *)shape, 0);
            }
            Map.Set_Default_Mouse(0, false);
            Map.Override_Mouse_Shape(0, false);
            WWMouse->Show_Mouse();
            return false;
        }
        Debug_Printf("Mode apparently set OK\n");
        unknown_window_839640 = Rect(0, 0, width, height);
        Debug_Printf("VisibleRect: %dx%d\n", width, height);
    }
    if (unknown_surface_839958) {
        Debug_Printf("Deleting AlternateSurface\n");
        delete unknown_surface_839958;
        unknown_surface_839958 = 0;
    }
    if (unknown_surface_839954) {
        Debug_Printf("Deleting HiddenSurface\n");
        delete unknown_surface_839954;
        unknown_surface_839954 = 0;
    }
    if (unknown_surface_839944) {
        Debug_Printf("Deleting TileSurface\n");
        delete unknown_surface_839944;
        unknown_surface_839944 = 0;
    }
    if (unknown_surface_839948) {
        Debug_Printf("Deleting SidebarSurface\n");
        delete unknown_surface_839948;
        unknown_surface_839948 = 0;
    }
    if (unknown_surface_839964) {
        Debug_Printf("Deleting CompositeSurface\n");
        delete unknown_surface_839964;
        unknown_surface_839964 = 0;
    }
    if (unknown_flag_851cb0 == false) {
        Debug_Printf("Setting new window size to %dx%d\n", width, height);
        SetWindowPos(MainWindow, 0, 0, 0, width, height, 2);
        Debug_Printf("Creating primary surface\n");
        unknown_surface_839950 = DSurface::Create_Primary(0);
    } else {
        Debug_Printf("Setting new window size to %dx%d\n", width, height);
        RECT rect;
        SetRect(&rect, 0, 0, width, height);
        AdjustWindowRectEx(&rect, GetWindowLongA(MainWindow, -16), GetMenu(MainWindow) != 0, GetWindowLongA(MainWindow, -20));
        MoveWindow(MainWindow, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 1);
    }
    Rect tactical = Unknown_006F1F30();
    {
        Rect sidebar(0, 0, unknown_int_7add80, unknown_window_839640.Height);
        Rect tile(0, 0, tactical.Width, unknown_window_839640.Height);
        Rect composite(0, 0, tactical.Width, unknown_window_839640.Height);
        Allocate_Surfaces(&unknown_window_839640, &composite, &tile, &sidebar, false);
    }
    unknown_surface_83995c = unknown_surface_839954;
    Debug_Printf("Recalc color remap tables\n");
    Unknown_00486010(red_right, red_left, green_right, green_left, blue_right, blue_left);
    if (WWMouse == 0) {
        WWMouse = new WWMouseClass(unknown_surface_839950, MainWindow);
        void const *shape = MixFileClass::Retrieve("MOUSE.SHP");
        if (shape) {
            Point2D hotspot = Point2D(0, 0);
            WWMouse->Set_Cursor(hotspot, (ShapeFileStruct const *)shape, 0);
        }
        Map.Set_Default_Mouse(0, false);
        Map.Override_Mouse_Shape(0, false);
        WWMouse->Show_Mouse();
    } else {
        ((WWMouseClass *)WWMouse)->Calc_Confining_Rect();
    }
    Map.unknown_slot42(tactical);
    Unknown_Reset_Art_006F33B0(unknown_8523e0, unknown_8523e4);
    Map.Init_IO();
    Map.unknown_slot54(1);
    Map.unknown_slot34();
    Map.Flag_To_Redraw(2);
    for (HWND dialog = Unknown_00735B10(); dialog != 0; dialog = (HWND)unknown_previous_key((int)dialog)) {
        Unknown_005FF380(dialog);
        Unknown_005E9F00(dialog, &old_size);
    }
    WWMouse->Show_Mouse();
    Debug_Printf("Mode change complete.\n");
    return true;
}
