// void Mono_Window_Init(void *instance, HWND__ *parent, bool allowed) (0x0059D780)
// Keeps the dialog's instance, the game window and whether the window may show, builds the
// eight pages (the first is the one on display), clears them and shows the window when it
// was asked for before a parent existed.
// @ref ?unknown_mono_instance_a70f00@@3PAXA=00a70f00
#include "shared/win32_api.hpp"
#include "shared/mono_window.hpp"

void __fastcall Mono_Window_Init(void *instance, HWND__ *parent, bool allowed)
{
    unknown_mono_instance_a70f00 = instance;
    unknown_mono_parent_a70f04 = parent;
    unknown_mono_allowed_a70f08 = allowed;
    for (int page = 0; page < 8; page++) {
        unknown_mono_pages_a70e40[page] = new MonoClass(page);
    }
    unknown_mono_viewed_a70f0c = unknown_mono_pages_a70e40[0];
    Mono_Clear_All_Pages();
    if (unknown_mono_requested_a70f09) {
        Mono_Window_Show();
    }
}
