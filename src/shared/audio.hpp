// The audio library's DirectSound driver and channel layer (0x00402550-
// 0x0040AC80; "Direct Sound Driver V2.0", 0x007CD184).
//
// No RTTI covers these C-style structures; their names are hypotheses
// taken from the library's own strings ("Audio Device Dump", the
// "Chan:TYPE: STATE" channel dump with FREE/PAUSED/PLAYING, "Audio
// Thread"). Field offsets are evidenced by the matched functions named in
// the comments; unknown_NN fields are untyped placeholders.
//
// The driver descriptor at 0x007CCE20 holds the driver name, the tag
// 'AUDm' (0x007CCE30), the device functions (init 0x00409390, release
// 0x00409F10, open 0x00409FB0, close 0x0040A130) and the channel function
// table (0x007CCDF0, AudioChannelDriver).
#ifndef RA2_SHARED_AUDIO_HPP
#define RA2_SHARED_AUDIO_HPP

#include "shared/dsound_api.hpp"
#include "shared/debug_printf.hpp"
#include "shared/random.hpp"
#include "shared/sound_play.hpp"

struct AudioChannel;
struct AudioDevice;
struct AudioDriver;
struct AudioChannelDriver;
struct AudioStream;
struct AudioQueue;

// A node of the library's circular doubly linked lists. A list is a node
// itself that stores its own address in Priority (0x004071F0); walks stop
// at the node whose Priority is its own address (0x004072F0/0x00407310).
// Ordinary nodes start with priority 0 (0x00407200) and can be inserted in
// priority order (0x00407210, 0x00407260).
struct AudioListNode {
    AudioListNode *Next;            // +0x00
    AudioListNode *Prev;            // +0x04
    int Priority;                   // +0x08
};

// A list head that also counts the users that are changing it (the
// device's channel list; 0x00401F80 and 0x00401F90 are the out-of-line
// copies of Enter and Leave).
struct AudioCountedList : AudioListNode {
    int volatile Busy;              // +0x0C
    void __fastcall Enter();        // 0x00401F80
    void __fastcall Leave();        // 0x00401F90 the count never goes below 0
};

AudioListNode *__fastcall Audio_List_First(AudioListNode *list);                    // 0x004072F0
AudioListNode *__fastcall Audio_List_Next(AudioListNode *node);                     // 0x00407310
int __fastcall Audio_List_Add_Ascending(AudioListNode *list, AudioListNode *node);  // 0x00407210 returns the position
void __fastcall Audio_List_Add_Descending(AudioListNode *list, AudioListNode *node); // 0x00407260
AudioListNode *__fastcall Audio_List_Nth(AudioListNode *list, int index);           // 0x00407330
void __fastcall Audio_List_Add_Tail(AudioListNode *list, AudioListNode *node);      // 0x00407350
AudioListNode *__fastcall Audio_List_Next_Unchecked(AudioListNode *node);          // 0x004073A0 (Next without the null test)
void __fastcall Audio_List_Init(AudioListNode *list);                               // 0x004071F0 (empty list head)
void __fastcall Audio_List_Init_Node(AudioListNode *node);                          // 0x00407200 (unlinked node)
void __fastcall Audio_List_Move_All(AudioListNode *list, AudioListNode *destination); // 0x004072B0
int __fastcall Audio_List_Count(AudioListNode *list);                               // 0x004072E0
void __fastcall Audio_List_Add_Head(AudioListNode *list, AudioListNode *node);      // 0x00407370
void __fastcall Audio_List_Remove(AudioListNode *node);                             // 0x00407380
AudioListNode *__fastcall Audio_List_Last(AudioListNode *list);                    // 0x004073B0

// A list cursor (0x00402C00 First, 0x00402C20 Next); VC6 expands it inline.
struct AudioListCursor {
    AudioListNode *Node;
    int unknown_04;

    void First(AudioListNode *list) { Node = Audio_List_First(list); }
    AudioListNode *Next()
    {
        if (Node != 0) {
            Node = Audio_List_Next(Node);
        }
        return Node;
    }
};

// The same walk with an out-of-line Next (0x004035D0).
struct AudioListIterator {
    AudioListNode *Node;
    int unknown_04;

    void First(AudioListNode *list) { Node = Audio_List_First(list); }
    AudioListNode *Next();                              // 0x004035D0
};

// A fixed-size block pool (0x00407400-0x00407470): count blocks of size
// bytes, each behind an 8-byte link, chained in a free list.
struct AudioPoolBlock {
    AudioPoolBlock *Next;           // +0x00
    int unknown_04;
    // +0x08 the block's data
};

struct AudioPool {
    AudioPoolBlock *Free;           // +0x00
    int unknown_04;
    // +0x08 the blocks
};

AudioPool *__fastcall Audio_Pool_Create(unsigned int count, int size);              // 0x00407400
void __fastcall Audio_Pool_Destroy(AudioPool *pool);                                // 0x00407440
void *__fastcall Audio_Pool_Alloc(AudioPool *pool);                                 // 0x00407450
void __fastcall Audio_Pool_Free(AudioPool *pool, void *data);                       // 0x00407460
int __fastcall Audio_Pool_Free_Count(AudioPool *pool);                              // 0x00407470

// A 32-byte sample format block (sources, channels, the device default and
// each DirectSound channel buffer keep one; 0x00402800 compares and copies
// it, 0x0040A260 builds a WAVEFORMATEX from it).
struct AudioFormat {
    int Bytes_For_Time(__int64 milliseconds);                       // 0x00408460
    unsigned __int64 __fastcall Time_For_Bytes(int bytes);          // 0x00408480 milliseconds
    void Update_Rate();                                             // 0x004084D0

    int unknown_00;
    int Type;                       // +0x04 AUDIO_FORMAT_* (0x00409B60)
    int Rate;                       // +0x08 samples per second
    int Channels;                   // +0x0C
    int BytesPerSample;             // +0x10
    int BytesPerSecond;             // +0x14 (0x004084D0; a quarter for ADPCM)
    int BlockSize;                  // +0x18 bytes per compressed block
    int unknown_1c;
};

enum {
    AUDIO_FORMAT_PCM = 0,
    AUDIO_FORMAT_IMA_ADPCM = 1
};

// The mixing thread's timing statistics (at +0x170 of a device; times
// in milliseconds). 0x00403870 sets the period (+0x00 and the late limit
// +0x08, ten times it as the peak window +0x20); 0x004038A0 and
// 0x004038C0 set +0x08 and +0x20 alone; 0x00403920 records one tick.
struct AudioTimeSpan {
    void Reset();                   // 0x00403820
    void Set(__int64 value);        // 0x00403870
    void Set_08(__int64 value);     // 0x004038A0
    void Set_20(__int64 value);     // 0x004038C0
    void Tick(__int64 now);         // 0x00403920
    int Is_Due(__int64 now);        // 0x004038E0 now - LastTime has reached the period (unsigned)
    // Prints "period (elapsed,maximum,peak,~late) spinner" into the buffer (0x004039C0; the device dump's
    // mixer: and level: lines).
    void __fastcall Format(char *buffer);

    __int64 volatile unknown_00;             // +0x00 period
    __int64 volatile LateLimit;              // +0x08
    __int64 volatile Elapsed;                // +0x10 since the previous tick
    __int64 volatile Peak;                   // +0x18 (reset when above the window)
    __int64 volatile PeakWindow;             // +0x20
    __int64 volatile LastTime;               // +0x28
    __int64 volatile Maximum;                // +0x30
    __int64 unknown_38;             // +0x38
    __int64 volatile unknown_40;    // +0x40 (5000 after Reset)
    int volatile TickCount;         // +0x48
    int volatile LateCount;         // +0x4C
    int volatile unknown_50;
    int unknown_54;
};

