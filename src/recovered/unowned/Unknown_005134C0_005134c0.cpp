// int __stdcall Unknown_005134C0(HWND, UINT, WPARAM, LPARAM) -- 0x005134C0
#include "shared/win32_api.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/options.hpp"

// @ref ?unknown_movie_choice_7db558@@3HA=007db558

// The movie list's last selection (0x007DB558).
extern int unknown_movie_choice_7db558;

int __stdcall Unknown_005134C0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    bool chosen = false;
    HWND list = GetDlgItem(window, 0x744);
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    int *choice = (int *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x497:
        if (list != 0) {
            Options.Fill_Movie_List(list);
            if (SendMessageA(list, 0x186, unknown_movie_choice_7db558, 0) == -1) {
                SendMessageA(list, 0x186, 0, 0);
            }
        } else {
            if (choice != 0) {
                *choice = -1;
            }
            return 0;
        }
        break;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 0x686:
            if (choice != 0) {
                *choice = -1;
            }
            break;
        case 0x744:
            if ((unsigned short)(wparam >> 16) == 0) {
                chosen = true;
            }
            break;
        case 0x745:
            chosen = true;
            break;
        }
        break;
    }
    if (list != 0 && chosen) {
        int index = SendMessageA(list, 0x188, 0, 0);
        unknown_movie_choice_7db558 = index;
        if (index != -1) {
            int movie = SendMessageA(list, 0x199, index, 0);
            if (movie != 0 && choice != 0) {
                *choice = movie;
            }
        }
    }
    return 0;
}
