// The Westwood VQA player library (unit 0x00776380-0x0077EDCF: audio,
// buffer_, config, drawer, dstream, loader, task, timer and unvq, linked in
// that order). The library is built with __fastcall as its default calling
// convention; handlers and UnVQ drawers are __cdecl. Names and the layout
// follow the Tiberian Sun reconstruction of the same library
// (docs/WESTWOOD_SOURCES.md); offsets are verified on RA2's accesses.
// Field names marked unknown_ are not read by recovered code yet.
#ifndef RA2_SHARED_VQA_PLAYER_HPP
#define RA2_SHARED_VQA_PLAYER_HPP

class VQAClass;

// The public handle: the leading fields of VQAHandleP.
struct VQAHandle {
    unsigned short unknown_00;  // +0x00
    unsigned short Width;       // +0x02
    unsigned short Height;      // +0x04
    unsigned short unknown_06[3];
    unsigned short unknown_0C;  // +0x0C
    unsigned short unknown_0E;
    int Frames;                 // +0x10
    unsigned char unknown_14[0x98];
    VQAClass *Player;           // +0xAC the owner (callbacks; VQAConfig::Owner)
};

// Handler actions (stream handler VQACMD_*, memory handler VQAMEM_*).
enum {
    VQACMD_INIT = 1,
    VQACMD_CLEANUP = 2,
    VQACMD_OPEN = 3,
    VQACMD_CLOSE = 4,
    VQACMD_READ = 5,
    VQACMD_WRITE = 6,
    VQACMD_SEEK = 7,
    VQACMD_SEEKPEEK = 8,
    VQACMD_SIZE = 9
};
enum {
    VQAMEM_ALLOC = 2,
    VQAMEM_FREE = 3,
    VQAMEM_LOCK = 4,
    VQAMEM_UNLOCK = 5,
    VQAMEM_QUERYSIZE = 6
};

// The player configuration (0x88 bytes; VQAClass +0x170, VQAHandleP +0x40;
// defaults from VQA_DefaultConfig 0x00777850). The handler type is the one
// RA2's accepted callbacks 0x0071D490.. are declared with.
typedef int (__cdecl *VQACallback)(VQAHandle *handle, int action, int buffer, int size);
typedef unsigned long (__cdecl *VQA_TC_FUNC)(VQAHandle *vqa);
typedef int (__cdecl *VQADrawerCallback)(VQAHandle *vqa, int frame);
typedef int (__cdecl *VQACountCallback)(VQAHandle *vqa);
struct VQAConfig {
    VQACallback StreamHandler;      // +0x00 0x0071D490 or 0x0071D640 (VQAClass flag 1)
    VQACallback MemoryHandler;      // +0x04 0x0071D680
    VQACallback EventHandler;       // +0x08 0x0071D6E0
    VQADrawerCallback DrawerCallback; // +0x0C (0)
    VQA_TC_FUNC TimerCallback;      // +0x10 0x004122C0 or 0x00411420 (VQA option 4)
    VQACountCallback UnusedCallback; // +0x14 (a count VQA_Play tracks the deltas of)
    VQACallback AudioHandler;       // +0x18 0x004115A0 (VQAAUDIO_* actions)
    char *ImageBuf;                 // +0x1C
    int ImageWidth;                 // +0x20 (-1)
    int ImageHeight;                // +0x24 (-1)
    int X1;                         // +0x28
    int Y1;                         // +0x2C
    int FrameRate;                  // +0x30 (constructor argument 6)
    int DrawRate;                   // +0x34 (constructor argument 7)
    int RefreshRate;                // +0x38 (60)
    int unknown_3c;
    int DrawFlags;                  // +0x40 bits 0x01, 0x04, 0x40, 0x80 from VQA options 15, 1, 10, 12
    int OptionFlags;                // +0x44 bits 0x01, 0x04, 0x08, 0x20, 0x100
    int NumFrameBufs;               // +0x48 (1 or 14)
    int NumCBBufs;                  // +0x4C (-1)
    int unknown_50;
    void *AudioBuf;                 // +0x54
    int AudioBufSize;               // +0x58
    int HMIBufSize;                 // +0x5C (0x2000)
    int AudioRate;                  // +0x60
    int Volume;                     // +0x64 (VQAClass::Unknown_0071CBC0)
    int unknown_68;
    VQAClass *Owner;                // +0x6C
    int InitialLoopID;              // +0x70
    int InitialLoopIterations;      // +0x74
    int StreamFileHandle;           // +0x78
    int unknown_7c;
    int unknown_80;
    int LatencyAdjustment;          // +0x84 (low 16 bits of 0x00A40B54)
};

