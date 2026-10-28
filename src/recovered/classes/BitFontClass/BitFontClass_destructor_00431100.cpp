// BitFontClass::~BitFontClass() (0x00431100)
// Releases the cursor glyph copy and the glyph data.
#include "shared/text_print.hpp"
#include "shared/raw_file_class.hpp"
// @ref ??_7BitFontClass@@6B@=0079c788
// @ref _free=007825e8
// @ref ??3@YAXPAX@Z=00781d3b

BitFontClass::~BitFontClass()
{
    if (unknown_08) {
        free(unknown_08);
    }
    if (Data) {
        Free_Font_Data(Data);
    }
}
