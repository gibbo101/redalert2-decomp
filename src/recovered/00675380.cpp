class Call_675380_0 {public: unsigned int target(unsigned int p0, unsigned int p1);};
class Call_675380_1 {public: unsigned int target(unsigned int p0, unsigned int p1);};
class Leaf_675380 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_675380::get(unsigned int a1, unsigned int a2) { unsigned int r0 = ((Call_675380_0*)(((unsigned int)this) + 0xc))->target((unsigned int)(a1), (unsigned int)(a2)); unsigned int r1 = ((Call_675380_1*)((unsigned int)this))->target((unsigned int)(a1), (unsigned int)(a2)); return r1; }
