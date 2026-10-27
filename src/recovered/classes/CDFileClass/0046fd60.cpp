class Call_46fd60_0 {public: unsigned int target();};
extern "C" unsigned char data_46fd60_79a658[];
class Call_46fd60_1 {public: unsigned int target();};
class Call_46fd60_2 {public: unsigned int target(unsigned int p0);};
class Leaf_46fd60 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_46fd60::get(unsigned int a1) { unsigned int r0 = ((Call_46fd60_0*)((unsigned int)this))->target(); *(unsigned char*)(((unsigned int)this) + 0x50) = 0; *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_46fd60_79a658; unsigned int r1 = ((Call_46fd60_1*)(a1))->target(); unsigned int r2 = ((Call_46fd60_2*)((unsigned int)this))->target((unsigned int)(r1)); return (unsigned int)this; }
