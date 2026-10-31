// Westwood's JSHELL.CPP helpers in RA2 (unit 0x0052EE00-0x0052EF69, fastcall): the packed bit
// array accessors BooleanVectorClass uses (shared/boolean_vector.hpp). A bit index is signed:
// byte bit / 8, mask 1 << (bit % 8).
#ifndef RA2_SHARED_JSHELL_HPP
#define RA2_SHARED_JSHELL_HPP

void __fastcall Set_Bit(void *array, int bit, int value);  // 0x0052EE40
int __fastcall Get_Bit(void const *array, int bit);        // 0x0052EE90
int __fastcall First_True_Bit(void const *array);          // 0x0052EED0
int __fastcall First_False_Bit(void const *array);         // 0x0052EF20

#endif
