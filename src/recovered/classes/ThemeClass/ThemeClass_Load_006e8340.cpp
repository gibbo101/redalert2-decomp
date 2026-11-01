// long ThemeClass::Load(IStream *stream) -- 0x006E8340 (name hypothesis after Save 0x006E8310)
// Purpose: reads the playing and queued themes from a save stream; when 0x00A40B51 is set the
// playing theme is restarted and the queued one queued again on Theme. Returns the read result.
#define THEME_CONTROL_RECORD
#include "shared/theme.hpp"
#include "shared/com_persist.hpp"
#include "shared/main_loop.hpp"
// @ref ?unknown_flag_a40b51@@3_NA=00a40b51
// @ref ?Play_Song@ThemeClass@@QAEHH@Z=006e7eb0
// @ref ?Theme@@3VThemeClass@@A=00a35d78

long ThemeClass::Load(IStream *stream)
{
    ThemeType score;
    ThemeType pending;
    HRESULT hr = stream->Read(&score, sizeof(score), 0);
    if (SUCCEEDED(hr)) {
        hr = stream->Read(&pending, sizeof(pending), 0);
        if (SUCCEEDED(hr) && unknown_flag_a40b51) {
            Theme.Play_Song(score);
            Theme.Queue_Song(pending);
        }
    }
    return hr;
}
