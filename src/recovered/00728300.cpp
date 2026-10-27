class Call_728300_0 {public: unsigned int target();};
extern "C" unsigned char data_728300_7af0dc[];
class Call_728300_1 {public: unsigned int target(unsigned int p0);};
class Leaf_728300 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_728300::get(unsigned int a1) { unsigned int r0 = ((Call_728300_0*)((unsigned int)this))->target(); *(unsigned int*)(((unsigned int)this)) = (unsigned int)data_728300_7af0dc; unsigned int r1 = ((Call_728300_1*)((unsigned int)this))->target((unsigned int)(*(unsigned int*)((a1) + 4))); return (unsigned int)this; }
