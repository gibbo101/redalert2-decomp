extern "C" unsigned int global_6bc210_a35db4;
class Call_6bc210_0 {public: unsigned int target(unsigned int p0);};
class Leaf_6bc210 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_6bc210::get(unsigned int a1, unsigned int a2) { unsigned int r0 = ((Call_6bc210_0*)(global_6bc210_a35db4))->target((unsigned int)(0)); *(unsigned char*)(((unsigned int)this) + 0x80) = 1; return r0; }
