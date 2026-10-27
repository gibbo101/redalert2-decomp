extern "C" unsigned char data_6bc590_8324e0[];
class Call_6bc590_0 {public: unsigned int target();};
class Leaf_6bc590 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_6bc590::get(unsigned int a1, unsigned int a2) { unsigned int r0 = ((Call_6bc590_0*)((unsigned int)data_6bc590_8324e0))->target(); *(unsigned char*)(((unsigned int)this) + 0x80) = 1; return r0; }