// A level that ramps towards its target over time (0x28 bytes; methods at
// 0x00407030-0x004071D4). Values are 16.16 fixed point.
enum {
    AUDIO_LEVEL_PENDING = 0x01,     // jump to the target on the next update
    AUDIO_LEVEL_CHANGED = 0x02      // the current value moved
};

struct AudioLevel {
    void __fastcall Init(int value);                    // 0x00407030 value, 1000 ms, then Update
    void __fastcall Set(int value);                     // 0x00407080 jump to value
    void __fastcall Set_Target(int value);              // 0x004070A0 ramp to value
    void __fastcall Set_Rate(__int64 period, int step); // 0x004070D0 step per period (ms)
    int __fastcall Update();                            // 0x004070F0 1 when the level changed
    int __fastcall Get_Target();                        // 0x004071E0 the target, whole part

    unsigned int volatile Flags;    // +0x00 AUDIO_LEVEL_*
    unsigned int Current;           // +0x04
    unsigned int Target;            // +0x08
    unsigned int Step;              // +0x0C per millisecond
    __int64 MaxElapsed;             // +0x10
    __int64 LastTime;               // +0x18 (Audio_Now)
    char unknown_20[0x28 - 0x20];
};

// A channel's volume, frequency and pan levels. 0x00401000 initializes
// them (volume 0x4000 = 100%, frequency 100%, pan 0x2000 = centre);
// 0x004010C0 combines another set into this one (volume and frequency
// multiply, pan offsets from centre). Every channel has its own set at
// +0x10 and the result at +0xD8; the eight sets at 0x0083144C-0x00831468
// are global.
struct AudioLevelSet {
    void __fastcall Init();                             // 0x00401000
    void Update();                                      // 0x00401080
    int Changed();                                      // 0x004010A0
    void Clear_Changed();                               // 0x00401170
    int __fastcall Scale_Frequency(int value);          // 0x00401190 value * frequency / 100

    AudioLevel Volume;              // +0x00 0..0x4000
    AudioLevel Frequency;           // +0x28 percent
    AudioLevel Pan;                 // +0x50 0..0x4000, 0x2000 centre
};

// 0x004010C0 is a free __fastcall function: as a member, VC6 orders the multiply operands differently.
void __fastcall Audio_Level_Set_Combine(AudioLevelSet *set, AudioLevelSet *other);  // 0x004010C0

// What a channel plays from (0x20 bytes; 0x00408380 makes one with its
// own data buffer): a data pointer and total size, a list of pieces
// (0x00408440 returns the first) and an optional format (+0x14).
struct AudioSource;

struct AudioSourceInfo : AudioListNode {
    void __fastcall Init(void *data, int size);     // 0x00408500
    void Detach();                                  // 0x00408520

    int unknown_0c;                 // +0x0C the piece's data
    int unknown_10;                 // +0x10 its size in bytes
    AudioSource *Source;            // +0x14 the source it belongs to
};

struct AudioSource {
    void Finish();                  // 0x00408450 (does nothing)
    AudioSourceInfo *Info();        // 0x00408440 the first piece

    int unknown_00;                 // +0x00 data (the owned buffer, or the play position)
    int unknown_04;                 // +0x04 total size
    AudioListNode Pieces;           // +0x08 AudioSourceInfo entries
    AudioFormat *Format;            // +0x14 (null: the device default)
    int unknown_18;                 // +0x18
    int unknown_1c;                 // +0x1C
};

class FileClass;

// The sound bag (AUDIO.BAG with its .IDX index): a table of named sounds
// with their position in the bag, size and format, and the file the sound
// being read is taken from.
enum {
    AUDIO_BAG_STEREO = 0x01,
    AUDIO_BAG_16_BIT = 0x04,
    AUDIO_BAG_ADPCM = 0x08
};

struct AudioBagEntry {
    char Name[0x10];                // +0x00
    int Offset;                     // +0x10 in the bag file
    int Size;                       // +0x14 bytes
    int Rate;                       // +0x18 samples per second
    unsigned int Flags;             // +0x1C AUDIO_BAG_*
    int BlockSize;                  // +0x20
};

struct AudioBag {
    AudioBagEntry *Entries;         // +0x00
    int Count;                      // +0x04
    char Path[0x104];               // +0x08
    FileClass *BagFile;             // +0x10C
    FileClass *File;                // +0x110 the file entries are read from (the bag, or a loose .WAV)
    int Loose;                      // +0x114 nonzero: entries are loose files next to the bag
    FileClass *Reader;              // +0x118 the file being read
    int Remaining;                  // +0x11C bytes of the entry left
    int unknown_120;
};

// A cache of sounds read from the bag: a list of entries (one per sound,
// with the AudioSource that plays it) and the two pools they and their
// pieces are taken from. 0x004019E0 makes one of bytes of piece memory,
// that many entries and pieces of block bytes.
struct AudioBank;

struct AudioBankEntry : AudioListNode {
    AudioSource *__fastcall Get_Source();      // 0x00402030
    int volatile unknown_0c;        // +0x0C nonzero while in use
    int unknown_10;
    int Id;                         // +0x14
    void *Data;                     // +0x18
    AudioSource Source;             // +0x1C
    AudioBank *Owner;               // +0x3C
    AudioFormat Format;             // +0x40 the sound's format
    int unknown_60;
};

struct AudioBank {
    AudioBag *Bag;                  // +0x00 where the sounds are read from
    AudioPool *Pieces;              // +0x04
    AudioPool *Entries;             // +0x08
    AudioListNode List;             // +0x0C the entries
    int BlockSize;                  // +0x18
    char unknown_1c[0xe8 - 0x1c];
};

AudioBank *__fastcall Audio_Bank_Create(AudioBag *bag, int bytes, int entries, int block);   // 0x004019E0 (ret 8)
void __fastcall Audio_Bank_Destroy(AudioBank *bank);                                        // 0x00401B00
AudioBankEntry *__fastcall Audio_Bank_Find(AudioBank *bank, int id);                       // 0x00401BB0
AudioBankEntry *__fastcall Audio_Bank_Load(AudioBank *bank, int id);                         // 0x00401C00
int __fastcall Audio_Bank_Evict(AudioBank *bank);                                           // 0x00401EF0
void __fastcall Audio_Bank_Entry_Destroy(AudioBankEntry *entry);                            // 0x00401FC0

int __fastcall Audio_Bag_Find(AudioBag *bag, char const *name);                             // 0x004015C0 index of the entry, -1 if there is none
void __fastcall Audio_Bag_Destroy(AudioBag *bag);                                           // 0x00401580
void __fastcall Audio_Bag_Get_Format(AudioBag *bag, int index, AudioFormat *format);        // 0x00401640
int __fastcall Audio_Bag_Read(AudioBag *bag, void *buffer, int length);                     // 0x004018C0
int __fastcall Audio_Bag_Open(AudioBag *bag, int index);                                    // 0x004016F0
AudioBag *__fastcall Audio_Bag_Create(char const *path, char const *directory);              // 0x004011C0
void __fastcall Audio_Bag_Close(AudioBag *bag);                                             // 0x00401910

AudioSource *__fastcall Audio_Source_Create(int size);                                      // 0x00408380
void __fastcall Audio_Source_Destroy(AudioSource *source);                                  // 0x004083E0
void __fastcall Audio_Source_Add_Piece(AudioSource *source, AudioSourceInfo *piece);        // 0x00408420

