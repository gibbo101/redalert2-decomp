// void Unknown_006F2C00() -- 0x006F2C00
// Frees the art block at 0x00AC116C (operator delete) and the companion object at
// 0x00AC1170 (delete through its virtual destructor), clearing each pointer
// (hypothesis; the same pair 0x006F2A30 loads).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_art_ac116c@@3PAXA=00ac116c
// @ref ?unknown_art_ac1170@@3PAVUnknownArtData_006f2390@@A=00ac1170

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac116c;
extern UnknownArtData_006f2390 *unknown_art_ac1170;

void __fastcall Unknown_006F2C00()
{
    if (unknown_art_ac116c != 0) {
        operator delete(unknown_art_ac116c);
        unknown_art_ac116c = 0;
    }
    if (unknown_art_ac1170 != 0) {
        delete unknown_art_ac1170;
        unknown_art_ac1170 = 0;
    }
}
