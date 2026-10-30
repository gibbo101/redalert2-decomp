// Movie playback (unit 0x005A1470-0x005A1FBF): the VQA movie wrapper used
// by the free play/close functions, and the MovieHandle interface with its
// VQA and Bink implementations (RTTI names MovieHandle 0x007A6654,
// VQMovieHandle 0x007A6624, BinkMovieHandle 0x007A6684).
//
// The VQA player (0x0071Cxxx) and the Bink wrapper (0x0042FEE0-0x00430820)
// are outside this unit; their members are named after their addresses.
// Names of slots, fields and free functions are hypotheses from use.
#ifndef RA2_SHARED_MOVIE_HPP
#define RA2_SHARED_MOVIE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/surface.hpp"
#include "shared/win32_window.hpp"
#include "shared/bink.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/vqa_player.hpp"

// The VQA option bits (a bit vector at 0x00AF9020; 18 options, option 6 set
// by default). Index meanings are unknown.
extern unsigned char unknown_vqa_options_af9020[3];
void __fastcall VQA_Unknown_0071DB20();                    // 0x0071DB20 defaults
void __fastcall VQA_Unknown_0071DB60(int option);          // 0x0071DB60 set
void __fastcall VQA_Unknown_0071DB80(int option);          // 0x0071DB80 clear
bool __fastcall VQA_Unknown_0071DBA0(int option);          // 0x0071DBA0 test
int __fastcall VQA_Unknown_0071DBC0(int option);           // 0x0071DBC0 toggle; 1 when now set

// Owned by the VQA movie at +0x48 (class unknown).
class VQAMovieCompanion {
public:
    ~VQAMovieCompanion();                                  // 0x0069B2A0
    void Unknown_0069B4F0(int unknown);                    // 0x0069B4F0
    void Unknown_0069B4E0();                               // 0x0069B4E0
    bool Unknown_0069B420(int time);                       // 0x0069B420 (Bink frame * interval)

    int unknown_00;          // +0x00 nonzero: active
    int unknown_04[3];       // +0x04
    Surface *unknown_10;     // +0x10 picture drawn over the movie
    Rect unknown_14;         // +0x14 its source area
    Rect unknown_24;         // +0x24 area cleared before a frame
};

// The VQA player library (0x0077xxxx, __fastcall; shared/vqa_player.hpp).
// Results are VQA error codes (-1 none).
extern int unknown_int_a40b54;                              // 0x00A40B54 (low 16 bits: VQAConfig +0x84)
void __fastcall VQA_Unknown_0070B7F0(int unknown1, unsigned unknown2);
void __fastcall VQA_Unknown_0070B690(int unknown1);
void VQA_Unknown_0070B820();
void VQA_Unknown_0070BBC0();
void VQA_Unknown_0070BF60();
void VQA_Unknown_0070C0A0();
extern bool unknown_vqa_paused_af901c;                     // 0x00AF901C the pause was reported
// Window message helpers (0x00522E90/0x00522ED0, the game's GetMessage /
// PeekMessage wrappers; __fastcall) and the message counter 0x00A52298.
// MSG: shared/win32_api.hpp.
WIN32_IMPORT BOOL WINAPI TranslateMessage(MSG const *message);
WIN32_IMPORT LRESULT WINAPI DispatchMessageA(MSG const *message);
BOOL __fastcall unknown_peek_message_522ed0(MSG *message, HWND window, UINT first, UINT last, UINT remove);
BOOL __fastcall unknown_get_message_522e90(MSG *message, HWND window, UINT first, UINT last);
extern int unknown_message_count_a52298;
bool VQA_Unknown_0071C590();                                // 0x0071C590 one window message

// Player callbacks given to the VQA library through the configuration.
int __cdecl VQA_Unknown_0071D490(VQAHandle *handle, int unknown2, int unknown3, int unknown4);
int __cdecl VQA_Unknown_0071D640(VQAHandle *handle, int unknown2, int unknown3, int unknown4);
int __fastcall VQA_Unknown_0071D660(VQAHandle *handle, int unknown2, int unknown3, int unknown4);
int __cdecl VQA_Unknown_0071D680(VQAHandle *handle, int request, int unknown3, int unknown4);
int __cdecl VQA_Unknown_0071D6E0(VQAHandle *handle, int event, int unknown3, int unknown4);

