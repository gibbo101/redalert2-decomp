extern "C" unsigned char data_7273c0_7af07c[];
extern "C" unsigned char data_7273c0_7a452c[];
class Call_7273c0_0 {public: unsigned int target();};
class Call_7273c0_1 {public: unsigned int target();};
class Leaf_7273c0 { public: unsigned int get(); };
unsigned int Leaf_7273c0::get() { *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_7273c0_7af07c; *(unsigned int*)((((unsigned int)this) + 8)) = (unsigned int)data_7273c0_7a452c; unsigned int r0 = ((Call_7273c0_0*)(((unsigned int)this) + 8))->target(); unsigned int r1 = ((Call_7273c0_1*)((unsigned int)this))->target(); return r1; }