// A channel driver's function table (the DirectSound one is at 0x007CCDF0).
// Every entry takes the channel in ECX; Lock and Unlock ignore it.
struct AudioChannelDriver {
    int unknown_00;
    int (__fastcall *Open)(AudioChannel *channel);              // +0x04 0x0040A180
    int (__fastcall *Close)(AudioChannel *channel);             // +0x08 0x0040A1F0
    HRESULT (__fastcall *Start)(AudioChannel *channel);         // +0x0C 0x0040A260
    int (__fastcall *Stop)(AudioChannel *channel);              // +0x10 0x0040A530
    int (__fastcall *Pause)(AudioChannel *channel);             // +0x14 0x0040A570
    HRESULT (__fastcall *Resume)(AudioChannel *channel);        // +0x18 0x0040A590
    int (__fastcall *Is_Playing)(AudioChannel *channel);        // +0x1C 0x0040A5C0
    int (__fastcall *Apply_Settings)(AudioChannel *channel);    // +0x20 0x0040A5F0
    HRESULT (__fastcall *unknown_24)(AudioChannel *channel);    // +0x24 0x0040A690
    int (__fastcall *Lock)(AudioChannel *channel);              // +0x28 0x0040A6A0
    int (__fastcall *Unlock)(AudioChannel *channel);            // +0x2C 0x0040A6B0
};

// The file streamer ("Audio Stream", 0x00407480-0x00408F50): streams
// whose sound comes from a file through a ring buffer (AudioStream) into
// a channel. All streams are in Audio_Stream_List under Audio_Stream_Lock;
// the streamer thread (0x004075B0) refills them.
class FileClass;

enum {
    AUDIO_STREAM_PLAYING = 0x01,
    AUDIO_STREAM_PAUSED = 0x02,
    AUDIO_STREAM_FILLING = 0x04     // the streamer thread still refills it
};

struct AudioStreamPlayer : AudioListNode {
    unsigned int Flags;                             // +0x0C AUDIO_STREAM_*
    int unknown_10;                                 // +0x10 (the creator's first argument)
    AudioChannel *Channel;                          // +0x14
    __int64 BufferTime;                             // +0x18 milliseconds buffered (at least 7000)
    __int64 unknown_20;                             // +0x20 (Audio_Now when it stopped or started)
    __int64 StartTime;                              // +0x28
    AudioStream *Ring;                              // +0x30
    AudioQueue *Fill;                               // +0x34 the ring's queue 0 (filled from the file)
    AudioQueue *Drain;                              // +0x38 the ring's queue 1 (played)
    AudioSource Source;                             // +0x3C what the channel plays
    AudioFormat Format;                             // +0x5C the file's format
    FileClass *File;                                // +0x7C
    int volatile PauseCount;                        // +0x80
    int unknown_84;
    int volatile HoldCount;                         // +0x88 nonzero: left alone by stop-all
    int unknown_8c;
    int unknown_90;                                 // +0x90 bytes per refill
    int DataSize;                                   // +0x94 bytes of sound data in the file
    int DataStart;                                  // +0x98 file position of the data
    int Remaining;                                  // +0x9C bytes of the file still to read
    int unknown_a0;                                 // +0xA0
    char Name[0x50];                                // +0xA4
    char unknown_f4[0xf8 - 0xf4];
};

// The streamer thread's shared block (0x00831480; 0x004075B0 receives it).
struct AudioStreamerThread {
    int volatile Quit;              // +0x00
    int volatile PassCount;         // +0x04
    int volatile Done;              // +0x08
    int unknown_0c;
    __int64 volatile Interval;      // +0x10 milliseconds between passes (1000 at start)
    int volatile Started;           // +0x18
    int unknown_1c;
    AudioTimeSpan Timing;           // +0x20
};

extern AudioStreamerThread Audio_Streamer;                // 0x00831480
extern HANDLE Audio_Streamer_Handle;                    // 0x00831500
extern DWORD Audio_Streamer_Id;                         // 0x00831504
extern CRITICAL_SECTION Audio_Stream_Lock;              // 0x00831508
extern AudioListNode Audio_Stream_List;                 // 0x00831520
extern int Audio_Streamer_Initialized;                  // 0x0083152C
extern int Audio_Streamer_Running;                      // 0x00831530
extern bool Audio_Stream_In_Read;                       // 0x00AB663C set around reads from a stream file

void __fastcall Audio_Source_Reset(AudioSource *source);                                    // 0x00408400
int __fastcall Audio_Format_Read_Wave(FileClass *file, AudioFormat *format, int *data_size);  // 0x00408530
void __fastcall Audio_Format_Init(AudioFormat *format);                                     // 0x004084C0 zero-fills it
AudioChannel *__fastcall Audio_Device_Create_Channel(AudioDevice *device, int flags);       // 0x004036C0
int __fastcall Audio_Streamer_Init();                                                                // 0x00407480
DWORD __stdcall Audio_Streamer_Proc(void *parameter);                                       // 0x004075B0
void Audio_Streamer_Shutdown();                                                             // 0x004076B0
AudioStreamPlayer *__fastcall Audio_Stream_Create(AudioDevice *device, __int64 buffer_time);              // 0x00407790
int __fastcall Audio_Stream_Next_Block(AudioChannel *channel);                              // 0x004078F0
int __fastcall Audio_Stream_Channel_Done(AudioChannel *channel);                            // 0x00407960
int __fastcall Audio_Stream_Channel_End(AudioChannel *channel);                             // 0x00407990
void __fastcall Audio_Stream_Destroy(AudioStreamPlayer *stream);                            // 0x004079C0
void __fastcall Audio_Stream_Set_Levels_94(AudioStreamPlayer *stream, AudioLevelSet *levels);  // 0x00407A70
void __fastcall Audio_Stream_Set_Levels_9c(AudioStreamPlayer *stream, AudioLevelSet *levels);  // 0x00407A80
int __fastcall Audio_Stream_Open(AudioStreamPlayer *stream, char const *name, int raw);      // 0x00407A90
void __fastcall Audio_Stream_Stop(AudioStreamPlayer *stream);                               // 0x00407E60
void __fastcall Audio_Stream_Hold(AudioStreamPlayer *stream);                               // 0x00407EA0
void __fastcall Audio_Stream_Release(AudioStreamPlayer *stream);                            // 0x00407EB0
void __fastcall Audio_Stream_Pause(AudioStreamPlayer *stream);                              // 0x00407ED0
void __fastcall Audio_Stream_Resume(AudioStreamPlayer *stream);                             // 0x00407F20
void __fastcall Audio_Stream_Fade_In(AudioStreamPlayer *stream);                            // 0x00407FD0
void __fastcall Audio_Stream_Fade_Out(AudioStreamPlayer *stream);                           // 0x00407FE0
int __fastcall Audio_Stream_Is_Playing(AudioStreamPlayer *stream);                          // 0x00407F90
void __fastcall Audio_Stream_Set_Name(AudioStreamPlayer *stream, char const *name);         // 0x00407FA0
char *__fastcall Audio_Stream_Name(AudioStreamPlayer *stream);                              // 0x00407FC0
int __fastcall Audio_Stream_Is_Fading(AudioStreamPlayer *stream);                           // 0x00407FF0
void __fastcall Audio_Stream_Wait(AudioStreamPlayer *stream);                               // 0x00408010
__int64 __fastcall Audio_Stream_Stop_Time(AudioStreamPlayer *stream);                       // 0x00408060
void __fastcall Audio_Streams_Stop_Filling();                                                        // 0x00408070
void Audio_Streams_Stop();                                                                  // 0x004080C0
void Audio_Streams_Hold();                                                                  // 0x00408120
void Audio_Streams_Release();                                                               // 0x00408150
void Audio_Streams_Pause();                                                                 // 0x00408190
void Audio_Streams_Resume();                                                                // 0x00408210
void Audio_Streams_Fade_Out();                                                              // 0x004082B0
void Audio_Streams_Fade_In();                                                               // 0x004082F0
int Audio_Streams_Done_Fading();                                                            // 0x00408330
void unknown_481fb0();                                                                       // 0x00481FB0 once per frame (shared/ms_engine.hpp)

// IMA ADPCM decoder state (0x0040ABF0).
struct AudioAdpcmState {
    int Sample;                     // +0x00 predicted sample
    int Index;                      // +0x04 step index, 0..88
};