// The VQA player object (VQA unit 0x0071C320-0x0071DC0F; class name
// unknown, 0x54C bytes from the constructor's stores).
class VQAClass {
public:
    VQAClass(char const *filename, int flags, int (*callback538)(), void (*callback53c)(), void (*callback540)(),
             int unknown6, int unknown7);                  // 0x0071C5F0
    ~VQAClass();                                           // 0x0071C8A0
    void Unknown_0070B7D0();                               // 0x0070B7D0 (releases the player)
    bool Unknown_0071CB30();                               // 0x0071CB30 opens the movie
    int Unknown_0071CBA0();                                // 0x0071CBA0
    int Unknown_0071CBC0(int value);                       // 0x0071CBC0 old value; -1 keeps it
    bool Unknown_0071CBE0(int unknown1, int unknown2);     // 0x0071CBE0
    bool Unknown_0071CC10(int unknown1, int unknown2, int unknown3);  // 0x0071CC10
    void Unknown_0071CC60(int frame);                      // 0x0071CC60 seek to a frame (no value: the same-frame path leaves EAX unset)
    bool Unknown_0071CC90();                               // 0x0071CC90
    int Unknown_0071CCD0(int frame, bool unknown);         // 0x0071CCD0 play loop (1: stopped by Escape)
    void Unknown_0071CF50(int frame);                      // 0x0071CF50 shows a frame (-1: the last)
    bool Unknown_0071CFC0(bool *unknown);                  // 0x0071CFC0
    void Unknown_0071D1A0();                               // 0x0071D1A0 (pause)
    void Unknown_0071D1E0();                               // 0x0071D1E0 (resume)
    void Unknown_0071D1F0();                               // 0x0071D1F0 (stop)
    void Unknown_0071D210();                               // 0x0071D210
    int Unknown_0071D230();                                // 0x0071D230
    bool Unknown_0071D240(int unknown1, int x, int y, int width, int height);   // 0x0071D240
    void Unknown_0071D2B0(int value);                      // 0x0071D2B0
    void Unknown_0071D2C0(int unknown1, unsigned unknown2);   // 0x0071D2C0
    int Unknown_0071D300();                                // 0x0071D300 (width)
    int Unknown_0071D310();                                // 0x0071D310 (height)
    int Unknown_0071D320();                                // 0x0071D320 callback +0x538
    void Unknown_0071D330();                               // 0x0071D330 callback +0x53C
    // Stream callbacks for the VQA library: request 3 open, 4 close,
    // 5 read, 6 (unsupported), 7 seek, 8 checked skip, 9 size; nonzero
    // results are errors. 0x0071CA00 reads the movie from Buffer,
    // 0x0071D340 from the file, 0x0071D4B0 from inside a mixfile.
    int Unknown_0071C8D0(unsigned size);                   // 0x0071C8D0 reads the file into Buffer (VQA error codes)
    int Unknown_0071CA00(int request, int unknown2, int unknown3);   // 0x0071CA00
    int Unknown_0071D340(int request, int unknown2, int unknown3);   // 0x0071D340
    int Unknown_0071D4B0(int request, int unknown2, int unknown3);   // 0x0071D4B0
    void Unknown_0071CAF0(unsigned char const *palette);  // 0x0071CAF0 copies the 768-byte palette
    void Unknown_0071CB20();                               // 0x0071CB20 applies the palette
    int Unknown_0071D790();                                // 0x0071D790 (returns 0)
    void Unknown_0071D7A0();                               // 0x0071D7A0 (empty)
    void Unknown_0071D7B0();                               // 0x0071D7B0 (empty)

    VQAMovieCompanion *Companion;          // +0x000
    CCFileClass File;                      // +0x004
    bool FileOpen;                         // +0x068
    char Filename[0x107];                  // +0x069
    VQAConfig Config;                      // +0x170 VQA configuration (0x88 bytes)
    VQAHandle *Handle;                     // +0x1F8
    unsigned char Palette[0x300];          // +0x1FC current movie palette (PaletteClass layout)
    int CurrentFrame;                      // +0x4FC
    int FrameCount;                        // +0x500
    int unknown_504;                       // +0x504
    int unknown_508;                       // +0x508 (-1)
    bool Opened;                           // +0x50C
    int Width;                             // +0x510
    int Height;                            // +0x514
    int unknown_518;                       // +0x518
    int unknown_51c;                       // +0x51C
    bool PaletteChanged;                   // +0x520
    int Flags;                             // +0x524
    unsigned FileSize;                     // +0x528
    unsigned Position;                     // +0x52C
    int unknown_530;                       // +0x530
    unsigned char *Buffer;                 // +0x534
    int (*Callback538)();                  // +0x538
    void (*Callback53C)();                 // +0x53C
    void (*Callback540)();                 // +0x540 called after each frame
    int unknown_544;                       // +0x544
    bool unknown_548;                      // +0x548 paused
    bool unknown_549;                      // +0x549
};

