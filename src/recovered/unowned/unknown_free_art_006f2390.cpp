// void unknown_free_art_6f2390() -- 0x006F2390
// Purpose: frees the two art sets loaded by 0x006F22C0: the shapes at
// 0x00AC1130/0x00AC1138 (operator delete) and the companion objects at
// 0x00AC1134/0x00AC113C (array delete through their virtual destructor),
// clearing each pointer.
// Assumptions: the companion objects' class is unidentified.
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_art_ac1130@@3PAXA=00ac1130
// @ref ?unknown_art_ac1134@@3PAVUnknownArtData_006f2390@@A=00ac1134
// @ref ?unknown_art_ac1138@@3PAXA=00ac1138
// @ref ?unknown_art_ac113c@@3PAVUnknownArtData_006f2390@@A=00ac113c

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac1130;
extern UnknownArtData_006f2390 *unknown_art_ac1134;
extern void *unknown_art_ac1138;
extern UnknownArtData_006f2390 *unknown_art_ac113c;

void unknown_free_art_6f2390()
{
    if (unknown_art_ac1130 != 0) {
        operator delete(unknown_art_ac1130);
        unknown_art_ac1130 = 0;
    }
    if (unknown_art_ac1134 != 0) {
        delete [] unknown_art_ac1134;
        unknown_art_ac1134 = 0;
    }
    if (unknown_art_ac1138 != 0) {
        operator delete(unknown_art_ac1138);
        unknown_art_ac1138 = 0;
    }
    if (unknown_art_ac113c != 0) {
        delete [] unknown_art_ac113c;
        unknown_art_ac113c = 0;
    }
}
