class Target_68ca20 { public: unsigned int target(unsigned int p0, unsigned int p1, unsigned int p2); };
class Leaf_68ca20 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_68ca20::get(unsigned int a1) { return ((Target_68ca20*)(this))->target((unsigned int)(a1), (unsigned int)(1), (unsigned int)(1)); }
