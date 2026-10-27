class Call_601780_0 {public: unsigned int target(unsigned int p0);};
class Call_601780_1 {public: unsigned int target(unsigned int p0);};
class Leaf_601780 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_601780::get(unsigned int a1) { *(unsigned int*)(((unsigned int)this)) = *(unsigned int*)((a1)); unsigned int r0 = ((Call_601780_0*)(((unsigned int)this) + 4))->target((unsigned int)((a1) + 4)); unsigned int r1 = ((Call_601780_1*)(((unsigned int)this) + 8))->target((unsigned int)((a1) + 8)); *(unsigned int*)(((unsigned int)this) + 0xc) = *(unsigned int*)((a1) + 0xc); *(unsigned int*)(((unsigned int)this) + 0x10) = *(unsigned int*)((a1) + 0x10); *(unsigned int*)(((unsigned int)this) + 0x14) = *(unsigned int*)((a1) + 0x14); return (unsigned int)this; }
