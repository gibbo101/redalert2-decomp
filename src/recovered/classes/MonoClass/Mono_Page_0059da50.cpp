// Mono debug page getter at0059DA50: ECX is a page index, not an object receiver.
// The array and MonoClass layout are shared with Mono_Window_Init/Shutdown.
#include "shared/mono_window.hpp"
// @ref ?unknown_mono_pages_a70e40@@3PAPAVMonoClass@@A=00a70e40
MonoClass *__fastcall Mono_Page_0059da50(int page)
{
    return unknown_mono_pages_a70e40[page];
}
