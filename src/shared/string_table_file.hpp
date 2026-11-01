// The string table unit's file formats and tables (0x006F8BE0-0x006FA1DF; RA2 only): StringTable::Load_String
// (0x006F9EC0) searches the label index built from <name>.csf or, failing that, the quoted entries of the text
// file <name>. Names are hypotheses.
#ifndef RA2_SHARED_STRING_TABLE_FILE_HPP
#define RA2_SHARED_STRING_TABLE_FILE_HPP

#include "shared/string_table.hpp"

// The header of a .csf file.
struct CSFHeader {
    int ID;             // 'CSF '
    int Version;
    int LabelCount;
    int StringCount;
    int Unused;
    int Language;
};

// One label: its name and the strings that follow it.
struct StringLabel {
    char Name[0x20];
    int StringCount;    // +0x20 strings of the label
    int FirstString;    // +0x24 index of its first string
};

// One entry of the language table (0x007F8CF0; the list ends at ID 10).
struct UnknownTableEntry_7f8cf0 {
    int ID;
    char const *Name;
    char const *Code;
    char const *Unknown;
};
typedef UnknownTableEntry_7f8cf0 LanguageInfo;

extern int unknown_initialized_ad044c;          // 0x00AD044C
extern int unknown_max_label_length_ad0428;     // 0x00AD0428
extern char const *unknown_file_name_ad0434;    // 0x00AD0434
extern char unknown_csf_name_ac5388[];          // 0x00AC5388
extern void *unknown_text_file_ad0430;          // 0x00AD0430
extern int unknown_label_count_ad0438;          // 0x00AD0438
extern int unknown_string_count_ad043c;         // 0x00AD043C
extern StringLabel *unknown_labels_ad0440;      // 0x00AD0440
extern wchar_t **unknown_texts_ad0444;          // 0x00AD0444
extern char **unknown_speech_ad0448;            // 0x00AD0448
extern int unknown_text_option_ad0450;          // 0x00AD0450 (reverses letter runs of text-file strings)
extern int unknown_language_7f8da0;             // 0x007F8DA0
extern int unknown_allow_text_7f8ce8;           // 0x007F8CE8
extern LanguageInfo unknown_languages_7f8cf0[]; // 0x007F8CF0 (ends with ID 10)
extern char unknown_line_acf410[0x1000];        // 0x00ACF410
extern char unknown_text_ac3378[0x1008];        // 0x00AC3378
extern char unknown_label_ac4380[0x1008];       // 0x00AC4380
extern wchar_t unknown_wide_text_ac93fc[0x1000];      // 0x00AC93FC
extern char unknown_reversed_text_acd410[];     // 0x00ACD410

UnknownTableEntry_7f8cf0 *__fastcall unknown_table_find_6f8dd0(int id);   // 0x006F8DD0
char const *__fastcall unknown_table_name_6f8e00(int id);                  // 0x006F8E00

#endif
