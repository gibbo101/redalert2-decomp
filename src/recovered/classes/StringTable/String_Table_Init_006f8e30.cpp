// The string table unit (0x006F8BE0-0x006FA1DF; RA2 only): loads the localized strings from <name>.csf (or,
// failing that, the quoted entries of the text file <name>) into a label index searched by
// StringTable::Load_String (0x006F9EC0).
#include "shared/string_table_file.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/session_state.hpp"
#include "shared/map_seed.hpp"

extern "C" void *__cdecl fopen(char const *name, char const *mode);                           // 0x00783A45
extern "C" char *__cdecl fgets(char *buffer, int count, void *file);                           // 0x00785547
extern "C" int __cdecl fclose(void *file);                                                     // 0x0078395B
extern "C" void __cdecl qsort(void *base, unsigned int count, unsigned int width,
                              int (__cdecl *compare)(void const *, void const *));             // 0x00781D46
extern "C" char *__cdecl strchr(char const *string, int character);                           // 0x00784130
extern "C" int __cdecl _stricmp(char const *left, char const *right);                          // 0x00781F20
int __cdecl Unknown_isspace_00784aa8(short character);                                         // 0x00784AA8
extern UnknownSessionState unknown_session_a3d298;
extern MapSeedClass unknown_map_seed_a6fd68;

// @ref ?unknown_initialized_ad044c@@3HA=00ad044c
// @ref ?unknown_max_label_length_ad0428@@3HA=00ad0428
// @ref ?unknown_file_name_ad0434@@3PBDB=00ad0434
// @ref ?unknown_csf_name_ac5388@@3PADA=00ac5388
// @ref ?unknown_text_file_ad0430@@3PAXA=00ad0430
// @ref ?unknown_label_count_ad0438@@3HA=00ad0438
// @ref ?unknown_string_count_ad043c@@3HA=00ad043c
// @ref ?unknown_labels_ad0440@@3PAUStringLabel@@A=00ad0440
// @ref ?unknown_texts_ad0444@@3PAPAGA=00ad0444
// @ref ?unknown_speech_ad0448@@3PAPADA=00ad0448
// @ref ?unknown_language_7f8da0@@3HA=007f8da0
// @ref ?unknown_allow_text_7f8ce8@@3HA=007f8ce8
// @ref ?unknown_line_acf410@@3PADA=00acf410
// @ref ?unknown_text_ac3378@@3PADA=00ac3378
// @ref ?unknown_label_ac4380@@3PADA=00ac4380
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_map_seed_a6fd68@@3VMapSeedClass@@A=00a6fd68
// @ref ?Unknown_0066EAA0@UnknownSessionState@@QAEXXZ=0066eaa0
// @ref ?Set_Default_Description_00576fe0@MapSeedClass@@QAEXXZ=00576fe0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Unknown_isspace_00784aa8@@YAHF@Z=00784aa8
// @ref _strchr=00784130
// @ref _fopen=00783a45
// @ref _fgets=00785547
// @ref _fclose=0078395b
// @ref _qsort=00781d46
// @ref __stricmp=00781f20
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??1CCFileClass@@UAE@XZ=0051ad20
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Open@CCFileClass@@UAEHH@Z=00469220
// @ref ?Read@CCFileClass@@UAEJPAXJ@Z=00469060
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_C@_04EIIJ@?4csf?$AA@=007f8e68
// @ref ??_C@_01LHO@r?$AA@=007e6acc
// @ref ?Read_CSF_File_006f9400@@YIHPBD@Z=006f9400
// @ref ?Read_Text_File_006f9790@@YIHXZ=006f9790
// @ref ??_C@_03PIHE@END?$AA@=007f8e64
// @ref ??_C@_0BC@DOGL@MaxLabelLen?5?$DN?5?$CFd?6?$AA@=007f8e50
// @ref ??_C@_0O@IKP@Language?3?5?$CFs?6?$AA@=007f8e40

void __fastcall Unknown_006F92A0(void *file, char *source, char *text, char *label, int limit);   // 0x006F92A0
int __fastcall Read_CSF_File_006f9400(char const *name);                                        // 0x006F9400
int __fastcall Read_Text_File_006f9790();                                                                   // 0x006F9790

// Opens a text file for reading.
static void *Open_File(char const *name)
{
    return fopen(name, "r");
}

// Closes a text file.
static void Close_File(void *file)
{
    fclose(file);
}

// The table sizes and language from the header of a .csf file; false when it is not one.
static int Read_CSF_Header(char const *name)
{
    CCFileClass file(name);
    int ok = 0;
    if (file.Is_Available() && file.Open(FILE_RIGHTS_READ)) {
        CSFHeader header;
        if (file.Read(&header, sizeof(header)) == sizeof(header) && header.ID == 'CSF ') {
            unknown_label_count_ad0438 = header.LabelCount;
            unknown_string_count_ad043c = header.StringCount;
            unknown_language_7f8da0 = header.Version < 2 ? 0 : header.Language;
            ok = 1;
        }
        return ok;
    }
    return 0;
}

