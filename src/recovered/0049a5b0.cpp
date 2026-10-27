class Call_49a5b0_0 {public: unsigned int target(unsigned int p0, unsigned int p1, unsigned int p2);};
class Call_49a5b0_1 {public: unsigned int target();};
class Leaf_49a5b0 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_49a5b0::get(unsigned int a1, unsigned int a2) { unsigned int r0 = ((Call_49a5b0_0*)((unsigned int)this))->target((unsigned int)(a1), (unsigned int)(a2), (unsigned int)(0)); unsigned int r1 = ((Call_49a5b0_1*)(r0))->target(); return r1; }
