// void BitFontClass::Free_Font_Data(FontDataType *data) (0x004313C0)
// Deletes a glyph data block and its tables.
#include "shared/text_print.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void __fastcall BitFontClass::Free_Font_Data(FontDataType *data)
{
    if (data->Map) {
        delete data->Map;
    }
    if (data->Glyphs) {
        delete data->Glyphs;
    }
    delete data;
}
