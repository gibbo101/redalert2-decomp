// int __fastcall Unknown_0074A5D0(int id) (0x0074A5D0)
// The index of one of the eight consecutive ids 0x754..0x75B, else -1.
int __fastcall Unknown_0074A5D0(int id)
{
    if (id == 0x754) {
        return 0;
    }
    if (id == 0x755) {
        return 1;
    }
    if (id == 0x756) {
        return 2;
    }
    if (id == 0x757) {
        return 3;
    }
    if (id == 0x758) {
        return 4;
    }
    if (id == 0x759) {
        return 5;
    }
    if (id == 0x75A) {
        return 6;
    }
    return id == 0x75B ? 7 : -1;
}
