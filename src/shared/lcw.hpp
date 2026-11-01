// LCW: Westwood's LZ77-style block compression.
//
// LCW_Uncomp (0x00534B50) is Westwood's C decoder compiled __fastcall
// (source in ECX, destination in EDX, length on the stack; recovered).
// LCW_Comp (0x00534D40) is hand-written assembly with the same register
// convention, declared __fastcall so C++ callers reproduce the original
// call sites; its body is not a C++ recovery.
#ifndef RA2_SHARED_LCW_HPP
#define RA2_SHARED_LCW_HPP

// Decompresses an LCW stream; returns the bytes written to dest.
int __fastcall LCW_Uncomp(void const *source, void *dest, unsigned long length = 0);
// Compresses length bytes; returns the bytes written to dest.
int __fastcall LCW_Comp(void const *source, void *dest, int length);

#endif
