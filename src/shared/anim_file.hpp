// Animate and AnimFile: a Deluxe Paint style animation file (".ANM": an
// "LPF " header, "ANIM" content type, 320x200, 256-colour pages) played
// through a FileClass (AnimFile.cpp, members 0x00423F90-0x00424C3D; RTTI
// vtables 0x0079C294 AnimFile, 0x0079C2B8 Animate). Names are hypotheses
// from the on-disk format.
//
// Layout (from the constructor 0x00423F90, Init 0x00424110 and the page
// readers):
//   +0x004  char Buffer[0x80]       first header read (cleared, read 0x80)
//   +0x084  FileClass *File         the animation file
//   +0x088  bool Loaded             Init succeeded
//   +0x089  bool OpenedFile         this object opened the file (closes it)
//   +0x08C  AnimFileHeader Header   0x80 bytes
//   +0x10C  unsigned char ColorMap[0x400]   256 entries of 4 bytes
//   +0x50C  RGBClass Palette[256]
//   +0x80C  AnimLargePage Pages[256]        6 bytes each
//   +0xE0C  Surface *Frame          the decoded frame (320x200, owned)
//   +0xE10  unsigned char *PageData the current large page (0x10000, owned)
//   +0xE14  int CurrentFrame (-1)   +0xE18 int CurrentPage (-1)
//   size 0xE1C
#ifndef RA2_SHARED_ANIM_FILE_HPP
#define RA2_SHARED_ANIM_FILE_HPP

#include "shared/raw_file_class.hpp"
#include "shared/rgb_class.hpp"
#include "shared/surface.hpp"

// The base of the animation players: slot 0 is the (scalar deleting)
// destructor, the others are pure.
class Animate {
public:
    virtual ~Animate() {}                                               // 0x00424B90 slot 0
    virtual bool Open(FileClass *file) = 0;                             // slot 1
    virtual void Close() = 0;                                           // slot 2
    virtual void *Get_Frame(int frame) = 0;                             // slot 3
    virtual RGBClass *Get_Palette() = 0;                                // slot 4
    virtual int Get_Frame_Count() = 0;                                  // slot 5
    virtual int Get_Width() = 0;                                        // slot 6
    virtual int Get_Height() = 0;                                       // slot 7
};

// The "LPF " header (0x80 bytes at +0x8C).
struct AnimFileHeader {
    unsigned long ID;                       // +0x00 "LPF "
    unsigned short MaxPages;                // +0x04 (0x100)
    unsigned short PageCount;               // +0x06
    unsigned long RecordCount;              // +0x08
    unsigned short MaxRecordsPerPage;       // +0x0C
    unsigned short TableOffset;             // +0x0E (0x500)
    unsigned long ContentType;              // +0x10 "ANIM"
    unsigned short Width;                   // +0x14 (320)
    unsigned short Height;                  // +0x16 (200)
    unsigned char Variant;                  // +0x18
    unsigned char Version;                  // +0x19
    bool HasLastDelta;                      // +0x1A
    bool LastDeltaValid;                    // +0x1B
    unsigned char PixelType;                // +0x1C
    unsigned char CompressionType;          // +0x1D
    unsigned char OtherRecordsPerFrame;     // +0x1E
    unsigned char BitmapType;               // +0x1F
    unsigned char RecordTypes[32];          // +0x20
    long FrameCount;                        // +0x40
    unsigned short FramesPerSecond;         // +0x44
    unsigned char Reserved[0x80 - 0x46];
};

// A large page's table entry.
struct AnimLargePage {
    unsigned short FirstRecord;             // +0x00
    unsigned short RecordCount;             // +0x02
    unsigned short ByteCount;               // +0x04
};

class AnimFile : public Animate {
public:
    AnimFile();                                                         // 0x00423F90
    virtual ~AnimFile();                                                // 0x00424BC0 slot 0 (scalar deleting); body 0x00423FF0

    virtual bool Open(FileClass *file);                                 // 0x00424070 slot 1
    virtual void Close();                                               // 0x004240B0 slot 2
    virtual void *Get_Frame(int frame);                                 // 0x004243B0 slot 3
    virtual RGBClass *Get_Palette() { return Palette; }                 // 0x00424BB0 slot 4 (inline)
    virtual int Get_Frame_Count();                                      // 0x00424370 slot 5
    virtual int Get_Width();                                            // 0x00424390 slot 6
    virtual int Get_Height();                                           // 0x004243A0 slot 7

    bool Initialize();                                                  // 0x00424110 (reads the header; false when it is not an animation)
    bool Validate();                                                    // 0x004242B0
    int Page_Size(int page) const;                                      // 0x004246F0
    bool Load_Page(int page);                                           // 0x00424720
    int Find_Page(int frame) const;                                     // 0x004247A0
    void *Frame_Data(int frame);                                        // 0x004247F0
    int Frame_Size(int frame);                                          // 0x004248F0
    bool Decode_Frame(void *source, int size, void *dest, int destsize);   // 0x004249F0 (uncompressed or run/skip/dump body; returns whether it decoded)

    char Buffer[0x80];                      // +0x004
    FileClass *File;                        // +0x084
    bool Loaded;                            // +0x088
    bool OpenedFile;                        // +0x089
    char unknown_8a[2];
    AnimFileHeader Header;                  // +0x08C
    unsigned char ColorMap[0x400];          // +0x10C
    RGBClass Palette[256];                  // +0x50C
    AnimLargePage Pages[256];               // +0x80C
    Surface *Frame;                         // +0xE0C
    unsigned char *PageData;                // +0xE10
    int CurrentFrame;                       // +0xE14
    int CurrentPage;                        // +0xE18
};

#endif