#pragma pack(push, 1)

// The movie header (VQHD chunk, 0x2A bytes).
struct VQAHeader {
    unsigned short Version;         // +0x00
    unsigned short Flags;           // +0x02
    unsigned short Frames;          // +0x04
    unsigned short ImageWidth;      // +0x06
    unsigned short ImageHeight;     // +0x08
    unsigned char BlockWidth;       // +0x0A
    unsigned char BlockHeight;      // +0x0B
    unsigned char FPS;              // +0x0C
    unsigned char Groupsize;        // +0x0D
    unsigned short Num1Colors;      // +0x0E
    unsigned short CBentries;       // +0x10
    unsigned short Xpos;            // +0x12
    unsigned short Ypos;            // +0x14
    unsigned short MaxFramesize;    // +0x16
    unsigned short SampleRate;      // +0x18
    unsigned char Channels;         // +0x1A
    unsigned char BitsPerSample;    // +0x1B
    unsigned short AltSampleRate;   // +0x1C
    unsigned char AltChannels;      // +0x1E
    unsigned char AltBitsPerSample; // +0x1F
    unsigned char ColorMode;        // +0x20
    unsigned char Pad;              // +0x21
    unsigned long MaxCBSize;        // +0x22
    unsigned long AudioPreload;     // +0x26
};

struct VQAChunkHeader {
    unsigned long ID;
    unsigned long Size;
};

struct VQACBNode {                  // 0x18 bytes
    unsigned char *Buffer;
    VQACBNode *Next;
    VQACBNode *Prev;
    unsigned long Flags;
    unsigned long CBOffset;
    int CodebookSize;
};

struct VQAFrameNode {               // 0x2C bytes
    unsigned char *Pointers;
    VQACBNode *Codebook;
    unsigned char *Palette;
    VQAFrameNode *Next;
    VQAFrameNode *Prev;
    unsigned long Flags;
    unsigned long PrevFlags;
    long FrameNum;
    long PtrOffset;
    long PalOffset;
    long PaletteSize;
};

struct VQALoader {                  // 0x3C bytes
    VQACBNode *CurCB;
    VQACBNode *FullCB;
    VQACBNode *PrevCB;
    VQAFrameNode *CurFrame;
    long NumPartialCB;
    long PartialCBSize;
    int CBSize;
    long CurFrameNum;
    long LastFrameNum;
    long WaitsOnDrawer;
    long WaitsOnAudio;
    long FrameSize;
    long MaxFrameSize;
    VQAChunkHeader CurChunkHdr;
};

struct VQADrawer {                  // 0x53C bytes
    VQAFrameNode *CurFrame;
    unsigned long Flags;
    unsigned char *ImageBuf;
    long ImageWidth;
    long ImageHeight;
    long X1;
    long Y1;
    long ScreenOffset;
    long CurPalSize;
    unsigned char Palette_24[768];
    unsigned char Palette_15[512];
    long BlocksPerRow;
    long NumRows;
    long NumBlocks;
    long LastFrameNum;
    long DesiredFrame;
    long WaitsOnLoader;
};

struct VQAFlipper {
    VQAFrameNode *CurFrame;
    long LastFrameNum;
};

struct VQALoopCache {               // 0x20 bytes
    char *Ptr;
    int Size;
    char *Buffer;
    int Bytes;
    int Offset;
    int Min;
    int Max;
    int ID;
};

