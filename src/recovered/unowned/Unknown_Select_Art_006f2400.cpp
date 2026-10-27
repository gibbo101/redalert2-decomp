// void *__fastcall Unknown_Select_Art_6f2400(int width, int unused, int unused2) -- 0x006f2400
// Chooses between two art data pointers by the screen width (640 selects the first;
// hypothesis: the low-resolution variant).
// @ref ?unknown_art_7f8730@@3PAXA=007f8730
// @ref ?unknown_art_7f8734@@3PAXA=007f8734
extern void *unknown_art_7f8730;
extern void *unknown_art_7f8734;

void *__fastcall Unknown_Select_Art_6f2400(int width, int unused, int unused2)
{
    void *art = unknown_art_7f8730;
    if (width != 0x280) {
        art = unknown_art_7f8734;
    }
    return art;
}
