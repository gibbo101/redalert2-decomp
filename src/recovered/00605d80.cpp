class Call_605d80_0 {public: unsigned int target(unsigned int p0);};
class Leaf_605d80 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_605d80::get(unsigned int a1, unsigned int a2) { unsigned int r0 = ((Call_605d80_0*)((unsigned int)this))->target((unsigned int)(a1)); *(unsigned int*)(((unsigned int)this) + 0x100) = *(unsigned int*)((a2)); return (unsigned int)this; }
