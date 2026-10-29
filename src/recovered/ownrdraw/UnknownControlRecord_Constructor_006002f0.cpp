// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8
// @ref ??0WideString@@QAE@XZ=0076f9b0
#include "shared/crt_memory.hpp"
#include "shared/wide_string.hpp"
#include "shared/text_print.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

UnknownControlRecord::UnknownControlRecord()
{
    memset(this, 0, sizeof(UnknownControlRecord));
    unknown_68 = 0xb;
    font_64 = BitFont;
    unknown_3c = new WideString;
    unknown_40 = 0;
    unknown_5c = 0;
    unknown_90 = -1;
}

}