// Chunk-indexed tables: LINF loops, PINF palette frames, CINF codebooks.
struct VQAInfoHeader {              // 8 bytes
    unsigned short Count;
    unsigned long Flags;
    unsigned short Pad;
};
struct VQALoopInfo {
    struct DATA {
        unsigned short StartFrame;
        unsigned short EndFrame;
    };
    VQAInfoHeader Header;
    DATA *Data;
};
struct VQAPaletteInfo {
    struct DATA {
        unsigned short Frame;
    };
    VQAInfoHeader Header;
    DATA *Data;
};
struct VQACodebookInfo {
    struct HEADER {
        unsigned short Count;
        unsigned short Groupsize;
        unsigned short Flags;
        unsigned short Pad;
    };
    struct DATA {                   // 6 bytes
        unsigned short Frame;
        int Size;
    };
    HEADER Header;
    DATA *Data;
};

// Per-chunk data caches of the MFCI/MSCI tables.
struct VQAChunkCache {              // 12 bytes
    struct DATA {
        char *Buffer;
        unsigned long Size;
        long Frame;
    };
    unsigned long Count;
    int WriteIndex;
    DATA *Data;
};
struct VQAMFCInfo {                 // 0x1C bytes
    struct HEADER {
        unsigned long StaticCount;
        unsigned long Count;
        int unknown_08;
        int unknown_0c;
    };
    struct DATA {                   // 0x18 bytes
        int KeyFrame;
        unsigned long ChunkID;
        char Pad[0x10];
    };
    struct TABLE {                  // 0x10 bytes
        unsigned long ChunkID;
        int FrameInterval;
        int EntrySize;
        int unknown_0c;
    };
    HEADER Header;
    DATA *StaticData;
    TABLE *Table;
    VQAChunkCache *Data2;
};
struct VQAMSCInfo {                 // 0x10 bytes
    struct HEADER {
        unsigned long Count;
        int unknown_04;
    };
    struct TABLE {                  // 0x10 bytes
        unsigned long ChunkID;
        int EntrySize;
        int unknown_08;
        int unknown_0c;
    };
    HEADER Header;
    TABLE *Table;
    VQAChunkCache *Data2;
};

struct VQASOS {                     // 12 bytes
    long Predicted;
    short Index;
    long Predicted2;
    short Index2;
};

struct VQAAudio {                   // 0x50 bytes
    unsigned char *Buffer;
    unsigned long AudBufPos;
    bool *IsLoaded;
    short *BlockRepeats;
    unsigned long NumAudBlocks;
    unsigned long Block1;
    unsigned long Block2;
    unsigned char *TempBuf;
    unsigned long BufferOffset;
    unsigned long TempBufLen;
    unsigned long TempBufSize;
    void *HMIBuffer;
    unsigned long Flags;
    unsigned long PlayPosition;
    unsigned long BufferPosition;
    int unknown_3c;
    unsigned long BytesPerSec;
    VQASOS ADPCM_Info;
};

typedef void (__cdecl *UNVQ_FUNC)(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
                                  unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth);
typedef long (__fastcall *VQAD_FUNC)(VQAHandle *vqa);
typedef long (__fastcall *VQAP_FUNC)(VQAHandle *vqa);

// Audio handler actions and VQAAudio::Flags bits.
enum {
    VQAAUDIO_INIT = 1,
    VQAAUDIO_OPEN = 2,
    VQAAUDIO_CLOSE = 3,
    VQAAUDIO_START = 4,
    VQAAUDIO_PAUSE = 6,
    VQAAUDIO_STOP = 7
};
enum {
    VQAAUDF_ISPLAYING = 1 << 6,
    VQAAUDF_ISREPEATING = 1 << 7,
    VQAAUDF_ISENDOFFILE = 1 << 8,
    VQAAUDF_ISDONE = 1 << 9,
    VQAAUDF_ISSTARVED = 1 << 10,
    VQAAUDF_MEMLOCKED = 1 << 30,
    VQAAUDF_MODLOCKED = 1 << 31
};

