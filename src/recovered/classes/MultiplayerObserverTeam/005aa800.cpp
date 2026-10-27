class Target_5aa800 { public: unsigned int target(unsigned int p0); };
class Leaf_5aa800 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_5aa800::get(unsigned int a1) { return ((Target_5aa800*)(this))->target((unsigned int)(a1)); }
