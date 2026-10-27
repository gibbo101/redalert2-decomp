class Call_7302e0_0 {public: unsigned int target();};
extern "C" unsigned char data_7302e0_7af27c[];
class Call_7302e0_1 {public: unsigned int target(unsigned int p0);};
class Leaf_7302e0 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_7302e0::get(unsigned int a1) { unsigned int r0 = ((Call_7302e0_0*)((unsigned int)this))->target(); *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_7302e0_7af27c; unsigned int r1 = ((Call_7302e0_1*)((unsigned int)this))->target((unsigned int)(*(unsigned int*)((a1) + 4))); return (unsigned int)this; }