struct AudioChannelBuffer;

// A decoder: fills destination from source, updating both sizes to the
// bytes produced and consumed (0x00409CB0 copies PCM, 0x00409D00 runs the
// block decoder). The block decoder decodes one input block into the
// output buffer (0x0040A990, IMA ADPCM).
typedef int (__fastcall *AudioDecodeFunction)(AudioChannelBuffer *record, void *destination, int *destination_size,
                                              void const *source, int *source_size);
typedef int (__fastcall *AudioBlockFunction)(AudioChannelBuffer *record);

// The block decoder's states (0x00409D00).
enum {
    AUDIO_DECODE_READ = 0,          // copy source bytes into the input block
    AUDIO_DECODE_WRITE = 1,         // copy decoded bytes out of the output block
    AUDIO_DECODE_BLOCK = 2,         // decode the input block
    AUDIO_DECODE_START = 3          // begin the next input block
};

// The DirectSound driver's per-channel buffer record (0xE0 bytes, zeroed
// by 0x0040A180, released by 0x0040A1F0).
struct AudioChannelBuffer {
    AudioChannel *Channel;          // +0x00
    int unknown_04;
    int volatile unknown_08;        // +0x08
    int volatile unknown_0c;        // +0x0C play position in frames
    __int64 volatile unknown_10;             // +0x10 last update time (ms)
    __int64 unknown_18;             // +0x18 time between the last two updates
    int unknown_20;                 // +0x20
    int unknown_24;                 // +0x24
    int unknown_28;                 // +0x28
    int volatile unknown_2c;        // +0x2C
    DWORD volatile PlayCursor;      // +0x30
    DWORD WriteCursor;              // +0x34
    int volatile unknown_38;        // +0x38
    int volatile unknown_3c;        // +0x3C
    int unknown_40;                 // +0x40
    AudioFormat Format;             // +0x44 the buffer's format
    IDirectSoundBuffer *Buffer;     // +0x64
    int BufferBytes;                // +0x68
    int FrameBytes;                 // +0x6C (not volatile: 0x004094D0 folds it into imul)
    AudioDecodeFunction Decode;     // +0x70
    int DecodeState;                // +0x74 AUDIO_DECODE_* (0x00409D00)
    int NextDecodeState;            // +0x78
    void *Input;                    // +0x7C compressed block buffer (malloc)
    int unknown_80;                 // +0x80
    int unknown_84;                 // +0x84
    int InputCapacity;              // +0x88
    int InputNeeded;                // +0x8C
    void *Output;                   // +0x90 decoded block buffer (malloc)
    int unknown_94;                 // +0x94
    int unknown_98;                 // +0x98
    int OutputCapacity;             // +0x9C
    int OutputNeeded;               // +0xA0
    int DecodeChannels;             // +0xA4
    int unknown_a8;                 // +0xA8
    int BlockSize;                  // +0xAC
    AudioBlockFunction Decode_Block;    // +0xB0
    AudioAdpcmState Adpcm[2];       // +0xB4 one per channel
    char unknown_c4[0xcc - 0xc4];
    int unknown_cc;                 // +0xCC
    int volatile unknown_d0;        // +0xD0
    int volatile unknown_d4;        // +0xD4
    int unknown_d8;                 // +0xD8
    DWORD volatile unknown_dc;      // +0xDC
};

// Channel flags (+0xA4); the dump names the states.
enum {
    AUDIO_CHANNEL_PLAYING = 0x01,
    AUDIO_CHANNEL_PAUSED = 0x04,
    AUDIO_CHANNEL_FREE = 0x08,
    AUDIO_CHANNEL_FLAG_10 = 0x10
};

// A playback channel, linked into its device's channel list.
struct AudioChannel : AudioListNode {
    int unknown_0c;                                 // +0x0C (0x00402440 sets it)
    AudioLevelSet Levels;                           // +0x10 the channel's own levels
    AudioLevelSet *unknown_levels_88;               // +0x88
    char unknown_08c[0x90 - 0x8c];
    AudioLevelSet *unknown_levels_90;               // +0x90 (combined and cleared)
    AudioLevelSet *unknown_levels_94;               // +0x94 (0x00830B50 at reset)
    AudioLevelSet *unknown_levels_98;               // +0x98
    AudioLevelSet *unknown_levels_9c;               // +0x9C
    int unknown_a0;                                 // +0xA0
    unsigned int volatile Flags;                    // +0xA4 shared with the mixing thread
    int volatile LoopCount;                         // +0xA8 -1 loops forever
    AudioDevice *Device;                            // +0xAC
    int (__fastcall *unknown_next_b0)(AudioChannel *channel);               // +0xB0
    int (__fastcall *unknown_loop_b4)(AudioChannel *channel);               // +0xB4
    int (__fastcall *unknown_done_b8)(AudioChannel *channel);               // +0xB8
    int (__fastcall *unknown_end_callback_bc)(AudioChannel *channel);      // +0xBC
    void *Owner;                                    // +0xC0 the stream or event feeding this channel
    char unknown_0c4[0xd4 - 0xc4];
    AudioChannelDriver const *Driver;               // +0xD4
    AudioLevelSet Settings;                         // +0xD8 the combined levels the driver applies
    char unknown_150[0x158 - 0x150];
    AudioChannelBuffer *DriverBuffer;               // +0x158
    int (__fastcall *unknown_next_block_15c)(AudioChannel *channel);       // +0x15C 0x004022C0
    int (__fastcall *unknown_end_of_source_160)(AudioChannel *channel);    // +0x160 0x00402330
    int (__fastcall *unknown_stop_callback_164)(AudioChannel *channel);    // +0x164 0x004023F0
    AudioSource *Source;                            // +0x168
    AudioSourceInfo *SourceInfo;                    // +0x16C
    int unknown_170;                                // +0x170
    int unknown_174;                                // +0x174
    int unknown_178;                                // +0x178
    AudioFormat Format;                             // +0x17C
    int FormatChanged;                              // +0x19C
    int unknown_1a0;                                // +0x1A0 set when the driver buffer is rebuilt
    char unknown_1a4[0x1a8 - 0x1a4];
    __int64 unknown_1a8;                            // +0x1A8 milliseconds (the stream's block length)
    __int64 unknown_1b0;                            // +0x1B0 milliseconds (the stream's first fill)
    char unknown_1b8[0x1c0 - 0x1b8];
};

// A driver descriptor (the DirectSound one is at 0x007CCE20).
struct AudioDriverInfo {
    char const *Name;                               // +0x00 "Direct Sound Driver V2.0"
    int unknown_04;
    unsigned int unknown_flags_08;                  // +0x08 bit 2: sets 0x00830B48 on creation
    unsigned int Flags;                             // +0x0C bit 1: in use
    unsigned int Tag;                               // +0x10 'AUDm'
    HRESULT (__fastcall *Init)(AudioDriver *driver);            // +0x14 0x00409390
    void (__fastcall *Release)(AudioDriver *driver);            // +0x18 0x00409F10
    HRESULT (__fastcall *Open)(AudioDevice *device);            // +0x1C 0x00409FB0
    void (__fastcall *Close)(AudioDevice *device);              // +0x20 0x0040A130
    AudioChannelDriver const *ChannelDriver;                    // +0x24 0x007CCDF0
};

// A driver instance (0x60 bytes, made by 0x00402AF0), linked into the
// system's driver list.
struct AudioDriver : AudioListNode {
    AudioDriverInfo *Info;                          // +0x0C
    int volatile DeviceCount;                       // +0x10
    int unknown_14;
    int unknown_ready_18;                           // +0x18 set by Init; summed by 0x00402C40
    AudioDevice *Devices[(0x60 - 0x1c) / 4];        // +0x1C by device index
};

