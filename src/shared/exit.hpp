// Emergency_Exit: ends the program with an exit code (0x00691310 calls the
// CRT's exit; TechnoTypeClass::Read_INI calls it with -1 on a fatal rules
// error).
#ifndef RA2_SHARED_EXIT_HPP
#define RA2_SHARED_EXIT_HPP

void __fastcall Emergency_Exit(int code);                           // 0x00691310

#endif
