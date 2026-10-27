// LCW: Westwood's LZ77-style block compression.
//
// LCW_Uncomp (0x00534B50) and LCW_Comp (0x00534D40) are hand-written
// assembly with a register calling convention (source in ECX, destination
// in EDX, length on the stack); they are declared __fastcall so C++ callers
// reproduce the original call sites. Their bodies are not C++ recoveries.
#ifndef RA2_SHARED_LCW_HPP
#define RA2_SHARED_LCW_HPP

// Decompresses an LCW stream; returns the bytes written to dest.
int __fastcall LCW_Uncomp(void const *source, void *dest, unsigned long length = 0);
// Compresses length bytes; returns the bytes written to dest.
int __fastcall LCW_Comp(void const *source, void *dest, int length);

#endif
