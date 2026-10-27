extern "C" unsigned int global_402c00_7cc968;
class Call_402c00_0 {public: unsigned int target();};
class Leaf_402c00 { public: unsigned int get(); };
unsigned int Leaf_402c00::get() { unsigned int r0 = ((Call_402c00_0*)(global_402c00_7cc968))->target(); *(unsigned int*)(((unsigned int)this)) = r0; return r0; }
