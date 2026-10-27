class Target_51b500 { public: unsigned int target(); };
class Leaf_51b500 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_51b500::get(unsigned int a1) { return ((Target_51b500*)(*(unsigned int*)((unsigned int)(this) + 4)))->target(); }
