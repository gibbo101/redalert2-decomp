// void Unknown_006F2F70() -- 0x006F2F70
// Frees the art block at 0x00AC116C (operator delete) and the companion object at
// 0x00AC1170 (delete through its virtual destructor), clearing each pointer
// (hypothesis; the same pair 0x006F2C40 loads).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_art_ac1178@@3PAXA=00ac1178
// @ref ?unknown_art_ac117c@@3PAVUnknownArtData_006f2390@@A=00ac117c

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac1178;
extern UnknownArtData_006f2390 *unknown_art_ac117c;

void __fastcall Unknown_006F2F70()
{
    if (unknown_art_ac1178 != 0) {
        operator delete(unknown_art_ac1178);
        unknown_art_ac1178 = 0;
    }
    if (unknown_art_ac117c != 0) {
        delete unknown_art_ac117c;
        unknown_art_ac117c = 0;
    }
}
