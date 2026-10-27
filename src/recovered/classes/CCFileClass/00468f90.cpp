class Call_468f90_0 {public: unsigned int target();};
class Call_468f90_1 {public: unsigned int target(unsigned int p0, unsigned int p1);};
extern "C" unsigned char data_468f90_79a6a0[];
class Call_468f90_2 {public: unsigned int target();};
class Call_468f90_3 {public: unsigned int target(unsigned int p0);};
class Leaf_468f90 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_468f90::get(unsigned int a1) { unsigned int r0 = ((Call_468f90_0*)((unsigned int)this))->target(); unsigned int r1 = ((Call_468f90_1*)(((unsigned int)this) + 0x54))->target((unsigned int)(0), (unsigned int)(0)); *(unsigned int*)(((unsigned int)this) + 0x60) = 0; *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_468f90_79a6a0; unsigned int r2 = ((Call_468f90_2*)(a1))->target(); unsigned int r3 = ((Call_468f90_3*)((unsigned int)this))->target((unsigned int)(r2)); return (unsigned int)this; }