// AltBufferFlags bits.
enum {
    VQAABUFF_ALTCB = 1 << 0,
    VQAABUFF_ALTPTR = 1 << 1,
    VQAABUFF_ALTLOOP = 1 << 2
};

// VQAHandleP::Flags, VQAConfig::DrawFlags/OptionFlags, VQAHeader::Flags,
// VQADrawer::Flags, VQAFrameNode::Flags and VQACBNode::Flags bits.
enum {
    VQADATF_DDONE = 1 << 1,
    VQADATF_LDONE = 1 << 2,
    VQADATF_PRIMED = 1 << 3,
    VQADATF_BUFCONFIG = 1 << 4,
    VQADATF_ALTIMG = 1 << 5,
    VQADATF_PAUSED = 1 << 6,
    VQADATF_LOOPED = 1 << 7,
    VQADATF_LOOPJMP = 1 << 8,
    VQADATF_AUDIOSYNC = 1 << 9,
    VQADATF_REFILLED = 1 << 10,
    VQADATF_FRAMESTALL = 1 << 11
};
enum {
    VQACFGF_BUFFER = 1 << 0,
    VQACFGF_NODRAW = 1 << 1,
    VQACFGF_NOSKIP = 1 << 2,
    VQACFGF_OFFSET = 1 << 3,
    VQACFGF_ORIGIN = 3 << 4,
    VQACFGF_TOPLEFT = 0 << 4,
    VQACFGF_TOPRIGHT = 1 << 4,
    VQACFGF_BOTRIGHT = 2 << 4,
    VQACFGF_BOTLEFT = 3 << 4,
    VQACFGF_HALFSIZE = 1 << 6,
    VQACFGF_NOTRANS = 1 << 7
};
enum {
    VQAOPTF_AUDIO = 1 << 0,
    VQAOPTF_STEP = 1 << 1,
    VQAOPTF_LOOPS = 1 << 5,
    VQAOPTF_ALTAUDIO = 1 << 6,
    VQAOPTF_LOOPCACHE = 1 << 8,
    VQAOPTF_WAITFILL = 1 << 9
};
enum {
    VQAHDF_AUDIO = 1 << 0,
    VQAHDF_ALTAUDIO = 1 << 1,
    VQAHDF_TRANS = 1 << 2,
    VQAHDF_SNDJUMP = 1 << 3
};
enum {
    VQADRWF_SETPAL = 1 << 0,
    VQADRWF_STEP = 1 << 1,
    VQADRWF_REPAINT = 1 << 2,
    VQADRWF_HOLD = 1 << 3,
    VQADRWF_FORCEDRAW = 1 << 4
};
enum {
    VQAFRMF_LOADED = 1 << 0,
    VQAFRMF_KEY = 1 << 1,
    VQAFRMF_PALETTE = 1 << 2,
    VQAFRMF_PALCOMP = 1 << 3,
    VQAFRMF_PTRCOMP = 1 << 4,
    VQAFRMF_RSDCOMP = 1 << 5,
    VQAFRMF_ALTPTR = 1 << 6,
    VQAFRMF_HOLD = 1 << 7,
    VQAFRMF_LOOPED = 1 << 8,
    VQAFRMF_LOOPJMP = 1 << 9,
    VQAFRMF_CHUNKS = 1 << 10,
    VQAFRMF_11 = 1 << 11
};

// FINF frame offset table entries: word offset (in 2-byte units) and flags.
#define VQAFINF_KEY (1L << 31)
#define VQAFINF_PAL (1L << 30)
#define VQAFINF_OFFSET 0x0FFFFFFFL
#define VQAFRAME_OFFSET(a) (((a) & VQAFINF_OFFSET) << 1)

