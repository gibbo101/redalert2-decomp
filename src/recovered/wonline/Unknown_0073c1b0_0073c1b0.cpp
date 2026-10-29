// void __fastcall Unknown_0073c1b0(bool online) (0x0073C1B0)
// The WOnline menu music: with online set, restarts the score (theme -2) unless a theme other than
// "INTRO" is playing or queued; otherwise queues theme -3.
#include "shared/wol_sink.hpp"
#include "shared/theme.hpp"
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?Still_Playing@ThemeClass@@QBE_NXZ=006e82d0
// @ref ?Stop@ThemeClass@@QAEX_N@Z=006e81a0
// @ref ?Queue_Song@ThemeClass@@QAEXH@Z=006e7e20
// @ref ?From_Name@ThemeClass@@QBEHPBD@Z=006e8510

void __fastcall Unknown_0073c1b0(bool online)
{
    if (online) {
        if (!Theme.Still_Playing()) {
            Theme.Stop();
            Theme.Queue_Song(-2);
            return;
        }
        int theme = Theme.Score;
        if (theme == -1) theme = Theme.Pending;
        if (theme == Theme.From_Name("INTRO")) {
            Theme.Stop();
            Theme.Queue_Song(-2);
        }
    } else {
        Theme.Queue_Song(-3);
    }
}
// @ref ??_C@_05KMPM@INTRO?$AA@=007dbc90
