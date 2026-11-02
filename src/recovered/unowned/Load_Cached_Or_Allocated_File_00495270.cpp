#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
void *__fastcall Load_Alloc_Data(FileClass &file);
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
void const *__fastcall Unknown_Load_Shape_00495270(char const *filename, bool &allocated)
{
    allocated = false;
    void const *cached = MixFileClass::Retrieve(filename);
    if (cached) return cached;
    CCFileClass file(filename);
    void *buffer = Load_Alloc_Data(file);
    allocated = buffer != 0;
    return buffer;
}