// The audio system (0x007CC968 points to it): the driver list, the device
// list, a busy count and the master levels.
struct AudioSystem {
    AudioListNode Drivers;                          // +0x00
    AudioListNode Devices;                          // +0x0C
    int volatile Busy;                              // +0x18
    char unknown_1c[0x20 - 0x1c];
    AudioLevelSet Levels;                           // +0x20 (0x00830B50 points here)
};

// An audio device (the object 0x00406F40 returns from 0x00831438), linked
// into the system's device list.
struct AudioDevice : AudioListNode {
    unsigned int Flags;                             // +0x0C bit 2: skipped by 0x00402900
    int volatile RefCount;                          // +0x10 users of the device
    int unknown_14;
    AudioDriver *Driver;                            // +0x18
    int DriverIndex;                                // +0x1C slot in Driver->Devices
    char unknown_020[0x24 - 0x20];
    AudioFormat NativeFormat;                       // +0x24
    AudioFormat DefaultFormat;                      // +0x44
    char unknown_064[0x68 - 0x64];
    AudioLevelSet Levels;                           // +0x68 the device (master) levels
    char unknown_0e0[0xe8 - 0xe0];
    AudioLevelSet *unknown_levels_e8;               // +0xE8
    int Id;                                         // +0xEC the index the device was asked for
    int ChannelCount;                               // +0xF0
    int unknown_f4;                                 // +0xF4
    AudioListNode ChannelList;                      // +0xF8
    int volatile unknown_busy_104;                  // +0x104
    char unknown_108[0x10c - 0x108];
    int (__fastcall *unknown_update_10c)(AudioDevice *device);      // +0x10C 0x00402F60 until the device is run
    void Run_Update();                              // 0x00403810 (jumps through +0x10C)
    AudioTimeSpan LevelSpan;                        // +0x110 the level update timing ("level:" in the dump)
    char unknown_168[0x170 - 0x168];
    AudioTimeSpan Span;                             // +0x170 the mixer timing ("mixer:" in the dump)
    char unknown_1c8[0x1d0 - 0x1c8];
    AudioChannelDriver const *ChannelDriver;        // +0x1D0 the channel functions (0x007CCDF0 for DirectSound)
    char unknown_1d4[0x1d8 - 0x1d4];
    int unknown_1d8;                                // +0x1D8
    int unknown_1dc;                                // +0x1DC
    int unknown_1e0;                                // +0x1E0
    char unknown_1e4[0x1e8 - 0x1e4];
};

// The block shared with the mixing thread (0x00831560; 0x004094D0 gets
// its address as the thread parameter).
struct AudioThreadBlock {
    int volatile Quit;              // +0x00 set to ask the thread to stop
    int volatile PassCount;         // +0x04 passes made
    int volatile Done;              // +0x08 set by the thread when it stops
    int volatile unknown_0c;        // +0x0C
    __int64 volatile Interval;      // +0x10 milliseconds to sleep between passes (33 at start)
    int volatile Started;           // +0x18 set by the thread
    HANDLE Handle;                  // +0x1C
    AudioDevice *Device;            // +0x20 the device being mixed (read once per pass by 0x004094D0)
    DWORD ThreadId;                 // +0x24
};

// The ring buffer (0x00408710-0x00409260): a ring of buffer nodes shared
// by two queues, 0 filling it ("Write" access) and 1 draining it ("Read"
// access). Each node has an aligned buffer and one (pointer, length)
// window per queue; committing bytes on one queue makes them available to
// the other.
struct AudioStreamWindow {
    char *Pointer;                  // +0x00
    int Length;                     // +0x04
};

struct AudioStreamNode : AudioListNode {
    // The next node round the ring, skipping the ring's list head; 0 when
    // the ring is empty (0x00408D70 is the out-of-line copy).
    AudioStreamNode *Ring_Next();
    // Opens both windows over the whole buffer.
    void Reset_Windows()
    {
        for (int window = 0; window < 2; window++) {
            Windows[window].Pointer = Base;
            Windows[window].Length = Size;
        }
    }

    int unknown_0c;
    void *Data;                     // +0x10 the allocation (Base is aligned inside it)
    int Shift;                      // +0x14 alignment: 1 << Shift bytes
    char *Base;                     // +0x18
    int Size;                       // +0x1C
    AudioStreamWindow Windows[2];   // +0x20 one per queue
    AudioStream *Ring;              // +0x30 the ring this node is in
    int Index;                      // +0x34 position in the ring
    int unknown_38;
};

enum {
    AUDIO_QUEUE_AT_HEAD = 0x01      // the current node caught up with the commit node
};

// One side of the ring (64 bytes; the ring holds two at +0x18).
struct AudioQueue {
    void Restart(AudioStreamNode *first);

    AudioStream *Stream;            // +0x00
    char *Pointer;                  // +0x04 current position
    int Available;                  // +0x08 contiguous bytes at Pointer (0x004090E0)
    AudioStreamNode *Node;          // +0x0C current node
    unsigned int volatile Flags;    // +0x10 AUDIO_QUEUE_*
    int Index;                      // +0x14 0 (fill) or 1 (drain): this queue's window in each node
    int unknown_18;                 // +0x18 nonzero: commits are left to the caller
    int volatile Users;             // +0x1C acquisitions (0x00408B50 allows one)
    int unknown_20;
    HRESULT Error;                  // +0x24 0x80040000 after a failed transfer
    AudioStreamNode *CommitNode;    // +0x28
    int Pending;                    // +0x2C bytes advanced but not committed
    int Position;                   // +0x30 offset in the ring (mod Stream->Size)
    int volatile Queued;            // +0x34 bytes the other queue committed to this one (the queues are shared between threads)
    int volatile Consumed;          // +0x38 bytes this queue committed
    char unknown_3c[0x40 - 0x3c];
};

enum {
    AUDIO_RING_FLAG_2 = 0x02        // cleared whenever a node is added or removed
};

struct AudioStream {
    int NodeCount;                  // +0x00
    AudioListNode Nodes;            // +0x04 the ring's nodes
    unsigned int Flags;             // +0x10
    int Size;                       // +0x14 ring size in bytes
    AudioQueue Queues[2];           // +0x18
    int volatile Users;             // +0x98 acquired queues
    char unknown_9c[0xa4 - 0x9c];
};

void __fastcall Audio_Queue_Reset(AudioQueue *queue);                                       // 0x00408850

// Starts the queue over again at first (inline in Audio_Ring_Reset):
// nothing queued or consumed (both -1001), position 0.
inline void AudioQueue::Restart(AudioStreamNode *first)
{
    CommitNode = first;
    Queued = -1001;
    Consumed = Queued;
    Position = 0;
    Audio_Queue_Reset(this);
}

// Opens every node's windows over its whole buffer and numbers the nodes;
// returns the first node or 0 (inline in Audio_Ring_Reset).
inline AudioStreamNode *Audio_Ring_Number_Nodes(AudioStream *ring)
{
    AudioStreamNode *first = (AudioStreamNode *)ring->Nodes.Next;
    if (first == (AudioStreamNode *)&ring->Nodes) {
        first = 0;
    } else if (first != 0) {
        int index = 0;
        AudioStreamNode *node = first;
        do {
            node->Reset_Windows();
            node->Index = index++;
            node = (AudioStreamNode *)node->Next;
        } while (node != (AudioStreamNode *)&ring->Nodes);
    }
    return first;
}

inline AudioStreamNode *AudioStreamNode::Ring_Next()
{
    AudioListNode *head = &Ring->Nodes;
    AudioListNode *next = Next;
    if (next == head) {
        next = next->Next;
        if (next == head) {
            next = 0;
        }
    }
    return (AudioStreamNode *)next;
}

