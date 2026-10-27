class Call_765aa0_0 {public: unsigned int target();};
extern "C" unsigned char data_765aa0_7af6f4[];
class Call_765aa0_1 {public: unsigned int target();};
extern "C" unsigned char data_765aa0_7af934[];
class Leaf_765aa0 { public: unsigned int get(); };
unsigned int Leaf_765aa0::get() { unsigned int r0 = ((Call_765aa0_0*)((unsigned int)this))->target(); *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_765aa0_7af6f4; unsigned int r1 = ((Call_765aa0_1*)(((unsigned int)this) + 0xc))->target(); *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_765aa0_7af934; return (unsigned int)this; }
