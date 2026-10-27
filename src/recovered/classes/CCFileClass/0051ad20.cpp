extern "C" unsigned char data_51ad20_79a6a0[];
class Call_51ad20_0 {public: unsigned int target();};
extern "C" unsigned char data_51ad20_79a658[];
class Call_51ad20_1 {public: unsigned int target();};
class Leaf_51ad20 { public: unsigned int get(); };
unsigned int Leaf_51ad20::get() { *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_51ad20_79a6a0; *(unsigned int*)(((unsigned int)this) + 0x60) = 0; unsigned int r0 = ((Call_51ad20_0*)(((unsigned int)this) + 0x54))->target(); *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_51ad20_79a658; unsigned int r1 = ((Call_51ad20_1*)((unsigned int)this))->target(); return r1; }