// The VQA movie wrapper (0x4C bytes).
class VQAMovie {
public:
    VQAMovie();                                            // 0x005A1710
    ~VQAMovie();                                           // 0x005A1760

    VQAClass *Player;        // +0x00
    int unknown_04;          // +0x04 (-1)
    Surface *FrameSurface;   // +0x08 decoded frames
    int Mode;                // +0x0C (1 and 2 select loop behaviour)
    int unknown_10;          // +0x10
    int unknown_14;          // +0x14 (negative: none)
    int unknown_18;          // +0x18
    int Repeats;             // +0x1C (1; negative: forever)
    int unknown_20;          // +0x20
    Rect Source;             // +0x24
    Rect Dest;               // +0x34 (client coordinates)
    bool unknown_44;         // +0x44
    bool Playing;            // +0x45
    VQAMovieCompanion *Companion;  // +0x48
};

extern VQAMovie *CurrentVQAMovie;                          // 0x00A710AC

void __fastcall VQA_Movie_Close(VQAMovie *movie);                                     // 0x005A1470
void __fastcall VQA_Movie_Play(VQAMovie *movie, bool hide, int theme, bool unknown);  // 0x005A14D0
bool __fastcall VQA_Movie_Unknown_005A15F0(VQAMovie *movie, bool *unknown);          // 0x005A15F0
bool __fastcall VQA_Movie_Is_Playing();                                              // 0x005A1620
void __fastcall VQA_Movie_Pause(VQAMovie *movie);                                     // 0x005A1630
void __fastcall VQA_Movie_Resume(VQAMovie *movie);                                    // 0x005A1640
void __fastcall VQA_Movie_Blit();                                                     // 0x005A1650

// The Bink player wrapper (Bink.cpp 0x0042FE50-0x0043101F, 0x30 bytes).
// Fields of RAD's BINK structure read by the wrapper (layout of the public
// Bink SDK header; the struct keeps its earlier name).
struct BinkHandleSize {
    int Width;               // +0x00
    int Height;              // +0x04
    unsigned Frames;         // +0x08
    unsigned FrameNum;       // +0x0C current frame, 1-based
    unsigned LastFrameNum;   // +0x10
    unsigned FrameRate;      // +0x14
    unsigned FrameRateDiv;   // +0x18
};

class BinkClass {
public:
    BinkClass(char const *filename);                       // 0x0042FE70
    BinkClass(char const *filename, Surface *surface);    // 0x0042FEA0
    ~BinkClass();                                          // 0x0042FEE0 (Close expanded)
    bool Open(char const *filename);                       // 0x0042FF30
    // Frees the companion, closes the movie and the file handle.
    void Close();                                          // 0x00430230
    void Unknown_00430280(int x, int y);                   // 0x00430280
    void Unknown_004303A0(int frame);                      // 0x004303A0 BinkGoto
    int Unknown_004303C0();                                // 0x004303C0 milliseconds per frame
    void Unknown_004303E0(int unknown);                    // 0x004303E0
    void Unknown_00430400(bool pause);                     // 0x00430400 BinkPause
    bool Unknown_00430420();                               // 0x00430420 past the last frame
    void Unknown_00430430();                               // 0x00430430
    bool Unknown_00430600(Surface *surface, int x, int y); // 0x00430600
    void Unknown_004307E0();                               // 0x004307E0 BinkWait
    void Unknown_00430940(Surface *surface, int x, int y);  // 0x00430940
    void Unknown_004309B0(Surface *surface, int x, int y, bool unknown4);   // 0x004309B0
    void Unknown_00430A30(Surface *surface);               // 0x00430A30
    void Unknown_00430AF0(Surface *surface);               // 0x00430AF0
    bool Unknown_00430800();                               // 0x00430800
    void Unknown_00430820();                               // 0x00430820

    bool unknown_00;                // +0x00
    BinkHandleSize *Handle;         // +0x04
    unsigned SurfaceType;           // +0x08 BinkDDSurfaceType of the screen
    Surface *Target;                // +0x0C
    Rect Area;                      // +0x10
    VQAMovieCompanion *Companion;   // +0x20
    int unknown_24;                 // +0x24 60 / frames per second
    HANDLE File;                    // +0x28 movie inside a mixfile, else INVALID_HANDLE_VALUE
    bool unknown_2c;                // +0x2C
    bool unknown_2d;                // +0x2D
};

