// @ref _swprintf=00783764
// @ref ??_C@_17FKIN@?$AA?$CF?$AAh?$AAs?$AA?$AA@=007eadcc
#include "shared/crt_tokens.hpp"
#include "shared/string_table.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

void UnknownControlRecord::Set_Text_600560(char const *text)
{
    if (text_28) {
        operator delete(text_28);
        text_28 = 0;
    }
    if (text && *text) {
        text_28 = (wchar_t *)operator new((strlen(text) + 1) * sizeof(wchar_t));
        swprintf(text_28, L"%hs", text);
    }
}

}
