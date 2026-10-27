class Target_499a20 { public: unsigned int target(unsigned int p0, unsigned int p1); };
class Leaf_499a20 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_499a20::get(unsigned int a1, unsigned int a2) { return ((Target_499a20*)(this))->target((unsigned int)(a1), (unsigned int)(a2)); }
