extern "C" unsigned char data_7395b0_7af554[];
class Call_7395b0_0 {public: unsigned int target();};
class Call_7395b0_1 {public: unsigned int target();};
class Leaf_7395b0 { public: unsigned int get(); };
unsigned int Leaf_7395b0::get() { *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_7395b0_7af554; unsigned int r0 = ((Call_7395b0_0*)(((unsigned int)this) + 0xc))->target(); unsigned int r1 = ((Call_7395b0_1*)((unsigned int)this))->target(); return r1; }
