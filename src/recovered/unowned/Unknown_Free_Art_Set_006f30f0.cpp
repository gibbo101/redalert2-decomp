// void Unknown_Free_Art_Set_006F30F0() -- 0x006F30F0
// Frees the second shell set loaded by 0x006F2FB0 (flag 0x00AC119C) (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_flag_ac119c@@3_NA=00ac119c
// @ref ?Unknown_006F4160@@YIXXZ=006f4160
// @ref ?Unknown_6F42D0@@YIXXZ=006f42d0
// @ref ?Unknown_0051A270@@YIXXZ=0051a270
// @ref ?unknown_art_ac11b4@@3PAXA=00ac11b4
// @ref ?unknown_art_ac11b8@@3PAXA=00ac11b8
// @ref ?unknown_art_ac11bc@@3PAXA=00ac11bc
// @ref ?unknown_art_ac11c0@@3PAXA=00ac11c0
// @ref ?unknown_art_ac11c4@@3PAXA=00ac11c4
// @ref ?unknown_art_ac11c8@@3PAXA=00ac11c8
// @ref ?unknown_art_ac11cc@@3PAXA=00ac11cc
// @ref ?unknown_art_ac11d0@@3PAXA=00ac11d0

void __fastcall Unknown_006F4160();
void __fastcall Unknown_6F42D0();
void __fastcall Unknown_0051A270();
extern bool unknown_flag_ac119c;
extern void *unknown_art_ac11b4;
extern void *unknown_art_ac11b8;
extern void *unknown_art_ac11bc;
extern void *unknown_art_ac11c0;
extern void *unknown_art_ac11c4;
extern void *unknown_art_ac11c8;
extern void *unknown_art_ac11cc;
extern void *unknown_art_ac11d0;

void __fastcall Unknown_Free_Art_Set_006F30F0()
{
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
}
