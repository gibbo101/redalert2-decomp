class Call_437b90_0 {public: unsigned int target(unsigned int p0);};
extern "C" unsigned int global_437b90_a40d2c;
class Call_437b90_1 {public: unsigned int target(unsigned int p0);};
class Leaf_437b90 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_437b90::get(unsigned int a1) { unsigned int r0 = ((Call_437b90_0*)((unsigned int)this))->target((unsigned int)(a1)); unsigned int r1 = ((Call_437b90_1*)(a1))->target((unsigned int)((global_437b90_a40d2c - *(unsigned int*)(((unsigned int)this) + 0x30)))); return r1; }
