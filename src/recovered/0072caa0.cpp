class Call_72caa0_0 {public: unsigned int target();};
extern "C" unsigned char data_72caa0_7a452c[];
class Call_72caa0_1 {public: unsigned int target(unsigned int p0);};
class Leaf_72caa0 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_72caa0::get(unsigned int a1) { unsigned int r0 = ((Call_72caa0_0*)((unsigned int)this))->target(); *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_72caa0_7a452c; unsigned int r1 = ((Call_72caa0_1*)((unsigned int)this))->target((unsigned int)(a1)); return (unsigned int)this; }
