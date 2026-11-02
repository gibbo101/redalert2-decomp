// MixFileClass: mixfile archives (packed game files), read through file
// class T (CCFileClass in RA2).
//
// Every constructed archive links itself into the static list MixList
// (0x00A70CC0, a List of MixFileClass *). A mixfile starts with a header
// of Count SubBlock records sorted by the CRC of the upper-cased member name;
// Offset() binary-searches each registered archive in list order. An archive
// may be cached: Data then holds its body (owned when IsAllocated), and
// member pointers come straight from memory.
//
// Layout (0x28 bytes, offsets observed in the code at 0x005952F0-0x00595AA0):
//   +0x00 Node<MixFileClass *>  vtable 0x007A6470, NextNode, PrevNode
//   +0x0C char const *Filename     archive file name (_strdup, freed with free)
//   +0x10 bool IsDigest            header is followed by a SHA digest
//   +0x11 bool IsEncrypted         header is Blowfish encrypted
//   +0x12 bool IsAllocated         Data was allocated by Cache()
//   +0x14 int Count                number of SubBlock records
//   +0x18 long DataSize            size of the member data
//   +0x1C long DataStart           file offset of the member data
//   +0x20 SubBlock *HeaderBuffer   the sorted index (operator new)
//   +0x24 void *Data               cached member data, or null
// Field names other than Filename follow Westwood's mixfile vocabulary and
// were checked against behaviour only. The constructor (0x005952F0) and
// Cache(Buffer const *) (0x00595810) are declared but not yet recovered.
//
// The list classes come from shared/ini_class.hpp (GenericNode, Node, List);
// they belong in a shared list header of their own.
#ifndef RA2_SHARED_MIX_FILE_CLASS_HPP
#define RA2_SHARED_MIX_FILE_CLASS_HPP

#include "shared/ini_class.hpp"

class Buffer;
class PKey;

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname,
                                  char const *ext);
extern "C" int __cdecl _stricmp(char const *left, char const *right);
extern "C" char *__cdecl _strupr(char *string);

class MixFileClass : public Node<MixFileClass *> {
public:
    // One index record: member name CRC (named ID for Binary_Search), member
    // offset from DataStart and member size.
    struct SubBlock {
        long ID;        // +0x00 CRC of the upper-cased name
        long Offset;    // +0x04
        long Size;      // +0x08
    };

    MixFileClass(char const *filename, PKey const *key);   // 0x005952F0
    ~MixFileClass();                                        // 0x00595620

    // qsort/bsearch order of SubBlock records (signed CRC compare).
    static int Compare_Blocks(void const *left, void const *right);   // 0x005952D0
    // Releases the cache of the named archive; false when not registered.
    static bool __fastcall Free(char const *filename);                 // 0x00595560
    // Data pointer of a member of a cached archive, else null.
    static void const *__fastcall Retrieve(char const *filename);      // 0x005956C0
    // Registered archive whose file name (name and extension only) matches.
    static MixFileClass *__fastcall Finder(char const *filename);      // 0x005956E0
    // Caches the named archive (see Cache below).
    static bool __fastcall Cache(char const *filename, Buffer const *buffer = 0);  // 0x00595770
    // Finds filename in the registered mixfiles. On success fills the
    // optional outputs: realptr (the data when the mixfile is cached in
    // memory), mixfile (the containing archive), offset (member start in the
    // archive file) and size (member size).
    static bool __fastcall Offset(char const *filename, void **realptr = 0, MixFileClass **mixfile = 0,
                                  long *offset = 0, long *size = 0);  // 0x00595AA0

    bool Cache(Buffer const *buffer = 0);                   // 0x00595810
    void Free();                                            // 0x00595A70

    char const *Filename;       // +0x0C name of the archive file
    bool IsDigest;              // +0x10
    bool IsEncrypted;           // +0x11
    bool IsAllocated;           // +0x12
    int Count;                  // +0x14
    long DataSize;              // +0x18
    long DataStart;             // +0x1C
    SubBlock *HeaderBuffer;     // +0x20
    void *Data;                 // +0x24

    // The declaration of this class-type static member takes one of VC6's generated-name numbers
    // in every unit that includes this header (renumbering later _$E initializers), so only units
    // that use mixfiles include it.
    static List<MixFileClass *> MixList;                 // 0x00A70CC0
};

#endif
