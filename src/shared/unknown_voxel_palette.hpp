// UnknownVoxelPalette: a voxel palette lookup (hypothesis: a .VPL file; members
// 0x0071BD00-0x0071C314). A 0x10-byte header (remap range, section count),
// a 256-entry RGB palette (0x300 bytes) and section count * 256 bytes of
// lookup; each buffer is either supplied or owned.
#ifndef RA2_SHARED_UNKNOWN_VOXEL_PALETTE_HPP
#define RA2_SHARED_UNKNOWN_VOXEL_PALETTE_HPP

class FileClass;

struct UnknownVoxelPaletteHeader {
    int unknown_00;                     // +0x00 first remap index (hypothesis)
    int unknown_04;                     // +0x04 last remap index (hypothesis)
    int unknown_08;                     // +0x08 section count
    int unknown_0c;                     // +0x0C
};

class UnknownVoxelPalette {
public:
    UnknownVoxelPalette(unsigned char *palette, unsigned char *table);     // 0x0071BD00
    ~UnknownVoxelPalette();                                     // 0x0071BD70
    int unknown_71bda0(FileClass *file);                        // 0x0071BDA0 (reads the palette; 1 on failure)
    int Run(FileClass *file);                                   // 0x0071BDE0 (reads; 1 on failure)
    int unknown_71be80(FileClass *file);                        // 0x0071BE80 (writes; 1 on failure)
    void unknown_71bf20(float *levels, int count);              // 0x0071BF20 (builds the lookup)
    unsigned char Closest_Color(float red, float green, float blue);    // 0x0071C1C0
    unsigned char unknown_71c250(float red, float green, float blue, bool remap);    // 0x0071C250

    UnknownVoxelPaletteHeader Header;   // +0x00
    unsigned char *Palette;             // +0x10 256 RGB byte triples
    unsigned char *unknown_14;          // +0x14 section count * 256 lookup
    int unknown_18;                     // +0x18 Palette is owned
    int unknown_1c;                     // +0x1C unknown_14 is owned
};

#endif
