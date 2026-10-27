class Target_732c20 { public: unsigned int target(); };
class Leaf_732c20 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_732c20::get(unsigned int a1) { return ((Target_732c20*)(*(unsigned int*)((unsigned int)(this) + 0x1c)))->target(); }