AudioStream *Audio_Ring_Create();                                                           // 0x00408710
void __fastcall Audio_Ring_Destroy(AudioStream *ring);                                      // 0x00408760
void __fastcall Audio_Queue_Reset(AudioQueue *queue);                                       // 0x00408850
void __fastcall Audio_Ring_Clear(AudioStream *ring);                                        // 0x00408890
void __fastcall Audio_Ring_Reset(AudioStream *ring);                                        // 0x00408990
void __fastcall Audio_Ring_Add_Node(AudioStream *ring, AudioStreamNode *node);              // 0x00408A30
int __fastcall Audio_Ring_Add_Nodes(AudioStream *ring, int count, int size, int shift);     // 0x00408A60
AudioQueue *__fastcall Audio_Ring_Acquire(AudioStream *ring, int index);                    // 0x00408B50
int __fastcall Audio_Ring_Drain_Available(AudioStream *ring);                               // 0x00408C50
int __fastcall Audio_Ring_Fill_Available(AudioStream *ring);                                // 0x00408C60
int __fastcall Audio_Ring_Size(AudioStream *ring);                                          // 0x00408C70
int __fastcall Audio_Ring_Is_Full(AudioStream *ring);                                       // 0x00408C80
AudioStreamNode *__fastcall Audio_Ring_Node_Create(int size, int shift);                    // 0x00408CA0
void __fastcall Audio_Ring_Node_Destroy(AudioStreamNode *node);                             // 0x00408D20
void __fastcall Audio_Ring_Node_Remove(AudioStreamNode *node);                              // 0x00408D40
AudioStreamNode *__fastcall Audio_Ring_Node_Next(AudioStreamNode *node);                    // 0x00408D70
void __fastcall Audio_Queue_Release(AudioQueue *queue);                                      // 0x00408D90
int __fastcall Audio_Queue_Set_18(AudioQueue *queue, int value);                            // 0x00408DD0
int __fastcall Audio_Queue_Get_18(AudioQueue *queue);                                       // 0x00408DE0
int __fastcall Audio_Queue_Index(AudioQueue *queue);                                        // 0x00408DF0
int __fastcall Audio_Queue_Copy(AudioQueue *queue, void *buffer, int bytes);                // 0x00408E00
int __fastcall Audio_Queue_File(AudioQueue *queue, FileClass *file, int bytes, int *done);  // 0x00408EA0
int __fastcall Audio_Queue_Stdio(AudioQueue *queue, void *file, int bytes, int *done);      // 0x00408F50
HRESULT __fastcall Audio_Queue_Error(AudioQueue *queue);                                    // 0x00409010
void __fastcall Audio_Queue_Rewind(AudioQueue *queue);                                      // 0x004091D0
int __fastcall Audio_Queue_Position(AudioQueue *queue);                                     // 0x00409250
AudioQueue *__fastcall Audio_Queue_Partner(AudioQueue *queue);                              // 0x00409260
AudioListNode *__fastcall Audio_Device_First_Channel(AudioDevice *device, AudioListIterator *cursor);   // 0x004035B0
int __fastcall Audio_Queue_Commit(AudioQueue *queue);                                // 0x00409020
int __fastcall Audio_Queue_Update(AudioQueue *queue, int limit);                    // 0x004090E0

// Channel operations (ECX is the channel).
void __fastcall Audio_Channel_Update_Settings(AudioChannel *channel);                      // 0x00402220
AudioChannel *__fastcall Audio_Channel_Create(AudioDevice *device);                         // 0x00402040
void __fastcall Audio_Channel_Reuse(AudioChannel *channel);                                 // 0x004024A0
void __fastcall Audio_Device_Destroy(AudioDevice *device);                                  // 0x00402EF0
void __fastcall Audio_Device_Remove(AudioDevice *device);                                   // 0x004033C0
void __fastcall Audio_Device_Release(AudioDevice *device);                                  // 0x00403310 the last user removes and destroys the device
// The sound events (0x00403EB0-0x00406880): a sound that was asked for, from
// the moment it is queued to the moment it has finished. Events are
// taken from a pool (or, flagged 0x80, allocated) and kept in a global
// list; each holds the bank entries (samples) it plays from.
struct AudioEventType : AudioListNode {
    int unknown_0c;                 // cleared when an event has no samples left to play
    unsigned int Flags;             // +0x10 AUDIO_EVENT_TYPE_*
    int unknown_14;                 // +0x14 starts as 0x20
    AudioLevel VolumeLevel;         // +0x18 (Current at +0x1C is the 16.16 volume)
    int unknown_40;                 // +0x40 starts as 2
    char unknown_44[0x48 - 0x44];
    int unknown_48;                 // +0x48 starts as 3
    int LoopCount;                  // +0x4C 0: loop forever
    int unknown_50;                 // +0x50 starts as 10
    float unknown_54;               // +0x54 starts as 0.2
    unsigned int unknown_58;        // above 0x20 the event is not played from its samples
    unsigned int unknown_5c;        // upper bound of the random delay between samples
    int unknown_60;                 // +0x60 low end of the pause between loops (ticks)
    int unknown_64;                 // +0x64 high end
    int unknown_68;                 // +0x68 percent, 0..100
    char Name[0x1f + 1];            // +0x6C
    char unknown_8c[0xb4 - 0x8c];
    int Samples[0x20];              // +0xB4 bag entries (0x004015C0 finds them by name)
    int SampleCount;                // +0x134
    int Intro;                      // +0x138 samples played first (0: none)
    int Outro;                      // +0x13C samples kept for the end
    char unknown_140[0x148 - 0x140];
};

enum {
    AUDIO_EVENT_TYPE_LOOPS = 0x01,
    AUDIO_EVENT_TYPE_RANDOM = 0x02,         // next sample drawn at random
    AUDIO_EVENT_TYPE_SEQUENCE = 0x20,
    AUDIO_EVENT_TYPE_SUSTAIN = 0x40
};

enum {
    AUDIO_EVENT_STOPPED = 0x01,     // already stopped (its samples are given back)
    AUDIO_EVENT_ALLOCATED = 0x80    // deleted rather than returned to the pool
};

struct AudioEventHandle;

struct AudioEvent : AudioListNode {
    int unknown_0c;
    int unknown_10;
    int unknown_14;
    unsigned int volatile Flags;    // +0x18 AUDIO_EVENT_*
    int volatile State;             // +0x1C 2: playing
    int unknown_20;
    AudioEventType *Type;           // +0x24
    AudioBankEntry *Samples[(0xa8 - 0x28) / 4];     // +0x28
    int SampleCount;                // +0xA8
    int unknown_ac;                 // +0xAC index of the sample being played
    AudioChannel *Channel;          // +0xB0
    char unknown_b4[0xb8 - 0xb4];
    AudioLevelSet Levels;           // +0xB8
    char unknown_130[0x138 - 0x130];
    int unknown_138;
    int unknown_13c;
    __int64 volatile unknown_140;   // +0x140 time the event was started or last resumed
    int volatile unknown_148;                // the source waiting for the delay to pass
    int unknown_14c;                // frequency the event's channel starts at
    int unknown_150;                // percent the volume starts below full
    int unknown_154;
    int volatile PauseCount;        // +0x158
    int unknown_15c;
    int unknown_160[(0x1e0 - 0x160) / 4];
    int unknown_1e0;
    int unknown_1e4;                // times the sequence has been replayed
    int Order[0x20];                // +0x1E8 the order the samples will be played in
    int unknown_268;                // +0x268 entries left in Order
    int unknown_26c;                // +0x26C passes played
    int unknown_270;                // +0x270 next entry of Order
    int unknown_274;                // +0x274 the sample picked for the whole pass (random events)
    AudioEventHandle *unknown_278;  // +0x278 the handle the game holds for this event (0: none)
    int unknown_27c;
};

// AudioEventHandle, what the game holds for an event: shared/sound_play.hpp.

// A keyword of the event settings (0x007CCB18, ends with a null name): the
// flags it turns on.
struct AudioEventKeyword {
    char const *Name;
    unsigned int Flags;
};
extern AudioEventKeyword Audio_Event_Keywords[];        // 0x007CCB18

