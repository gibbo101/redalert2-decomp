// Selects and clears a debug page, then refreshes the selected page.
#include "shared/mono_window.hpp"
// @ref ?unknown_mono_pages_a70e40@@3PAPAVMonoClass@@A=00a70e40
// @ref ?unknown_mono_viewed_a70f0c@@3PAVMonoClass@@A=00a70f0c
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90

void __fastcall Mono_View_Page(int page)
{
    unknown_mono_viewed_a70f0c = unknown_mono_pages_a70e40[page];
    unknown_mono_viewed_a70f0c->Clear();
    unknown_mono_viewed_a70f0c->Refresh(0, 0, 80, 25);
}
