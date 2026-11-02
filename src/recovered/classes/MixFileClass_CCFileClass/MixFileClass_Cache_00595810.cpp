// bool MixFileClass::Cache(Buffer const *buffer) (0x00595810)
// TibSun mixfile.cpp: loads the archive's member data into memory (the caller's buffer when it is
// large enough, else an owned allocation touched every 4 KB), reads it through the file straw (and
// a SHA straw for a digested archive), and checks the digest that follows the data.
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/file_straw.hpp"
#include "shared/sha_straw.hpp"
#include "shared/crt_memory.hpp"
#include "shared/unknown_globals.hpp"

bool MixFileClass::Cache(Buffer const *buffer)
{
    if (Data != 0) return true;

    if (buffer != 0 && (buffer->Get_Size() == 0 || buffer->Get_Size() >= DataSize)) {
        Data = buffer->Get_Buffer();
    } else {
        Data = new char[DataSize];
        IsAllocated = true;
        for (char *i = (char *)Data; i < &((char *)Data)[DataSize]; i += 4096) {
            volatile char tmp = *i;
        }
        Service_Game_IO_00481fb0();
    }

    if (Data != 0) {
        CCFileClass file(Filename);
        FileStraw fstraw(file);
        Straw *straw = &fstraw;

        SHAStraw sha;
        if (IsDigest) {
            sha.Get_From(fstraw);
            straw = &sha;
        }

        file.Open(FILE_RIGHTS_READ);
        file.Bias(0);
        file.Bias(DataStart);

        int actual = straw->Get(Data, DataSize);
        if (actual != DataSize) {
            delete[] (char *)Data;
            Data = 0;
            file.Error(5);
            return false;
        }

        if (IsDigest) {
            char digest1[20];
            char digest2[20];
            sha.Result(digest2);
            fstraw.Get(digest1, sizeof(digest1));
            if (memcmp(digest1, digest2, sizeof(digest1)) != 0) {
                delete[] (char *)Data;
                Data = 0;
                return false;
            }
        }
        return true;
    }
    IsAllocated = false;
    return false;
}
// @ref ??0SHAEngine@@QAE@XZ=00595d10
// @ref ??_7SHAStraw@@6B@=007a6478
// @ref ?Result@SHAStraw@@QBEHPAX@Z=00675400
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??1FileStraw@@UAE@XZ=00773900
// @ref ??1Straw@@UAE@XZ=0069b010
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_7FileStraw@@6B@=0079d9ac
// @ref ??_7Straw@@6B@=0079e9f8
// @ref ?Bias@RawFileClass@@QAEXHH@Z=00639360
// @ref ?Error@CCFileClass@@UAEXHHPBD@Z=00469000
// @ref ?Get@FileStraw@@UAEHPAXH@Z=007738a0
// @ref ?Open@CCFileClass@@UAEHH@Z=00469220
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
