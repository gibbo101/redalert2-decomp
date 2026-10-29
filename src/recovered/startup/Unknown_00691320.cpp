// void Unknown_00691320() (0x00691320): the orderly shutdown before Emergency_Exit. Sets ReadyToQuit,
// posts WM_DESTROY to the game window and pumps messages until the window procedure has handled it,
// revokes and disconnects the application object, uninitializes OLE, removes the mouse, frees a
// pending block, posts WM_QUIT and ends with Prog_End.
#include "shared/exit.hpp"
#include "shared/win32_window.hpp"
#include "shared/com_api.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"
#include "shared/queue.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Unknown_00691320@@YAXXZ=00691320
// @ref ?ReadyToQuit@@3HA=00a40d80
// @ref ?unknown_active_object_7f4ccc@@3KA=007f4ccc
// @ref ?unknown_block_abd488@@3PAXA=00abd488
// @ref ?unknown_flag_abd48c@@3_NA=00abd48c
// @ref ?Prog_End@@YAXXZ=006909e0
// @ref ?Unknown_005BB5A0@@YAXXZ=005bb5a0
// @ref __imp__RevokeActiveObject@8=0079a354

void Unknown_00691320()
{
    ReadyToQuit = 1;
    PostMessageA(MainWindow, 0x0002, 0, 0);  // WM_DESTROY
    while (MainWindow) {
        Unknown_005B5EE0();
        if (ReadyToQuit != 1) {
            break;
        }
    }
    if (unknown_active_object_7f4ccc != -1) {
        RevokeActiveObject(unknown_active_object_7f4ccc, 0);
        unknown_active_object_7f4ccc = -1;
    }
    CoDisconnectObject((IUnknown *)&unknown_application_84c7dc, 0);
    OleUninitialize();
    if (WWMouse) {
        WWMouse->Release_Mouse();
        delete WWMouse;
    }
    WWMouse = 0;
    if (unknown_flag_abd48c) {
        delete unknown_block_abd488;
        unknown_flag_abd48c = false;
    }
    PostQuitMessage(0);
    Unknown_005BB5A0();
    Prog_End();
}