// VQA_Play modes and flags; loop modes.
enum {
    VQAMODE_RUN = 0,
    VQAMODE_WALK = 1,
    VQAMODE_PAUSE = 2,
    VQAMODE_STOP = 3
};
enum {
    VQAPLAYF_STEP = 1 << 0,
    VQAPLAYF_REPAINT = 1 << 1
};
enum {
    VQALOOP_NORMAL = 0,
    VQALOOP_JUMP = 1,
    VQALOOP_2 = 2,
    VQALOOP_3 = 3
};
enum {
    VQACBF_CBCOMP = 1 << 1,
    VQACBF_ALTPTR = 1 << 2,
    VQACBF_CBFULL = 1 << 3
};

// Event handler actions.
enum {
    VQAEVENT_PALETTE = 2,
    VQAEVENT_CODEBOOK = 3,
    VQAEVENT_LOOPED = 4,
    VQAEVENT_LOOPJUMP = 5,
    VQAEVENT_LOCK = 6,
    VQAEVENT_UNLOCK = 7
};

// Block dimensions as BLOCK_DIM(width, height).
#define BLOCK_DIM(a, b) ((((a) & 0xFF) << 8) | ((b) & 0xFF))
#define BLOCK_4X2 BLOCK_DIM(4, 2)
#define BLOCK_4X4 BLOCK_DIM(4, 4)

// Ticks per second of the movie clock.
#define VQA_TIMETICKS 60

// The private handle (0x7DC bytes, allocated by VQA_Open 0x0077B7A0).
struct VQAHandleP {
    unsigned short Version;         // +0x000
    unsigned short ImageWidth;      // +0x002
    unsigned short ImageHeight;     // +0x004
    short unknown_006;
    void *ImageBuf;                 // +0x008
    unsigned short ColorMode;       // +0x00C
    unsigned short FrameRate;       // +0x00E
    long NumFrames;                 // +0x010
    int LoadedFrames;               // +0x014
    int DrawnFrames;                // +0x018
    int SkippedFrames;              // +0x01C
    int StartTime;                  // +0x020
    int EndTime;                    // +0x024
    int LastCallbackCount;          // +0x028
    int MaxCallbackDelta;           // +0x02C
    int MemUsed;                    // +0x030
    int AudioHandleIndex;           // +0x034
    int RepeatedBuffers;            // +0x038
    unsigned short SampleRate;      // +0x03C
    unsigned char Channels;         // +0x03E
    unsigned char BitsPerSample;    // +0x03F
    VQAConfig Config;               // +0x040
    char Filename[32];              // +0x0C8
    VQAHeader Header;               // +0x0E8
    unsigned long ClipWidth;        // +0x112
    unsigned long ClipHeight;       // +0x116
    short unknown_11a;
    int StopFrame;                  // +0x11C
    int LoopID;                     // +0x120
    int LoopIterations;             // +0x124
    int LoopStartFrame0;            // +0x128
    int LoopEndFrameMode2;          // +0x12C
    int LoopEndFrameJump;           // +0x130
    int LoopIterationsJump;         // +0x134
    int LoopEndFrameNormal;         // +0x138
    int LoopStartFrame1;            // +0x13C
    int LoopEndFrame2;              // +0x140
    int LoopStartFrame2;            // +0x144
    int TickOffset;                 // +0x148
    int unknown_14c;
    unsigned long Flags;            // +0x150
    unsigned long AltBufferFlags;   // +0x154
    void *AltImageBuf;              // +0x158
    int AltImageWidth;              // +0x15C
    int AltImageHeight;             // +0x160
    VQALoader Loader;               // +0x164
    VQADrawer Drawer;               // +0x1A0
    VQAFlipper Flipper;             // +0x6DC
    VQAFrameNode *FrameData;        // +0x6E4
    void *AltPtrBuffer;             // +0x6E8
    VQACBNode *CBData;              // +0x6EC
    void *AltCBBuffer;              // +0x6F0
    VQALoopCache LoopCache;         // +0x6F4
    VQALoopInfo LoopInfo;           // +0x714
    VQAMFCInfo MFCInfo;             // +0x720
    VQAMSCInfo MSCInfo;             // +0x73C
    VQACodebookInfo CodebookInfo;   // +0x74C
    VQAPaletteInfo PaletteInfo;     // +0x758
    long *Foff;                     // +0x764
    long Max_CB_Size;               // +0x768
    long Max_Ptr_Size;              // +0x76C
    long Max_Pal_Size;              // +0x770
    int CBBufferSize;               // +0x774
    int PtrBufferSize;              // +0x778
    VQAD_FUNC Draw_Frame;           // +0x77C
    VQAP_FUNC Page_Flip;            // +0x780
    UNVQ_FUNC UnVQ1;                // +0x784
    UNVQ_FUNC UnVQ2;                // +0x788
    VQAAudio Audio;                 // +0x78C
};

