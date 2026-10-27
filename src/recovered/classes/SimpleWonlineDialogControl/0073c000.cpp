class Call_73c000_0 {public: unsigned int target();};
extern "C" unsigned char data_73c000_7af6f4[];
class Leaf_73c000 { public: unsigned int get(); };
unsigned int Leaf_73c000::get() { unsigned int r0 = ((Call_73c000_0*)((unsigned int)this))->target(); *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_73c000_7af6f4; return (unsigned int)this; }