extern AudioListNode Audio_Priority_Lists[][10];         // 0x00830B58 rows of ten lists (0x78 bytes a row); users unknown

extern AudioListNode Audio_Event_List;                  // 0x00830EA0
extern int Audio_Event_Count;                           // 0x00830FA4
extern int Audio_Events_Ready;                          // 0x00830FB8
extern AudioPool *Audio_Event_Pool;                     // 0x00830FC0
extern int Audio_Event_Maximum;                         // 0x00830FA8
extern int Audio_Events_Open;                           // 0x00830FBC
extern int Audio_Enabled;                               // 0x007CCBD8
extern int Audio_Event_Serial;                          // 0x007CCBDC
extern AudioListNode Audio_Event_Type_List;             // 0x00830F70
extern AudioLevelSet Audio_Event_Levels;                // 0x00830ED8
extern AudioBag *Audio_Event_Bag;                       // 0x00830FAC
extern AudioBank *Audio_Event_Bank;                     // 0x00830FB0
extern int Audio_Static_Sound_Count;                    // 0x00AD0848 (static sounds in use; reported with the maximum)
extern int Audio_Static_Sound_Maximum;                  // 0x00AD084C
// Reports the audio event and static sound usage through a callback taking each text line (0x00406770).
void __fastcall Audio_Report_Usage(void (__fastcall *report)(char *text));

// The event a handle stands for, or 0 when the handle no longer matches (a
// stale handle forgets its event).
inline AudioEvent *Audio_Event_Resolve(AudioEventHandle *handle)
{
    if (Audio_Events_Ready == 0 || handle->Token != &Audio_Event_Bag) {
        return 0;
    }
    AudioEvent *event = handle->Event;
    if (event != 0 && (handle->Type != event->Type || handle->Serial != event->unknown_138)) {
        event = 0;
        handle->Event = 0;
    }
    return event;
}

extern AudioDevice *Audio_Event_Device;                 // 0x00830FB4
void __fastcall Audio_Event_Play_Named(char const *name, int volume);                          // 0x00406680
void __fastcall Audio_Event_Load_Samples(AudioEvent *event);                                  // 0x00404890
int __fastcall Audio_Event_Next_Piece(AudioEvent *event);                                     // 0x00404B90
int __fastcall Audio_Event_Begin(AudioEvent *event);                                         // 0x004054B0
void *__fastcall Audio_Find_Listed(int rows);                                               // 0x00404E00 first thing on a list of the first rows, minus 0xA4
void Audio_Events_Update();                                                                  // 0x004041B0
void Audio_Events_Shutdown();                                                                // 0x00403F80
int __fastcall Audio_Events_Init(AudioDevice *device, AudioBag *bag);                         // 0x00403EB0
AudioSource *__fastcall Audio_Event_Next_Sample(AudioEvent *event);                         // 0x00404790
AudioSource *__fastcall Audio_Event_Start_Pass(AudioEvent *event);                          // 0x004046E0
AudioSource *__fastcall Audio_Event_Start_Samples(AudioEvent *event);                       // 0x004046E0

AudioChannel *__fastcall Audio_Event_Start_Channel(int priority, unsigned int flags);        // 0x00405B60
int __fastcall Audio_Event_Channel_Next(AudioChannel *channel);                              // 0x00405AD0
void __fastcall Audio_Event_Update(AudioEvent *event);                                       // 0x004055D0
int __fastcall Audio_Event_Channel_Done(AudioChannel *channel);                              // 0x00405A10
int __fastcall Audio_Event_Channel_End(AudioChannel *channel);                               // 0x00405A00
void __fastcall Audio_Event_Detach(AudioEvent *event);                                      // 0x00404120
void __fastcall Audio_Event_Release_Samples(AudioEvent *event);                             // 0x00404D60
void __fastcall Audio_Event_Free(AudioEvent *event);                                        // 0x00404DB0
void __fastcall Audio_Event_Stop(AudioEvent *event);                                        // 0x00405300
void __fastcall Audio_Event_Pause(AudioEvent *event);                                       // 0x004053F0
void __fastcall Audio_Event_Resume(AudioEvent *event);                                      // 0x00405440
void __fastcall Audio_Event_Finish(AudioEvent *event);                                      // 0x00405590
AudioEvent *__fastcall Audio_Event_Create(AudioEventType *type);                          // 0x00405170
void __fastcall Audio_Level_Fade_To_Zero(AudioLevel *level);                               // 0x00406FA0 ramps a level to 0
void __fastcall Audio_Wait_Drain(AudioLevel *level);                                       // 0x00406FE0 waits until it reaches its target (or MaxElapsed passes)
void __fastcall Audio_Stop();                                                               // 0x00406DC0 (stops the main device channels, clears the events)
void Audio_Events_Clear();                                                                  // 0x00404E50
void Audio_Events_Pause();                                                                  // 0x00404FB0
void Audio_Events_Resume();                                                                 // 0x00405020

AudioDevice *__fastcall Audio_Create_Device(int driver_index, AudioFormat const *format);       // 0x00402C70
int __fastcall Audio_Device_Update(AudioDevice *device);                                    // 0x00402F60 the device's first update function (+0x10C)
AudioChannel *__fastcall Audio_Device_New_Channel(AudioDevice *device);                     // 0x004034B0
int __fastcall Audio_Device_New_Channels(AudioDevice *device, int count);                   // 0x00403530
AudioChannel *__fastcall Audio_Device_Find_Channel(AudioDevice *device, int id);              // 0x004035F0
int __fastcall Audio_Device_Destroy_Channels(AudioDevice *device, int id);                  // 0x004036F0
void __fastcall Audio_Device_Stop_Channels(AudioDevice *device, int id);                    // 0x00403730
void __fastcall Audio_Device_Pause_Channels(AudioDevice *device, int id);                   // 0x00403770
void __fastcall Audio_Device_Resume_Channels(AudioDevice *device, int id);                  // 0x004037C0
int __fastcall Audio_Channel_Next_Piece(AudioChannel *channel);                             // 0x004022C0
int __fastcall Audio_Channel_Source_Ended(AudioChannel *channel);                           // 0x00402330
int __fastcall Audio_Channel_Finished(AudioChannel *channel);                               // 0x004023F0
int __fastcall Audio_Channel_Is_Free(AudioChannel *channel);                                // 0x00402430
void __fastcall Audio_Channel_Release(AudioChannel *channel, int value);                    // 0x00402440
void __fastcall Audio_Channel_Reset(AudioChannel *channel);                                 // 0x004024A0
void __fastcall Audio_Channel_Destroy(AudioChannel *channel);                               // 0x00402550
void __fastcall Audio_Channel_Stop(AudioChannel *channel);                                  // 0x004025B0
void __fastcall Audio_Channel_Pause(AudioChannel *channel);                                 // 0x00402600
void __fastcall Audio_Channel_Resume(AudioChannel *channel);                                // 0x00402650
void __fastcall Audio_Channel_Lock(AudioChannel *channel);                                  // 0x004026A0
void __fastcall Audio_Channel_Unlock(AudioChannel *channel);                                // 0x004026B0
void __fastcall Audio_Channel_Set_Flag_10(AudioChannel *channel);                           // 0x004026C0
void __fastcall Audio_Channel_Clear_Flag_10(AudioChannel *channel);                         // 0x004026F0
HRESULT __fastcall Audio_Channel_Start(AudioChannel *channel);                              // 0x00402720
void __fastcall Audio_Channel_Set_Source(AudioChannel *channel, AudioSource *source);       // 0x00402790
int __fastcall Audio_Channel_Set_Format(AudioChannel *channel, AudioFormat const *format);   // 0x00402800
void __fastcall Audio_Device_Add_Channel(AudioDevice *device, AudioChannel *channel);       // 0x00402860
void __fastcall Audio_Channel_Detach(AudioChannel *channel);                        // 0x004028B0
void Audio_Update_Devices();                                                                // 0x00402900
HRESULT Audio_System_Init();                                                                // 0x00402940
void __fastcall Audio_System_Shutdown();                                                               // 0x00402990
AudioDriver *__fastcall Audio_Create_Driver(AudioDriverInfo *info);                         // 0x00402AF0
void __fastcall Audio_Destroy_Driver(AudioDriver *driver);                                  // 0x00402B80
void Audio_Destroy_Drivers();                                                               // 0x00402BB0
AudioListNode *__fastcall Audio_List_Cursor_Next(AudioListCursor *cursor);                  // 0x00402C20
AudioListNode *__fastcall Audio_Cursor_Advance(AudioListCursor *cursor);                    // 0x004031F0
void __fastcall Audio_First_Device(AudioListCursor *cursor);                                // 0x004031D0 Node = the first device
int Audio_Ready_Driver_Count();                                                                 // 0x00402C40

