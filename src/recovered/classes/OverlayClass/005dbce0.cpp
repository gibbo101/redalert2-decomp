class Target_5dbce0 { public: unsigned int target(unsigned int p0, unsigned int p1, unsigned int p2); };
class Leaf_5dbce0 { public: unsigned int get(unsigned int a1, unsigned int a2, unsigned int a3); };
unsigned int Leaf_5dbce0::get(unsigned int a1, unsigned int a2, unsigned int a3) { return ((Target_5dbce0*)(a2))->target((unsigned int)(a1), (unsigned int)(a2), (unsigned int)(a3)); }
