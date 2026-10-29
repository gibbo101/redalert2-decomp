// void __fastcall Emergency_Exit(int code) (0x00691310): ends the program with an exit code; its
// callers run the orderly shutdown 0x00691320 first (Red Alert's Emergency_Exit, split in two).
#include "shared/exit.hpp"
// @ref _exit=00784edc

void __fastcall Emergency_Exit(int code)
{
    exit(code);
}