#pragma pack(pop)

// VQAHeader::Version of the first file format.
#define VQAHD_VER1 1

// Rounds a chunk size up to an even byte count (IFF padding).
#define PADSIZE(size) (((size) + 1) & ~1)

// audio.cpp
long __fastcall VQA_OpenAudio(VQAHandleP *vqap);                                      // 0x00776380
void __fastcall VQA_CloseAudio(VQAHandleP *vqap);                                     // 0x00776420
void __fastcall VQA_StartAudio(VQAHandleP *vqap);                                     // 0x00776480
void __fastcall VQA_PauseAudio(VQAHandleP *vqap);                                     // 0x007764A0
void __fastcall VQA_StopAudio(VQAHandleP *vqap);                                      // 0x007764C0
long __fastcall CopyAudio(VQAHandleP *vqap);                                          // 0x007764E0
int __cdecl VQA_AudioFillCallback(VQAHandleP *vqap);                                  // 0x00776680
int __cdecl VQA_AudioDoneCallback(VQAHandleP *vqap, int buffer);                      // 0x007767D0

// buffer_.cpp
long __fastcall AllocBuffers(VQAHandleP *vqap);                                       // 0x007768A0
void __fastcall FreeBuffers(VQAHandleP *vqap);                                        // 0x00777190
long __fastcall VQA_Configure_Buffer(VQAHandleP *vqap);                               // 0x007776B0
int __cdecl VQA_Memory_Handler(VQAHandle *vqa, int action, int buffer, int nbytes);    // 0x007777E0

// drawer.cpp
long __fastcall VQA_ResetLastFrameNum(VQAHandle *vqa);                                 // 0x00777870
long __fastcall VQA_Configure_Drawer(VQAHandleP *vqap);                                // 0x00777880
void __fastcall VQA_DispatchFrameChunks(VQAHandleP *vqap, long frame);                 // 0x00777A40
void __fastcall VQA_UnVQFrame(VQAHandleP *vqap, VQAFrameNode *frame);                  // 0x00777B50
long __fastcall DrawFrame_MCGA(VQAHandle *vqa);                                        // 0x00777C50
long __fastcall Select_Frame(VQAHandleP *vqap);                                        // 0x00777C90
long __fastcall VQA_ComputeDesiredFrame(VQAHandleP *vqap, VQAConfig *config, VQADrawer *drawer,
                                        VQAFrameNode *frame, unsigned long time);      // 0x00778030
void __fastcall Prepare_Frame(VQAHandleP *vqap);                                       // 0x007781F0
long __fastcall PageFlip_MCGA(VQAHandle *vqa);                                         // 0x007782C0
long __fastcall DrawFrame_MCGABuf(VQAHandle *vqa);                                     // 0x00778350
long __fastcall PageFlip_MCGABuf(VQAHandle *vqa);                                      // 0x007783A0
void __cdecl UnVQ_Nop(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
                      unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth);  // 0x00778430
long __fastcall PageFlip_Nop(VQAHandle *vqa);                                          // 0x00778440

// dstream.cpp
int __cdecl Disk_VQA_Stream_Handler(VQAHandle *vqa, int action, int buffer, int nbytes);    // 0x00778450
int __cdecl Memory_VQA_Stream_Handler(VQAHandle *vqa, int action, int buffer, int nbytes);  // 0x007785B0