// Drops leading and trailing white space.
static void Strip_Line(char *line)
{
    char *in = line;
    char c = *in;
    while (c != 0 && Unknown_isspace_00784aa8(c)) {
        c = *++in;
    }
    char *out = line;
    while ((*out++ = *in++) != 0) {
    }
    out -= 2;
    while (out > line && *out != 0 && Unknown_isspace_00784aa8(*out)) {
        out--;
    }
    out[1] = 0;
}

// int __fastcall String_Table_Init_006f8e30(char const *filename) (0x006F8E30): loads the table once; 1 when it
// holds strings. The body runs to 0x006F929D (the frozen inventory row stopped at 0x006F91F5, inside it).
int __fastcall String_Table_Init_006f8e30(char const *filename)
{
    if (unknown_initialized_ad044c != 0) {
        return 1;
    }
    unknown_initialized_ad044c = 1;
    unknown_max_label_length_ad0428 = 0;
    unknown_file_name_ad0434 = filename;
    if (filename == 0 || *filename == 0) {
        return 0;
    }
    strcpy(unknown_csf_name_ac5388, filename);
    char *dot = strchr(unknown_csf_name_ac5388, '.');
    if (dot != 0) {
        *dot = 0;
    }
    strcat(unknown_csf_name_ac5388, ".csf");
    int csf;
    if (Read_CSF_Header(unknown_csf_name_ac5388)) {
        csf = 1;
    } else {
        if (unknown_allow_text_7f8ce8 == 0) {
            return 0;
        }
        unknown_text_file_ad0430 = fopen(filename, "r");
        if (unknown_text_file_ad0430 == 0) {
            return 0;
        }
        unknown_label_count_ad0438 = 0;
        unknown_string_count_ad043c = 0;
        while (true) {
            if (fgets(unknown_line_acf410, 0xFFF, unknown_text_file_ad0430) == 0) {
                break;
            }
            Strip_Line(unknown_line_acf410);
            if (unknown_line_acf410[0] == '"') {
                int length = strlen(unknown_line_acf410);
                unknown_line_acf410[length] = '\n';
                unknown_line_acf410[length + 1] = 0;
                Unknown_006F92A0(unknown_text_file_ad0430, &unknown_line_acf410[1], unknown_text_ac3378, unknown_label_ac4380, 0x1000);
                unknown_string_count_ad043c++;
                continue;
            }
            if (_stricmp(unknown_line_acf410, "END") == 0) {
                unknown_label_count_ad0438++;
            }
        }
        unknown_label_count_ad0438 += 500;
        unknown_string_count_ad043c += 1000;
        Close_File(unknown_text_file_ad0430);
        csf = 0;
    }
    if (unknown_string_count_ad043c == 0 || unknown_label_count_ad0438 == 0) {
        return 0;
    }
    unknown_labels_ad0440 = (StringLabel *)::operator new(unknown_label_count_ad0438 * sizeof(StringLabel));
    if (unknown_labels_ad0440 == 0) {
        return 0;
    }
    memset(unknown_labels_ad0440, 0, unknown_label_count_ad0438 * sizeof(StringLabel));
    unknown_texts_ad0444 = (wchar_t **)::operator new(unknown_string_count_ad043c * sizeof(wchar_t *));
    if (unknown_texts_ad0444 == 0) {
        return 0;
    }
    memset(unknown_texts_ad0444, 0, unknown_string_count_ad043c * sizeof(wchar_t *));
    unknown_speech_ad0448 = (char **)::operator new(unknown_string_count_ad043c * sizeof(char *));
    if (unknown_speech_ad0448 == 0) {
        return 0;
    }
    memset(unknown_speech_ad0448, 0, unknown_string_count_ad043c * sizeof(char *));
    if (csf == 0) {
        unknown_text_file_ad0430 = Open_File(filename);
        if (unknown_text_file_ad0430 == 0) {
            return 0;
        }
        if (!Read_Text_File_006f9790()) {
            Close_File(unknown_text_file_ad0430);
            return 0;
        }
        Close_File(unknown_text_file_ad0430);
    } else {
        Read_CSF_File_006f9400(unknown_csf_name_ac5388);
    }
    qsort(unknown_labels_ad0440, unknown_label_count_ad0438, sizeof(StringLabel), (int (__cdecl *)(void const *, void const *))_stricmp);
    Debug_Printf("MaxLabelLen = %d\n", unknown_max_label_length_ad0428);
    Debug_Printf("Language: %s\n", unknown_table_name_6f8e00(unknown_language_7f8da0));
    unknown_session_a3d298.Unknown_0066EAA0();
    unknown_map_seed_a6fd68.Set_Default_Description_00576fe0();
    return 1;
}
