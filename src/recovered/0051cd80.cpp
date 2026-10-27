class Target_51cd80 { public: unsigned int target(); };
class Leaf_51cd80 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_51cd80::get(unsigned int a1) { return ((Target_51cd80*)(this))->target(); }