// Bink.cpp helpers and globals (names are hypotheses).
#include "shared/sound_available.hpp"
void *unknown_directsound_40a6c0();             // 0x0040A6C0 the DirectSound object
#include "shared/debug_printf.hpp"
extern float unknown_volume_a40b48;             // 0x00A40B48 movie volume scale
extern float unknown_volume_84e9a8;             // 0x0084E9A8
VQAMovieCompanion *__fastcall unknown_create_companion_69b190(char const *filename);   // 0x0069B190

class MovieHandle {
public:
    virtual ~MovieHandle();                                // slot 0 (0x005A1BA0)
    virtual bool Unknown_Slot1() = 0;                      // slot 1 (+0x04) next frame
    virtual void Unknown_Slot2() = 0;                      // slot 2 (+0x08)
    virtual void Pause(bool pause) = 0;                    // slot 3 (+0x0C)
    virtual void Play() = 0;                               // slot 4 (+0x10)
    virtual bool Is_Finished() = 0;                        // slot 5 (+0x14)
    virtual void Set_Position(int x, int y) = 0;          // slot 6 (+0x18)
    virtual void Unknown_Slot7(int frame) = 0;             // slot 7 (+0x1C) seek to a frame
    virtual void Unknown_Slot8(int unknown) = 0;           // slot 8 (+0x20)
    virtual int Unknown_Slot9() = 0;                       // slot 9 (+0x24)
    virtual void Blit() = 0;                               // slot 10 (+0x28)

    // +0x00 vtable
    bool unknown_04;         // +0x04 (read as a byte by RadarClass 0x00633D30: the radar follows it at +0x14B8)
    char unknown_05[3];
    int Width;               // +0x08
    int Height;              // +0x0C
};

class VQMovieHandle : public MovieHandle {
public:
    VQMovieHandle(VQAMovie *movie);                        // 0x005A17B0
    virtual ~VQMovieHandle();                              // 0x005A1A00 (??_G 0x005A1F00)
    virtual bool Unknown_Slot1();                          // 0x005A1860
    virtual void Unknown_Slot2();                          // 0x005A18A0
    virtual void Pause(bool pause);                        // 0x005A17F0
    virtual void Play();                                   // 0x005A1830
    virtual bool Is_Finished();                            // 0x005A1850
    virtual void Set_Position(int x, int y);              // 0x005A18B0
    virtual void Unknown_Slot7(int frame);                 // 0x005A1910
    virtual void Unknown_Slot8(int unknown);               // 0x005A18F0
    virtual int Unknown_Slot9();                           // 0x005A1930
    virtual void Blit();                                   // 0x005A1940

    VQAMovie *Movie;         // +0x10
    bool Finished;           // +0x14
};

class BinkMovieHandle : public MovieHandle {
public:
    BinkMovieHandle(BinkClass *bink);                      // 0x005A1A80
    virtual ~BinkMovieHandle();                            // 0x005A1B70 (??_G 0x005A1F80)
    virtual bool Unknown_Slot1();                          // 0x005A1AF0
    virtual void Unknown_Slot2();                          // 0x005A1B00
    virtual void Pause(bool pause);                        // 0x005A1AB0
    virtual void Play();                                   // 0x005A1AC0
    virtual bool Is_Finished();                            // 0x005A1AE0
    virtual void Set_Position(int x, int y);              // 0x005A1B10
    virtual void Unknown_Slot7(int frame);                 // 0x005A1B40
    virtual void Unknown_Slot8(int unknown);               // 0x005A1B30
    virtual int Unknown_Slot9();                           // 0x005A1B50
    virtual void Blit();                                   // 0x005A1B60

    BinkClass *Bink;         // +0x10
};

extern MovieHandle *CurrentMovieHandle;                    // 0x00A710B0

bool __fastcall Find_Movie_File(char const *name, char *found, int unused);           // 0x005A1BB0
MovieHandle *__fastcall Create_Movie_Handle(char const *name, Surface *surface, Rect const *area);  // 0x005A1D30
int __fastcall Is_Movie_Active();                                                   // 0x005A1ED0
void __fastcall Movie_Handle_Blit();                                                 // 0x005A1EF0

#endif
