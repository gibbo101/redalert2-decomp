// void BinkClass::Unknown_00430430() (0x00430430)
// Plays the movie to its last frame: window messages are dispatched first,
// otherwise the due frames are drawn (at the movie area of the target; a
// movie drawn elsewhere is then copied to the screen surface at the window
// client area). Escape stops it unless unknown_00 is set.
#include "shared/movie.hpp"
#include "shared/keyboard.hpp"
#include "shared/win32_api.hpp"
// @ref ??_C@_0BA@BOHO@Bink?5Error?3?5?$CFs?6?$AA@=007cf4d8

void BinkClass::Unknown_00430430()
{
    if (Handle == 0) {
        Debug_Printf("Bink Error: %s\n", BinkGetError());
        return;
    }
    WWKeyboard->Clear();
    unknown_2c = true;
    unknown_2d = false;
    while (Handle->FrameNum < Handle->Frames) {
        MSG message;
        unknown_message_count_a52298++;
        if (unknown_peek_message_522ed0(&message, 0, 0, 0, 0)) {
            if (!unknown_get_message_522e90(&message, 0, 0, 0)) {
                break;
            }
            TranslateMessage(&message);
            DispatchMessageA(&message);
        } else {
            if (!unknown_2c) {
                Sleep(33);
            }
            if (Target == unknown_surface_839950) {
                RECT client;
                GetClientRect(MainWindow, &client);
                ClientToScreen(MainWindow, (POINT *)&client);
                Unknown_00430600(Target, Area.X + client.left, Area.Y + client.top);
            } else if (Unknown_00430600(Target, Area.X, Area.Y)) {
                RECT client;
                GetClientRect(MainWindow, &client);
                ClientToScreen(MainWindow, (POINT *)&client);
                Rect dest = Area;
                dest.X += client.left;
                dest.Y += client.top;
                unknown_surface_839950->Copy_From(dest, *Target, Area, false, true);
            }
            if (WWKeyboard->Check() && !unknown_00 && WWKeyboard->Get() == 0x81B) {
                break;
            }
        }
    }
    WWKeyboard->Clear();
}
