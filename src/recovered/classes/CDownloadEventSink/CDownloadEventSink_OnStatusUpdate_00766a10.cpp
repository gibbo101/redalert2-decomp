#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
HRESULT __stdcall CDownloadEventSink::OnStatusUpdate(int status)
{
    wchar_t text[200];
    text[0]=0;
    switch(status) {
    case 2:
        swprintf(text,StringTable::Load_String("TXT_CONNECTING",0,"D:\\Ra2\\wonline.cpp",0xfa5));
        break;
    case 4:
        swprintf(text,StringTable::Load_String("TXT_FINDING_PATCH",0,"D:\\Ra2\\wonline.cpp",0xfa9));
        break;
    }
    HWND label=GetDlgItem(Unknown_00735B10(),0x5c8);
    SendMessageA(label,0x4b2,0,(LPARAM)text);
    return 0;
}
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
// @ref ??_C@_0P@OFIL@TXT_CONNECTING?$AA@=00800498
// @ref ??_C@_0BC@NEBC@TXT_FINDING_PATCH?$AA@=008004a8
