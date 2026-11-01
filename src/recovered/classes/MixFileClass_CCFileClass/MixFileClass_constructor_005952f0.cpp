// MixFileClass<T>::MixFileClass(char const *filename, PKey const *key) (0x005952F0)
// TibSun mixfile.cpp: makes sure a disk is present, opens the archive, reads the (optionally
// Blowfish/PK encrypted) header and index, notes where the member data starts and links the
// archive at the tail of MixList.
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/file_straw.hpp"
#include "shared/pk_straw.hpp"
#include "shared/cd.hpp"
#include "shared/exit.hpp"

extern "C" char *__cdecl _strdup(char const *string);
extern "C" void *__cdecl memmove(void *dest, void const *src, unsigned int count);

#pragma pack(1)
struct MixFileHeader {
    short count;
    long size;
};
struct MixFileAlternate {
    short First;
    unsigned IsDigest : 1;
    unsigned IsEncrypted : 1;
};
#pragma pack()

template <class T>
MixFileClass<T>::MixFileClass(char const *filename, PKey const *key) :
    Filename(0),
    IsDigest(false),
    IsEncrypted(false),
    IsAllocated(false),
    Count(0),
    DataSize(0),
    DataStart(0),
    HeaderBuffer(0),
    Data(0)
{
    if (!CD().Force_Available(CD::RequiredCD)) {
        Unknown_00691320();
        Emergency_Exit(1);
    }

    T file(filename);
    Filename = _strdup(file.File_Name());
    FileStraw fstraw(file);
    PKStraw pstraw(PKStraw::DECRYPT, CryptRandom);
    Straw *straw = &fstraw;

    if (!file.Is_Available()) return;

    MixFileHeader fileheader;
    MixFileAlternate alternate;

    straw->Get(&alternate, 4);

    if (alternate.First == 0) {
        IsDigest = alternate.IsDigest;
        IsEncrypted = alternate.IsEncrypted;
        if (IsEncrypted) {
            pstraw.Key(key);
            pstraw.Get_From(&fstraw);
            straw = &pstraw;
        }
        straw->Get(&fileheader, sizeof(fileheader));
    } else {
        memmove(&fileheader, &alternate, 4);
        straw->Get(((char *)&fileheader) + 4, sizeof(fileheader) - 4);
    }

    Count = fileheader.count;
    DataSize = fileheader.size;

    HeaderBuffer = new SubBlock[Count];
    if (!HeaderBuffer) return;

    straw->Get(HeaderBuffer, Count * sizeof(SubBlock));

    DataStart = file.Seek(0, FILE_SEEK_CURRENT) + file.BiasStart;

    MixList.Add_Tail(this);
}

// @ref ??_GBlowfishEngine@@QAEPAXI@Z=00595c40
// @ref ?Unlink@GenericNode@@QAEXXZ=00595bc0
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??0PKStraw@@QAE@W4CryptControl@0@AAVRandomStraw@@@Z=0060fe30
// @ref ??1BlowfishEngine@@QAE@XZ=004355f0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??1FileStraw@@UAE@XZ=00773900
// @ref ??1Straw@@UAE@XZ=0069b010
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7?$MixFileClass@VCCFileClass@@@@6B@=007a6470
// @ref ??_7BlowStraw@@6B@=007a6460
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CD@@6B@=0079d868
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_7FileStraw@@6B@=0079d9ac
// @ref ?CryptRandom@@3VRandomStraw@@A=00a40778
// @ref ?Emergency_Exit@@YIXH@Z=00691310
// @ref ?Get_From@PKStraw@@UAEXPAVStraw@@@Z=0060fea0
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Key@PKStraw@@QAEXPBVPKey@@@Z=0060fef0
// @ref ?MixList@?$MixFileClass@VCCFileClass@@@@2V?$List@PAV?$MixFileClass@VCCFileClass@@@@@@A=00a70cc0
// @ref ?RequiredCD@CD@@2HA=007d20e0
// @ref ?Seek@CCFileClass@@UAEJJH@Z=004690f0
// @ref ?Unknown_00691320@@YAXXZ=00691320
// @ref __strdup=0078d816
// @ref _memmove=00783290
