// void Unknown_006F2AB0() -- 0x006F2AB0
// Once loaded (flag 0x00AC1174): clears the flag, releases the backdrop shape at 0x00AC1104
// (freed only when it was allocated, flag 0x00AC1217) and the art pair at
// 0x00AC116C/0x00AC1170 that 0x006F2A30 loads (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_ac1174@@3_NA=00ac1174
// @ref ?unknown_flag_ac1217@@3_NA=00ac1217
// @ref ?unknown_art_ac1104@@3PAXA=00ac1104
// @ref ?unknown_art_ac116c@@3PAXA=00ac116c
// @ref ?unknown_art_ac1170@@3PAVUnknownArtData_006f2390@@A=00ac1170

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern bool unknown_flag_ac1174;
extern bool unknown_flag_ac1217;
extern void *unknown_art_ac1104;
extern void *unknown_art_ac116c;
extern UnknownArtData_006f2390 *unknown_art_ac1170;

void __fastcall Unknown_006F2AB0()
{
    if (unknown_flag_ac1174) {
        unknown_flag_ac1174 = false;
        if (unknown_flag_ac1217) {
            operator delete(unknown_art_ac1104);
            unknown_flag_ac1217 = false;
        }
        unknown_art_ac1104 = 0;
        if (unknown_art_ac116c != 0) {
            operator delete(unknown_art_ac116c);
            unknown_art_ac116c = 0;
        }
        if (unknown_art_ac1170 != 0) {
            delete unknown_art_ac1170;
            unknown_art_ac1170 = 0;
        }
    }
}
