// HFONT __fastcall unknown_create_font_7360b0(HDC dc, char const *face, int width, int height, unsigned attributes) (0x007360B0)
// @ref __real@8@3ffe8000000000000000=0079a728
#include "shared/win_util.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_math.hpp"

HFONT __fastcall unknown_create_font_7360b0(HDC dc, char const *face, int width, int height, unsigned attributes)
{
    POINT point;
    TEXTMETRICA metrics;
    LOGFONTA font;

    SaveDC(dc);
    SetGraphicsMode(dc, 2);                 // GM_ADVANCED
    ModifyWorldTransform(dc, 0, 1);         // MWT_IDENTITY
    SetViewportOrgEx(dc, 0, 0, 0);
    SetWindowOrgEx(dc, 0, 0, 0);
    point.x = width;
    point.y = height;
    DPtoLP(dc, &point, 1);
    font.lfHeight = -point.y;
    font.lfWidth = 0;
    font.lfEscapement = 0;
    font.lfOrientation = 0;
    font.lfWeight = (attributes & 1) ? 700 : 0;
    font.lfItalic = (attributes & 2) ? 1 : 0;
    font.lfUnderline = (attributes & 4) ? 1 : 0;
    font.lfStrikeOut = (attributes & 8) ? 1 : 0;
    font.lfCharSet = 0;
    font.lfOutPrecision = 0;
    font.lfClipPrecision = 0;
    font.lfQuality = 0;
    font.lfPitchAndFamily = 0;
    strcpy(font.lfFaceName, face);
    HFONT handle = CreateFontIndirectA(&font);
    if (width != 0) {
        handle = (HFONT)SelectObject(dc, handle);
        GetTextMetricsA(dc, &metrics);
        DeleteObject(SelectObject(dc, handle));
        font.lfWidth = (int)(metrics.tmAveCharWidth * fabs(point.x) / fabs(point.y) + 0.5);
        handle = CreateFontIndirectA(&font);
    }
    RestoreDC(dc, -1);
    return handle;
}
