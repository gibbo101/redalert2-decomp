#include "shared/compressed_file.hpp"
// @ref ?Load_Compressed_Data_004953b0=004953b0
int __fastcall Load_Compressed_Data_Scaled_00495520(FileClass &file, Buffer const &scratch, Buffer const &output, void *extra, int unknown_stack_0c)
{
    return Load_Compressed_Data_004953b0(file, scratch, output, extra) / 8000;
}
