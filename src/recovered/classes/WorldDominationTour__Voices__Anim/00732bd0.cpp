class Target_732bd0 { public: unsigned int target(); };
class Leaf_732bd0 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_732bd0::get(unsigned int a1, unsigned int a2) { return ((Target_732bd0*)(*(unsigned int*)((unsigned int)(this) + 0x1c)))->target(); }
