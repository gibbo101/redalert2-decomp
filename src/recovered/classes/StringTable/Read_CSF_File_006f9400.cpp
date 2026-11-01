// The .csf reader of the string table unit (0x006F8BE0-0x006FA1DF).
#include "shared/string_table_file.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_max_label_length_ad0428@@3HA=00ad0428
// @ref ?unknown_labels_ad0440@@3PAUStringLabel@@A=00ad0440
// @ref ?unknown_texts_ad0444@@3PAPAGA=00ad0444
// @ref ?unknown_speech_ad0448@@3PAPADA=00ad0448
// @ref ?unknown_line_acf410@@3PADA=00acf410
// @ref ?unknown_wide_text_ac93fc@@3PAGA=00ac93fc
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Open@CCFileClass@@UAEHH@Z=00469220
// @ref ?Read@CCFileClass@@UAEJPAXJ@Z=00469060
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658

// Drops repeated spaces and the spaces at the ends of lines.
static inline void Collapse_White_Space(wchar_t *string)
{
    wchar_t *in = string;
    wchar_t previous = 0;
    int line_start = 1;
    wchar_t *out = string;
    for (wchar_t c = *in++; c != 0; c = *in++) {
        if (c == ' ') {
            if (previous == c || line_start) {
                continue;
            }
        } else if (c == '\n' || c == '\t') {
            if (previous == ' ') {
                out--;
            }
            *out = c;
            line_start = 1;
            previous = c;
            out++;
            continue;
        }
        *out++ = c;
        previous = c;
        line_start = 0;
    }
    if (previous == ' ') {
        out--;
    }
    *out = 0;
}

// Undoes the .csf string encoding (every character inverted).
static void Decode_String(wchar_t *string)
{
    for (; *string != 0; string++) {
        *string = ~*string;
    }
}

// int __fastcall Read_CSF_File_006f9400(char const *name) (0x006F9400): reads the labels and strings of a .csf
// file into the tables Init sized from its header; 0 when the file is short or malformed.
int __fastcall Read_CSF_File_006f9400(char const *name)
{
    CCFileClass file(name);
    int string_index = 0;
    if (!file.Is_Available() || !file.Open(FILE_RIGHTS_READ)) {
        return 0;
    }
    CSFHeader header;
    if (file.Read(&header, sizeof(header)) != sizeof(header)) {
        return 0;
    }
    int id;
    int count;
    int length;
    int label = 0;
    while (file.Read(&id, 4) == 4) {
        if (id != 'LBL ') {
            return 0;
        }
        file.Read(&count, 4);
        file.Read(&length, 4);
        if (length != 0) {
            file.Read(unknown_line_acf410, length);
        }
        unknown_line_acf410[length] = 0;
        strcpy(unknown_labels_ad0440[label].Name, unknown_line_acf410);
        if (length > unknown_max_label_length_ad0428) {
            unknown_max_label_length_ad0428 = length;
        }
        unknown_labels_ad0440[label].FirstString = string_index;
        unknown_labels_ad0440[label].StringCount = count;
        for (int index = 0; index < count; index++) {
            file.Read(&id, 4);
            if (id != 'STR ' && id != 'STRW') {
                return 0;
            }
            file.Read(&length, 4);
            if (length != 0) {
                file.Read(unknown_wide_text_ac93fc, length * 2);
            }
            unknown_wide_text_ac93fc[length] = 0;
            Decode_String(unknown_wide_text_ac93fc);
            Collapse_White_Space(unknown_wide_text_ac93fc);
            unknown_texts_ad0444[string_index + index] = (wchar_t *)::operator new((wcslen(unknown_wide_text_ac93fc) + 1) * sizeof(wchar_t));
            wcscpy(unknown_texts_ad0444[string_index + index], unknown_wide_text_ac93fc);
            if (id == 'STRW') {
                file.Read(&length, 4);
                if (length != 0) {
                    file.Read(unknown_line_acf410, length);
                }
                unknown_line_acf410[length] = 0;
                if (length != 0) {
                    unknown_speech_ad0448[string_index + index] = (char *)::operator new(length + 1);
                    strcpy(unknown_speech_ad0448[string_index + index], unknown_line_acf410);
                }
            }
        }
        label++;
        string_index += count;
    }
    return 1;
}
