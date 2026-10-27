class Call_601410_0 {public: unsigned int target();};
class Call_601410_1 {public: unsigned int target();};
class Leaf_601410 { public: unsigned int get(); };
unsigned int Leaf_601410::get() { unsigned int r0 = ((Call_601410_0*)(((unsigned int)this) + 8))->target(); unsigned int r1 = ((Call_601410_1*)(((unsigned int)this) + 4))->target(); return r1; }
