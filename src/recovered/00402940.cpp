extern "C" unsigned int global_402940_7cc968;
class Call_402940_0 {public: unsigned int target();};
class Call_402940_1 {public: unsigned int target();};
extern "C" unsigned int global_402940_830b50;
class Call_402940_2 {public: unsigned int target();};
extern "C" unsigned int global_402940_830b4c;
class Leaf_402940 { public: unsigned int get(); };
unsigned int Leaf_402940::get() { unsigned int r0 = ((Call_402940_0*)(global_402940_7cc968))->target(); unsigned int r1 = ((Call_402940_1*)((global_402940_7cc968) + 0xc))->target(); *(unsigned int*)((global_402940_7cc968) + 0x18) = 0; global_402940_830b50 = (global_402940_7cc968) + 0x20; unsigned int r2 = ((Call_402940_2*)((global_402940_7cc968) + 0x20))->target(); global_402940_830b4c = 1; return 0; }