// The audio stream queue functions (ECX is the queue).
HRESULT __fastcall Audio_Queue_Flush(AudioQueue *queue);                                    // 0x00409210
int __fastcall Audio_Queue_Ready(AudioQueue *queue);                                        // 0x00409230
int __fastcall Audio_Queue_Available(AudioQueue *queue);                                    // 0x00409240
void __fastcall Audio_DS_Setup_Decoder(AudioChannelBuffer *record);                         // 0x00409B60
int __fastcall Audio_Copy_Block(AudioChannelBuffer *record, void *destination, int *destination_size,
                                void const *source, int *source_size);                      // 0x00409CB0
int __fastcall Audio_DS_Decode_Blocks(AudioChannelBuffer *record, void *destination, int *destination_size,
                                      void const *source, int *source_size);                // 0x00409D00
int __fastcall Audio_DS_Decode_Adpcm_Block(AudioChannelBuffer *record);                     // 0x0040A990
int __fastcall Audio_DS_Fill(AudioChannelBuffer *record, int bytes);                       // 0x004097A0

// The millisecond clock.
void Audio_Timer_Init();                                                                    // 0x00409280
__int64 __fastcall Audio_Now();                                                                        // 0x004092D0

// The DirectSound driver: device functions (ECX is the device) ...
HRESULT __fastcall Audio_DS_Init(AudioDriver *driver);                                      // 0x00409390
void Audio_DS_Release();                                                                    // 0x00409F10
HRESULT __fastcall Audio_DS_Open(AudioDevice *device);                                      // 0x00409FB0
void __fastcall Audio_DS_Close();                                                                // 0x0040A130
// ... channel functions (the AudioChannelDriver entries) ...
int __fastcall Audio_DS_Channel_Open(AudioChannel *channel);                                // 0x0040A180
int __fastcall Audio_DS_Channel_Close(AudioChannel *channel);                               // 0x0040A1F0
HRESULT __fastcall Audio_DS_Channel_Start(AudioChannel *channel);                           // 0x0040A260
int __fastcall Audio_DS_Channel_Stop(AudioChannel *channel);                                // 0x0040A530
int __fastcall Audio_DS_Channel_Pause(AudioChannel *channel);                               // 0x0040A570
HRESULT __fastcall Audio_DS_Channel_Resume(AudioChannel *channel);                          // 0x0040A590
int __fastcall Audio_DS_Channel_Is_Playing(AudioChannel *channel);                          // 0x0040A5C0
int __fastcall Audio_DS_Channel_Apply_Settings(AudioChannel *channel);                      // 0x0040A5F0
// ... and the primary buffer.
void __fastcall Audio_DS_Set_Primary_Format(int rate, int bits, int channels);              // 0x0040A6E0
void __fastcall Audio_DS_Apply_Primary_Format();                                            // 0x0040A770
long __fastcall Audio_DS_Volume_Attenuation(int volume);                                    // 0x0040A820
void Audio_DS_Stop_Primary();                                                               // 0x0040A860
void Audio_DS_Restart_Primary();                                                            // 0x0040A870

// Runs the device's update with the eight global level sets updated
// (0x0040A8C0; 0x00403810 jumps through the device's +0x10C).
void __fastcall Audio_Run_With_Levels_Updated(AudioDevice *device);                        // 0x0040A8C0

short __fastcall Audio_Adpcm_Decode(unsigned char code, AudioAdpcmState *state);            // 0x0040ABF0

// Globals.
extern AudioDriverInfo *Audio_Default_Driver;           // 0x007CCFDC
extern int Audio_Is_On;                                 // 0x0083143C
int __fastcall Audio_Init(int enable);                  // 0x00406AD0
extern AudioBag *Audio_Main_Bag;                        // 0x00831434
extern AudioDevice *Audio_Main_Device;                  // 0x00831438
extern int Audio_Update_Busy;                           // 0x0083146C
extern __int64 Audio_Update_Last;                       // 0x00831470 tick of the last update

AudioDevice *Audio_Get_Device();                        // 0x00406F40 (returns the device at 0x00831438)
extern AudioSystem *Audio_System_Instance;             // 0x007CC968
extern int Audio_unknown_830b48;                        // 0x00830B48
extern int Audio_Initialized;                           // 0x00830B4C
extern AudioLevelSet *Audio_Master_Levels;              // 0x00830B50 &Audio_System_Instance->Levels
extern AudioLevelSet Audio_Level_Set_830fd8;            // 0x00830FD8 the sets Audio_Global_Levels points at
extern AudioLevelSet Audio_Level_Set_831058;            // 0x00831058
extern AudioLevelSet Audio_Level_Set_8310d8;            // 0x008310D8
extern AudioLevelSet Audio_Level_Set_831168;            // 0x00831168
extern AudioLevelSet Audio_Level_Set_8311f8;            // 0x008311F8
extern AudioLevelSet Audio_Level_Set_831290;            // 0x00831290
extern AudioLevelSet Audio_Level_Set_831310;            // 0x00831310
extern AudioLevelSet Audio_Level_Set_8313b0;            // 0x008313B0
extern AudioLevelSet *Audio_Global_Levels[8];           // 0x0083144C
// Pause and resume every playing channel (0x00406E40, 0x00406E70; the game's pause
// counter 0x0065C1F0 / 0x0065C310 brackets them).
void Audio_Pause_All();
void Audio_Resume_All();
extern AudioThreadBlock Audio_Thread;                   // 0x00831560
extern int volatile Audio_Thread_Users;                 // 0x00831588
extern int Audio_Thread_Running;                        // 0x008315A8
extern CRITICAL_SECTION Audio_Lock;                     // 0x00831590
extern IDirectSound *Audio_DirectSound;                 // 0x008315AC
extern IDirectSoundBuffer *Audio_Primary_Buffer;        // 0x008315B0
extern long const Audio_Attenuation[101];               // 0x007CCE48 hundredths of a dB for 0..100%
extern int const Audio_Adpcm_Steps[89];                 // 0x007CD020
extern int const Audio_Adpcm_Index[16];                 // 0x007CCFE0
extern __int64 Audio_Ticks_Per_Ms;                      // 0x00831538
extern __int64 (*Audio_Clock)();                        // 0x00831558

DWORD __stdcall Audio_Thread_Proc(void *parameter);     // 0x004094D0
__int64 Audio_Counter_Clock();                          // 0x004092E0
__int64 Audio_System_Clock();                           // 0x00409310
extern int volatile Audio_Clock_Sequence;               // 0x0083155C bumped by every reader of the system clock
extern __int64 Audio_Clock_Time;                        // 0x007CCDE8 the extended timeGetTime (starts at 2^32)
extern unsigned long *const Audio_Clock_Low;            // 0x0079A750 &low word of Audio_Clock_Time
extern unsigned long *const Audio_Clock_High;           // 0x0079A754 &high word of Audio_Clock_Time

#endif
