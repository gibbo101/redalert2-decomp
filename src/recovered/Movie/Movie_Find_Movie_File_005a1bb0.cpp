// bool __fastcall Find_Movie_File(char const *name, char *found, int unused) (0x005A1BB0)
// Cuts the name at its extension, unlocks the movie in the options, then looks for "<name>.BIK" and, failing
// that, "<name>.VQA"; copies the name found into found when given.
#include "shared/movie.hpp"
#include "shared/options.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/crt_string.hpp"
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?Unlock_Movie@OptionsClass@@QAEXPBD@Z=005da3f0
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50

bool __fastcall Find_Movie_File(char const *name, char *found, int unused)
{
    char filename[200];

    strcpy(filename, name);
    char *extension = filename;
    while (*extension != '\0' && *extension != '.') {
        extension++;
    }
    *extension = '\0';
    Options.Unlock_Movie(filename);

    strcpy(extension, ".BIK");
    if (CCFileClass(filename).Is_Available()) {
        if (found != 0) {
            strcpy(found, filename);
        }
        return true;
    }
    strcpy(extension, ".VQA");
    if (CCFileClass(filename).Is_Available()) {
        if (found != 0) {
            strcpy(found, filename);
        }
        return true;
    }
    return false;
}
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_C@_04HJCD@?4BIK?$AA@=007d9d74
// @ref ??_C@_04MOHI@?4VQA?$AA@=007d9d7c
