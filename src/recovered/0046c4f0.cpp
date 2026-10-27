class Call_46c4f0_0 {public: unsigned int target();};
class Call_46c4f0_1 {public: unsigned int target(unsigned int p0, unsigned int p1, unsigned int p2);};
class Leaf_46c4f0 { public: unsigned int get(unsigned int a1, unsigned int a2, unsigned int a3); };
unsigned int Leaf_46c4f0::get(unsigned int a1, unsigned int a2, unsigned int a3) { unsigned int r0 = ((Call_46c4f0_0*)(a3))->target(); unsigned int r1 = ((Call_46c4f0_1*)((unsigned int)this))->target((unsigned int)(a1), (unsigned int)(a2), (unsigned int)(r0)); return r1; }
