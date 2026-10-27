class Target_51b320 { public: unsigned int target(); };
class Leaf_51b320 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_51b320::get(unsigned int a1) { return ((Target_51b320*)(*(unsigned int*)((unsigned int)(this) + 4)))->target(); }
