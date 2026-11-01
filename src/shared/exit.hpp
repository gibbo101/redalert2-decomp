// Emergency_Exit: ends the program with an exit code (0x00691310 calls the
// CRT's exit; TechnoTypeClass::Read_INI calls it with -1 on a fatal rules
// error).
#ifndef RA2_SHARED_EXIT_HPP
#define RA2_SHARED_EXIT_HPP

void __fastcall Emergency_Exit(int code);                           // 0x00691310
// Posts the main window's WM_DESTROY (0x00691320; MixFileClass's constructor calls it before
// Emergency_Exit when no game disk can be found).
void Unknown_00691320();
// The CRT's exit (0x00784EDC; never returns).
extern "C" __declspec(noreturn) void __cdecl exit(int code);
// Red Alert's ReadyToQuit (0x00A40D80): 1 while the window procedure is quitting.
extern int ReadyToQuit;
// The application object's active-object registration (0x007F4CCC, -1 when none).
extern unsigned long unknown_active_object_7f4ccc;
// A block freed on exit while its flag is set (0x00ABD488, flag 0x00ABD48C).
extern void *unknown_block_abd488;
extern bool unknown_flag_abd48c;

#endif
