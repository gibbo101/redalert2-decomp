// int __fastcall Read_Line(FileClass &file, char *buffer, int len, bool &eof) (0x006395C0; Tiberian Sun readline.cpp): reads through a FileStraw (the Straw version expands inline).
#include "shared/reference_counted.hpp"
#include "shared/file_straw.hpp"
#include "shared/crt_string.hpp"

int __fastcall Read_Line(Straw &file, char *buffer, int len, bool &eof);

int __fastcall Read_Line(FileClass &file, char *buffer, int len, bool &eof)
{
    FileStraw fs(file);
    return Read_Line(fs, buffer, len, eof);
}