// unvq.cpp (C drawers) and the handwritten assembly decoders.
#define UNVQ_DECL(name) void __cdecl name(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer, \
                                          unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth)
UNVQ_DECL(UnVQ2_C1_4x4);              // 0x0077CBD0
UNVQ_DECL(UnVQ1_C4_4x4);              // 0x0077CF70
UNVQ_DECL(UnVQ2_C4_4x4);              // 0x0077D0C0
UNVQ_DECL(UnVQ1_C4_4x2);              // 0x0077D470
UNVQ_DECL(UnVQ2_C4_4x2);              // 0x0077D5B0
UNVQ_DECL(UnVQ2_C0_4x4_TRANS);        // 0x0077D940
UNVQ_DECL(UnVQ2_C0_4x4_KEY);          // 0x0077DD90
UNVQ_DECL(UnVQ2_C0_4x4_TRANS_HALF);   // 0x0077E1A0
UNVQ_DECL(UnVQ2_C0_4x2_TRANS);        // 0x0077E5B0
UNVQ_DECL(UnVQ2_C0_4x2_KEY);          // 0x0077E9E0
extern "C" {
UNVQ_DECL(ASM_UnVQ_4x2);              // 0x0077FF50
UNVQ_DECL(ASM_UnVQ_4x4);              // 0x0077FFE6
UNVQ_DECL(ASM_UnVQ_4x4_HALF);         // 0x007800A4
UNVQ_DECL(ASM_UnVQ1_C1_4x4);          // 0x007801D8
}
#undef UNVQ_DECL

// task.cpp (entry points VQAClass calls keep their VQA_Unknown_ names below)
int __fastcall VQA_GetLoopCount(VQAHandleP *vqap);                                     // 0x0077C7C0
void __fastcall VQA_ResetCache(VQAHandleP *vqap);                                      // 0x0077C880
char *__fastcall VQA_Version();                                                        // 0x0077C8D0
int __fastcall VQA_GetClipping(VQAHandleP *vqap, int &clipw, long &cliph);             // 0x0077C8E0
char *__fastcall VQA_IDString();                                                       // 0x0077C950
long __fastcall User_Update(VQAHandle *vqa);                                           // 0x0077C960
long __fastcall VQA_NumFramesWithPalettes(VQAHandleP *vqap);                           // 0x0077CA30
int __fastcall VQA_GetXYPos(VQAHandleP *vqap, int &x, long &y);                        // 0x0077CA50
long __fastcall VQA_LargestLoop(VQAHandleP *vqap, long streamsize);                    // 0x0077CA70

// The game's audio lock release the player calls when it closes (TS name; game code).
int Lock_Audio_Handler();                                                              // 0x00412370
int Unlock_Audio_Handler();                                                            // 0x00412380
extern "C" void __cdecl VQA_sosCODECInitStream(VQASOS *info);                          // 0x00780560 (asm)

// config.cpp, timer.cpp
void __fastcall VQA_SetTimer(VQAHandleP *vqap, long time);                             // 0x0077CB20
void __fastcall VQA_StepTimer(VQAHandleP *vqap, long step);                            // 0x0077CB60
unsigned long __fastcall VQA_GetTime(VQAHandleP *vqap);                                // 0x0077CB70

// ZAP audio frame header (SND1 chunks).
struct ZAPHeader {
    unsigned short UnCompSize;
    unsigned short CompSize;
};

// Handwritten assembly helpers of the library (vqa_uncomp.asm, vqa_sos.asm).
extern "C" long __cdecl AudioUnzap(void *source, void *dest, long size);                                // 0x00781130
extern "C" unsigned long __cdecl VQA_LCW_Uncompress(char const *source, char *dest, unsigned long length); // 0x007813EB
extern "C" void __cdecl VQA_sosCODECDecompressData(void *source, void *dest, unsigned short bits,
                                                   unsigned short channels, unsigned long size, VQASOS *info); // 0x00780581

