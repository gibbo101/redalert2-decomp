class Target_630300 { public: unsigned int target(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3); };
class Leaf_630300 { public: unsigned int get(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4); };
unsigned int Leaf_630300::get(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4) { return ((Target_630300*)(this))->target((unsigned int)(a1), (unsigned int)(a2), (unsigned int)(a3), (unsigned int)(a4)); }
