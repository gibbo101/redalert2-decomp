class Target_51af60 { public: unsigned int target(); };
class Leaf_51af60 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_51af60::get(unsigned int a1) { return ((Target_51af60*)(*(unsigned int*)((unsigned int)(this) + 4)))->target(); }