// loader.cpp
long __fastcall VQA_LoadFrame(VQAHandleP *vqap, long flags);                                          // 0x00778680
long __fastcall VQA_LoadFrame_Internal(VQAHandleP *vqap, long flags);                                 // 0x00778950
long __fastcall PrimeBuffers(VQAHandleP *vqap);                                                       // 0x007796A0
bool __fastcall VQA_IsFrameStartOfLoop(VQAHandleP *vqap, long framenum);                              // 0x007796F0
long __fastcall VQA_ReloadPalette(VQAHandleP *vqap, long framenum, int force);                        // 0x00779740
long __fastcall VQA_SeekGroup(VQAHandleP *vqap, long framenum, long groupsize, bool preloadaudio,
                              bool reset_state, bool &skipcodebook);                                  // 0x00779950
long __fastcall VQA_GetPaletteFrameRange(VQAHandleP *vqap, long framenum, long *first_frame, long *last_frame); // 0x007798C0
long __fastcall Load_CLIP(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077A340
long __fastcall Load_LINF(VQAHandleP *vqap);                                                          // 0x0077A360
long __fastcall Load_MFCI(VQAHandleP *vqap);                                                          // 0x0077A4C0
long __fastcall Load_MSCI(VQAHandleP *vqap);                                                          // 0x0077A940
long __fastcall VQA_GetCodebookFrameRange(VQAHandleP *vqap, long framenum, long *first_frame, long *last_frame); // 0x0077AC00
long __fastcall Load_CINF(VQAHandleP *vqap);                                                          // 0x0077AC80
long __fastcall Load_PINF(VQAHandleP *vqap);                                                          // 0x0077ADF0
long __fastcall Load_FINF(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077AF50
long __fastcall Load_CBFZ(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077AFA0
long __fastcall Load_CBP0(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077B020
long __fastcall Load_CBPZ(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077B140
long __fastcall Load_CPLZ(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077B2C0
long __fastcall Load_SND0(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077B390
long __fastcall Load_SND1(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077B460
long __fastcall Load_SND2(VQAHandleP *vqap, unsigned long iffsize);                                   // 0x0077B620

// Library entry points called by VQAClass (names from the call sites; TS names in comments).
void __fastcall VQA_Unknown_00777850(VQAConfig *config);                                         // defaults
int __fastcall VQA_Unknown_0077B7A0(char const *filename, VQAConfig *config, VQAHandle **handle);   // VQA_Open
int __fastcall VQA_Unknown_0077C640(VQAHandle *handle, int id, int iterations, int mode);         // VQA_SetLoop
int __fastcall VQA_Unknown_0077C6C0(VQAHandle *handle, int start, int end, int iterations, int mode);  // VQA_SetLoop_Internal
int __fastcall VQA_Unknown_0077C2E0(VQAHandle *handle, int frame, int fromwhere);               // VQA_SeekFrame
int __fastcall VQA_Unknown_0077BF10(VQAHandle *handle, int mode, int flags);                    // VQA_Play
void __fastcall VQA_Unknown_0077BE70(VQAHandle *handle);                                         // stop
void __fastcall VQA_Unknown_0077C7D0(VQAHandle *handle);
int __fastcall VQA_Unknown_0077C480(VQAHandle *handle, int buffer, int width, int height, int x, int y);  // VQA_Set_DrawBuffer
int __fastcall VQA_Unknown_0077C8A0(VQAHandle *handle, int frames);
int __fastcall VQA_Unknown_0077C920(VQAHandle *handle, int *blockw, int *blockh, int *clrmode);  // VQA_GetBlockInfo
int __fastcall VQA_Unknown_0077C440(VQAHandle *handle, void (*unvq1)(), void (*unvq2)());       // VQA_SetUnVQ
int __fastcall VQA_Unknown_0077CBA0(VQAHandle *handle);                                         // VQA_GetMovieTime
void VQA_Unknown_0077FD80();
void VQA_Unknown_0077FE89();

#endif
