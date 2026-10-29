// Debug_Printf: the game's debug output function (an empty function in this build).
#ifndef RA2_SHARED_DEBUG_PRINTF_HPP
#define RA2_SHARED_DEBUG_PRINTF_HPP

void __cdecl Debug_Printf(char const *format, ...);     // 0x004068F0
// A loading-progress message (an empty function in this build; 0x00496460; Init_Bootstrap_Mixfiles
// passes " %s" and a file name, Unknown_0051A2B0 a plain text; name hypothesis).
void __cdecl Unknown_00496460(char const *format, ...);   // 0x00496460
// A nesting counter around focus changes: the first Unknown_00406F50 calls 0x0040A860, Unknown_00406F70
// counts down (Focus_Loss and Focus_Restore; names hypotheses).
void Unknown_00406F50();                                // 0x00406F50
void Unknown_00406F70();                                // 0x00406F70

#endif
