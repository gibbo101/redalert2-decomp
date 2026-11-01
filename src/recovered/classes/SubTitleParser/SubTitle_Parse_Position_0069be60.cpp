// void __fastcall unknown_subtitle_parse_position(unsigned short *value, SubTitle *subtitle) (0x0069BE60):
// the "Position" handler: "[line:]alignment" with the alignment one of Left, Right, Center (default).
struct SubTitleAlignmentName {
    unsigned short const *Name;
    int Alignment;
};
extern SubTitleAlignmentName unknown_subtitle_alignments_7f6320[];
// @ref ?unknown_subtitle_alignments_7f6320@@3PAUSubTitleAlignmentName@@A=007f6320
extern "C" long __cdecl wcstol(unsigned short const *string, unsigned short **end, int base);   // 0x00784BB8

void __fastcall unknown_subtitle_parse_position(unsigned short *value, SubTitle *subtitle)
{
    unsigned short *colon = wcschr(value, ':');
    if (colon != 0) {
        *colon = 0;
        subtitle->Set_Line_Position(wcstol(value, 0, 0));
        value = colon + 1;
    }
    int alignment = 2;
    for (int index = 0; unknown_subtitle_alignments_7f6320[index].Name != 0; index++) {
        if (_wcsicmp(value, unknown_subtitle_alignments_7f6320[index].Name) == 0) {
            alignment = unknown_subtitle_alignments_7f6320[index].Alignment;
            break;
        }
    }
    subtitle->Set_Alignment(alignment);
}
