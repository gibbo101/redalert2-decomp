class Call_4de1e0_0 {public: unsigned int target();};
class Leaf_4de1e0 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_4de1e0::get(unsigned int a1) { unsigned int r0 = ((Call_4de1e0_0*)(((unsigned int)this) + 4))->target(); *(unsigned int*)(((unsigned int)this)) = r0; *(unsigned int*)(((unsigned int)this) + 8) = a1; return (unsigned int)this; }
