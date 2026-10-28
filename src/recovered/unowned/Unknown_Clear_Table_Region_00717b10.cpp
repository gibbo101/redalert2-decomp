// void __fastcall Unknown_Clear_Table_Region_00717B10(int x, int y, unsigned int width, int height) (0x00717B10)
// Clears a width x height rectangle of the 256 x 256 byte table at 0x00AE3408 (row stride 256), or the whole
// table when the rectangle leaves it (x or y negative, or the right/bottom edge above 255).
// @ref ?unknown_table_ae3408@@3PAEA=00ae3408
extern "C" void *__cdecl memset(void *destination, int value, unsigned int length);
#pragma intrinsic(memset)

extern unsigned char unknown_table_ae3408[0x10000];

void __fastcall Unknown_Clear_Table_Region_00717B10(int x, int y, unsigned int width, int height)
{
    if (x < 0 || y < 0 || x + (int)width > 255 || (height += y) > 255) {
        memset(unknown_table_ae3408, 0, sizeof(unknown_table_ae3408));
    } else if (y <= height) {
        unsigned char *row = &unknown_table_ae3408[x + y * 256];
        int rows = height - y + 1;
        do {
            memset(row, 0, width);
            row += 256;
            rows--;
        } while (rows != 0);
    }
}
