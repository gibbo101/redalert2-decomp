extern "C" unsigned char data_402190_4022c0[];
extern "C" unsigned char data_402190_402330[];
extern "C" unsigned char data_402190_4023f0[];
extern "C" unsigned int global_402190_830b50;
class Call_402190_0 {public: unsigned int target();};
class Leaf_402190 { public: unsigned int get(); };
unsigned int Leaf_402190::get() { *(unsigned int*)(((unsigned int)this) + 0x15c) = (unsigned int)data_402190_4022c0; *(unsigned int*)(((unsigned int)this) + 0x160) = (unsigned int)data_402190_402330; *(unsigned int*)(((unsigned int)this) + 0x164) = (unsigned int)data_402190_4023f0; *(unsigned int*)(((unsigned int)this) + 0xb0) = 0; *(unsigned int*)(((unsigned int)this) + 0xb4) = 0; *(unsigned int*)(((unsigned int)this) + 0xb8) = 0; *(unsigned int*)(((unsigned int)this) + 0xbc) = 0; *(unsigned int*)(((unsigned int)this) + 0xc0) = 0; *(unsigned int*)(((unsigned int)this) + 0xc) = 1; *(unsigned int*)(((unsigned int)this) + 0xa8) = 0; *(unsigned int*)(((unsigned int)this) + 0xa4) = 0; *(unsigned int*)(((unsigned int)this) + 0xa0) = 0; *(unsigned int*)(((unsigned int)this) + 0x94) = global_402190_830b50; *(unsigned int*)(((unsigned int)this) + 0x90) = 0; *(unsigned int*)(((unsigned int)this) + 0x98) = 0; *(unsigned int*)(((unsigned int)this) + 0x9c) = 0; unsigned int r0 = ((Call_402190_0*)(((unsigned int)this) + 0x10))->target(); *(unsigned int*)(((unsigned int)this) + 0x168) = 0; return r0; }
