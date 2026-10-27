class Target_5a3f70 { public: unsigned int target(unsigned int p0, unsigned int p1); };
class Leaf_5a3f70 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_5a3f70::get(unsigned int a1, unsigned int a2) { return ((Target_5a3f70*)(this))->target((unsigned int)(a1), (unsigned int)(a2)); }
