// void Unknown_6F4360() -- 0x006F4360
// Frees the eight art blocks at 0x00AC11B4 and clears their pointers (hypothesis).
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_art_acac11b4@@3PAXA=00ac11b4
// @ref ?unknown_art_acac11b8@@3PAXA=00ac11b8
// @ref ?unknown_art_acac11bc@@3PAXA=00ac11bc
// @ref ?unknown_art_acac11c0@@3PAXA=00ac11c0
// @ref ?unknown_art_acac11c4@@3PAXA=00ac11c4
// @ref ?unknown_art_acac11c8@@3PAXA=00ac11c8
// @ref ?unknown_art_acac11cc@@3PAXA=00ac11cc
// @ref ?unknown_art_acac11d0@@3PAXA=00ac11d0

extern void *unknown_art_acac11b4;
extern void *unknown_art_acac11b8;
extern void *unknown_art_acac11bc;
extern void *unknown_art_acac11c0;
extern void *unknown_art_acac11c4;
extern void *unknown_art_acac11c8;
extern void *unknown_art_acac11cc;
extern void *unknown_art_acac11d0;

void __fastcall Unknown_6F4360()
{
    operator delete(unknown_art_acac11b4);
    unknown_art_acac11b4 = 0;
    operator delete(unknown_art_acac11b8);
    unknown_art_acac11b8 = 0;
    operator delete(unknown_art_acac11bc);
    unknown_art_acac11bc = 0;
    operator delete(unknown_art_acac11c0);
    unknown_art_acac11c0 = 0;
    operator delete(unknown_art_acac11c4);
    unknown_art_acac11c4 = 0;
    operator delete(unknown_art_acac11c8);
    unknown_art_acac11c8 = 0;
    operator delete(unknown_art_acac11cc);
    unknown_art_acac11cc = 0;
    operator delete(unknown_art_acac11d0);
    unknown_art_acac11d0 = 0;
}
