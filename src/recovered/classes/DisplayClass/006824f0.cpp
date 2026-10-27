class Call_6824f0_0 {public: unsigned int target(unsigned int p0);};
extern "C" unsigned char data_6824f0_79e91c[];
class Leaf_6824f0 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_6824f0::get(unsigned int a1) { unsigned int r0 = ((Call_6824f0_0*)((unsigned int)this))->target((unsigned int)(a1)); *(unsigned char*)(((unsigned int)this) + 0x11c8) = 0; *(unsigned char*)(((unsigned int)this) + 0x11c9) = 0; *(unsigned char*)(((unsigned int)this) + 0x11ca) = 0; *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_6824f0_79e91c; return (unsigned int)this; }
