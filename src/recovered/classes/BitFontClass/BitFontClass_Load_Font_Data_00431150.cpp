// FontDataType *BitFontClass::Load_Font_Data(char const *filename) (0x00431150)
// Reads a font file's glyph data: a "fonT" file holds the metrics and the character map
// directly, a "FoNt" file a header, a table of character ranges and the glyphs. Null when
// the file cannot be read.
#include "shared/text_print.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/crt_memory.hpp"
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50

// The header of a "fonT" file (0x1C bytes): the metrics of FontDataType.
struct FontShortHeaderType {
    int Magic;          // 'fonT'
    int unknown_00;
    int Width;
    int unknown_08;
    int Height;
    int GlyphCount;
    int GlyphSize;
};

FontDataType *__fastcall BitFontClass::Load_Font_Data(char const *filename)
{
    FontDataType *data = 0;
    FontShortHeaderType header;
    CCFileClass *file = new CCFileClass(filename);
    if (file != 0) {
        if (file->Is_Available() && file->Open(FILE_RIGHTS_READ)) {
            data = new FontDataType;
            if (data != 0) {
                memset(data, 0, sizeof(FontDataType));
                data->Map = (unsigned short *)operator new(0x10000 * sizeof(unsigned short));
                if (data->Map != 0) {
                    memset(data->Map, 0, 0x10000 * sizeof(unsigned short));
                    if (file->Read(&header, sizeof(header)) == sizeof(header)) {
                        if (header.Magic == 0x546E6F66) {
                            data->unknown_08 = header.unknown_08;
                            data->Height = header.Height;
                            data->Width = header.Width;
                            data->unknown_00 = header.unknown_00;
                            data->GlyphSize = header.GlyphSize;
                            data->GlyphCount = header.GlyphCount;
                            if (file->Read(data->Map, 0x10000 * sizeof(unsigned short)) != 0x10000 * sizeof(unsigned short)) {
                                goto failed;
                            }
                        } else if (header.Magic == 0x744E6F46) {
                            file->Seek(0, FILE_SEEK_START);
                            FontFileHeaderType fileheader;
                            if (file->Read(&fileheader, sizeof(fileheader)) != sizeof(fileheader)) {
                                goto failed;
                            }
                            data->unknown_08 = fileheader.unknown_0c;
                            data->Height = fileheader.Height;
                            data->Width = fileheader.Width;
                            data->unknown_00 = fileheader.unknown_04;
                            data->GlyphSize = fileheader.GlyphSize;
                            FontRangeType *ranges = (FontRangeType *)malloc(fileheader.RangeCount * sizeof(FontRangeType));
                            if (ranges == 0) {
                                goto failed;
                            }
                            file->Seek(fileheader.RangeOffset, FILE_SEEK_START);
                            if (file->Read(ranges, fileheader.RangeCount * sizeof(FontRangeType)) != fileheader.RangeCount * sizeof(FontRangeType)) {
                                goto failed;
                            }
                            data->GlyphCount = 0;
                            for (unsigned index = 0; index < (unsigned)fileheader.RangeCount; index++) {
                                unsigned short glyph = ranges[index].First;
                                for (int character = ranges[index].Low; character <= ranges[index].High; character++, glyph++) {
                                    data->Map[character] = glyph + 1;
                                    data->GlyphCount++;
                                }
                            }
                            free(ranges);
                            file->Seek(fileheader.GlyphOffset, FILE_SEEK_START);
                        } else {
                            goto failed;
                        }
                        int size = data->GlyphCount * data->GlyphSize;
                        data->MappedCount = 0;
                        for (int character = 0; character < 0x10000; character++) {
                            if (data->Map[character]) {
                                data->MappedCount++;
                            }
                        }
                        data->Glyphs = (unsigned char *)operator new(size);
                        if (data->Glyphs != 0 && file->Read(data->Glyphs, size) == size) {
                            goto loaded;
                        }
                    }
                }
failed:
                if (data->Map) {
                    delete data->Map;
                }
                if (data->Glyphs) {
                    delete data->Glyphs;
                }
                delete data;
                data = 0;
            }
        }
loaded:
        delete file;
    }
    return data;
}
