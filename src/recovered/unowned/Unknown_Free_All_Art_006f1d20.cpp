// void Unknown_Free_All_Art_006F1D20() -- 0x006F1D20
// Frees every art resource the shell loaded: the four flagged buffers
// (0x00AC1218..0x00AC1220 and 0x00AC10C0), the two art pairs 0x006F20B0 loads
// (0x00AC1130..0x00AC113C), then, when the second set is loaded (0x00AC119C),
// the second set's pairs and blocks, and finally the third set (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Unknown_006F4160@@YIXXZ=006f4160
// @ref ?Unknown_6F42D0@@YIXXZ=006f42d0
// @ref ?Unknown_0051A270@@YIXXZ=0051a270
// @ref ?Unknown_006F5150@@YIXXZ=006f5150
// @ref ?Unknown_6F5400@@YIXXZ=006f5400
// @ref ?unknown_art_ac1218@@3PAXA=00ac1218
// @ref ?unknown_art_ac121c@@3PAXA=00ac121c
// @ref ?unknown_art_ac1220@@3PAXA=00ac1220
// @ref ?unknown_art_ac10c0@@3PAXA=00ac10c0
// @ref ?unknown_flag_ac1224@@3_NA=00ac1224
// @ref ?unknown_flag_ac1225@@3_NA=00ac1225
// @ref ?unknown_flag_ac1226@@3_NA=00ac1226
// @ref ?unknown_flag_ac1227@@3_NA=00ac1227
// @ref ?unknown_art_ac1130@@3PAXA=00ac1130
// @ref ?unknown_art_ac1134@@3PAVUnknownArtData_006f2390@@A=00ac1134
// @ref ?unknown_art_ac1138@@3PAXA=00ac1138
// @ref ?unknown_art_ac113c@@3PAVUnknownArtData_006f2390@@A=00ac113c
// @ref ?unknown_flag_ac119c@@3_NA=00ac119c
// @ref ?unknown_art_ac11b4@@3PAXA=00ac11b4
// @ref ?unknown_art_ac11b8@@3PAXA=00ac11b8
// @ref ?unknown_art_ac11bc@@3PAXA=00ac11bc
// @ref ?unknown_art_ac11c0@@3PAXA=00ac11c0
// @ref ?unknown_art_ac11c4@@3PAXA=00ac11c4
// @ref ?unknown_art_ac11c8@@3PAXA=00ac11c8
// @ref ?unknown_art_ac11cc@@3PAXA=00ac11cc
// @ref ?unknown_art_ac11d0@@3PAXA=00ac11d0
// @ref ?unknown_art_ac11a0@@3PAXA=00ac11a0
// @ref ?unknown_art_ac11a4@@3PAVUnknownArtData_006f2390@@A=00ac11a4
// @ref ?unknown_art_ac11a8@@3PAXA=00ac11a8
// @ref ?unknown_art_ac11ac@@3PAVUnknownArtData_006f2390@@A=00ac11ac
// @ref ?unknown_flag_ac11b0@@3_NA=00ac11b0

class UnknownArtData_006f2390 {
public:
    virtual ~UnknownArtData_006f2390();
};
extern void *unknown_art_ac1218;
extern void *unknown_art_ac121c;
extern void *unknown_art_ac1220;
extern void *unknown_art_ac10c0;
extern bool unknown_flag_ac1224;
extern bool unknown_flag_ac1225;
extern bool unknown_flag_ac1226;
extern bool unknown_flag_ac1227;
extern void *unknown_art_ac1130;
extern UnknownArtData_006f2390 *unknown_art_ac1134;
extern void *unknown_art_ac1138;
extern UnknownArtData_006f2390 *unknown_art_ac113c;
extern bool unknown_flag_ac119c;
extern void *unknown_art_ac11b4;
extern void *unknown_art_ac11b8;
extern void *unknown_art_ac11bc;
extern void *unknown_art_ac11c0;
extern void *unknown_art_ac11c4;
extern void *unknown_art_ac11c8;
extern void *unknown_art_ac11cc;
extern void *unknown_art_ac11d0;
extern void *unknown_art_ac11a0;
extern UnknownArtData_006f2390 *unknown_art_ac11a4;
extern void *unknown_art_ac11a8;
extern UnknownArtData_006f2390 *unknown_art_ac11ac;
extern bool unknown_flag_ac11b0;
void __fastcall Unknown_006F4160();
void __fastcall Unknown_6F42D0();
void __fastcall Unknown_0051A270();
void __fastcall Unknown_006F5150();
void __fastcall Unknown_6F5400();

void __fastcall Unknown_Free_All_Art_006F1D20()
{
    if (unknown_flag_ac1224) {
        operator delete(unknown_art_ac1218);
        unknown_flag_ac1224 = false;
    }
    unknown_art_ac1218 = 0;
    if (unknown_flag_ac1225) {
        operator delete(unknown_art_ac121c);
        unknown_flag_ac1225 = false;
    }
    unknown_art_ac121c = 0;
    if (unknown_flag_ac1226) {
        operator delete(unknown_art_ac1220);
        unknown_flag_ac1226 = false;
    }
    unknown_art_ac1220 = 0;
    if (unknown_flag_ac1227) {
        operator delete(unknown_art_ac10c0);
        unknown_flag_ac1227 = false;
    }
    unknown_art_ac10c0 = 0;
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
    if (unknown_flag_ac119c) {
        unknown_flag_ac119c = false;
        Unknown_006F4160();
        Unknown_6F42D0();
        operator delete(unknown_art_ac11b4);
        unknown_art_ac11b4 = 0;
        operator delete(unknown_art_ac11b8);
        unknown_art_ac11b8 = 0;
        operator delete(unknown_art_ac11bc);
        unknown_art_ac11bc = 0;
        operator delete(unknown_art_ac11c0);
        unknown_art_ac11c0 = 0;
        operator delete(unknown_art_ac11c4);
        unknown_art_ac11c4 = 0;
        operator delete(unknown_art_ac11c8);
        unknown_art_ac11c8 = 0;
        operator delete(unknown_art_ac11cc);
        unknown_art_ac11cc = 0;
        operator delete(unknown_art_ac11d0);
        unknown_art_ac11d0 = 0;
        Unknown_0051A270();
    }
    Unknown_006F5150();
    if (unknown_art_ac11a0 != 0) {
        operator delete(unknown_art_ac11a0);
        unknown_art_ac11a0 = 0;
    }
    if (unknown_art_ac11a4 != 0) {
        delete unknown_art_ac11a4;
        unknown_art_ac11a4 = 0;
    }
    if (unknown_art_ac11a8 != 0) {
        operator delete(unknown_art_ac11a8);
        unknown_art_ac11a8 = 0;
    }
    if (unknown_art_ac11ac != 0) {
        delete unknown_art_ac11ac;
        unknown_art_ac11ac = 0;
    }
    Unknown_6F5400();
    unknown_flag_ac11b0 = false;
}
