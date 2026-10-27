class Target_675400 { public: unsigned int target(unsigned int p0); };
class Leaf_675400 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_675400::get(unsigned int a1) { return ((Target_675400*)((this + 0x10)))->target((unsigned int)(a1)); }
