// int GraphicMenu::Run() (0x004DE9E0): plays the menu's theme over the cleared screen, waits for the background
// animation, then runs the engine until a key picks an item (1 and 13 choose the item under the mouse, other
// keys the item whose shortcut matches); the mouse highlights the item under it. Returns the chosen item's ID.
#include "shared/graphic_menu_class.hpp"
#include "shared/vector_cursor.hpp"
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"
#include "shared/theme.hpp"
#include "shared/surface.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?From_Name@ThemeClass@@QBEHPBD@Z=006e8510
// @ref ?Play_Song@ThemeClass@@QAEHH@Z=006e7eb0
// @ref ?Queue_Song@ThemeClass@@QAEXH@Z=006e7e20
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref ?Check@WWKeyboardClass@@QAEGXZ=005322d0
// @ref ?Get@WWKeyboardClass@@QAEGXZ=00532320
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Wait_For@MSEngine@@QAEXPAVMSAnim@@I@Z=005b2f30
// @ref ?Broadcast@MSEngine@@QAEXH@Z=005b3800
// @ref ?Redraw@MSEngine@@QAEXXZ=005b2f90
// @ref ?Check_Focus@MSEngine@@QAEXXZ=005b3670
// @ref ?Run@MSEngine@@QAEXH@Z=005b3550
// @ref ?Set_Enabled@GraphicMenuItem@@QAEX_N@Z=004e0160
// @ref ?unknown_5ff5d0@@YAHXZ=005ff5d0
int unknown_5ff5d0();

int GraphicMenu::Run()
{
    ::Theme.Play_Song(::Theme.From_Name(Theme.Get()));
    unknown_surface_839958->Fill(0);
    unknown_surface_839954->Fill(0);
    unknown_surface_839950->Copy_From(*unknown_surface_839954, false, true);
    bool done = false;
    GraphicMenuItem *selected = 0;
    WWKeyboard->Clear();
    if (Anim) {
        Engine.Wait_For(Anim, 300000);
    }
    Engine.Broadcast((int)&unknown_surface_839958->Get_Rect());
    Engine.Redraw();
    do {
        WWMouse->Hide_Mouse();
        Engine.Check_Focus();
        WWMouse->Show_Mouse();
        Point2D point(WWMouse->Get_Mouse_X(), WWMouse->Get_Mouse_Y());
        if (WWKeyboard->Check()) {
            int key = WWKeyboard->Get();
            GraphicMenuItem *item;
            if (key == 1 || key == 13) {
                item = Item_At(point);
            } else {
                item = Item_For(key);
            }
            if (item) {
                if (selected != item) {
                    if (selected) {
                        selected->Set_Enabled(false);
                    }
                    selected = item;
                    item->Set_Enabled(true);
                }
                done = true;
            }
        } else {
            GraphicMenuItem *item = Item_At(point);
            if (item != selected) {
                if (selected) {
                    selected->Set_Enabled(false);
                }
                selected = item;
                if (item) {
                    item->Set_Enabled(true);
                }
            }
        }
        Engine.Run(1);
    } while (!done);
    if (selected) {
        selected->Play_Sound((int)&Engine);
    }
    unknown_5ff5d0();
    ::Theme.Queue_Song(-3);
    return selected ? selected->ID : -1;
}
