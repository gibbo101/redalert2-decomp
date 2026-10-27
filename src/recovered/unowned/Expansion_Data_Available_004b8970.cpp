#include "shared/cc_file_class.hpp"
extern char const expansion_data_name_007d7eac[];
// @ref ?expansion_data_name_007d7eac@@3QBDB=007d7eac
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// No direct callers found; no-argument fastcall convention is an exact-code hypothesis.
bool __fastcall Expansion_Data_Available_004b8970()
{
    CCFileClass file(expansion_data_name_007d7eac);
    return file.Is_Available(0);
}
