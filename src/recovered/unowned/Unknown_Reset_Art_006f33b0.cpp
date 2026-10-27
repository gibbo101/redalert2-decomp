// void __fastcall Unknown_Reset_Art_006F33B0(int width, int height) -- 0x006F33B0
// Frees the eight blocks 0x006F3E70 builds and rebuilds them for the new size (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Unknown_006F3E70@@YIXHH@Z=006f3e70
// @ref ?unknown_art_ac11b4@@3PAXA=00ac11b4
// @ref ?unknown_art_ac11b8@@3PAXA=00ac11b8
// @ref ?unknown_art_ac11bc@@3PAXA=00ac11bc
// @ref ?unknown_art_ac11c0@@3PAXA=00ac11c0
// @ref ?unknown_art_ac11c4@@3PAXA=00ac11c4
// @ref ?unknown_art_ac11c8@@3PAXA=00ac11c8
// @ref ?unknown_art_ac11cc@@3PAXA=00ac11cc
// @ref ?unknown_art_ac11d0@@3PAXA=00ac11d0

void __fastcall Unknown_006F3E70(int width, int height);
extern void *unknown_art_ac11b4;
extern void *unknown_art_ac11b8;
extern void *unknown_art_ac11bc;
extern void *unknown_art_ac11c0;
extern void *unknown_art_ac11c4;
extern void *unknown_art_ac11c8;
extern void *unknown_art_ac11cc;
extern void *unknown_art_ac11d0;

void __fastcall Unknown_Reset_Art_006F33B0(int width, int height)
{
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
    Unknown_006F3E70(width, height);
}
