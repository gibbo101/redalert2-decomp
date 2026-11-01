#pragma once
// Hi-colour VQA support (the unit at 0x0070B690-0x0070C43F): a 15-bit to
// screen-format pixel table and the table-driven 16-bit UnVQ block decoders
// that VQAClass installs as its draw callbacks. Names follow the Westwood
// VQA library (unvqtblc); argument roles are read from the code.

// Screen pixel formats the table can produce (red, green, blue field shifts).
enum HicolorModeType {
    HICOLOR_MODE_555,   // 10, 5, 0
    HICOLOR_MODE_556,   // 11, 6, 1
    HICOLOR_MODE_565,   // 11, 6, 0
    HICOLOR_MODE_655    // 11, 5, 0
};

extern unsigned short *HicolorTable;                               // 0x00AD0614

bool __fastcall Hicolor_Init_Table(int mode);                      // 0x0070B690
void Hicolor_Clear_Table();                                        // 0x0070B7D0
void __fastcall Hicolor_Translate(void *buffer, int count);        // 0x0070B7F0

void __cdecl UnVQ2_4x4_Table(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
    unsigned long blocks_per_row, unsigned long rows, unsigned long width);    // 0x0070B820
void __cdecl UnVQ2_4x2_Table(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
    unsigned long blocks_per_row, unsigned long rows, unsigned long width);    // 0x0070BBC0
void __cdecl UnVQ1_4x4_Table(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
    unsigned long blocks_per_row, unsigned long rows, unsigned long width);    // 0x0070BF60
void __cdecl UnVQ1_4x2_Table(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
    unsigned long blocks_per_row, unsigned long rows, unsigned long width);    // 0x0070C0A0
