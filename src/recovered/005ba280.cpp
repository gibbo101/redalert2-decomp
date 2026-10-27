extern "C" unsigned char data_5ba280_7e63ec[];
extern "C" unsigned char data_5ba280_7dbce4[];
extern "C" unsigned char data_5ba280_839740[];
class Call_5ba280_0 {public: unsigned int target(unsigned int p0, unsigned int p1, unsigned int p2);};
extern "C" unsigned char data_5ba280_7e63dc[];
class Call_5ba280_1 {public: unsigned int target(unsigned int p0, unsigned int p1, unsigned int p2);};
class Leaf_5ba280 { public: unsigned int get(); };
unsigned int Leaf_5ba280::get() { unsigned int r0 = ((Call_5ba280_0*)((unsigned int)data_5ba280_839740))->target((unsigned int)((unsigned int)data_5ba280_7dbce4), (unsigned int)((unsigned int)data_5ba280_7e63ec), (unsigned int)(0)); *(unsigned int*)(((unsigned int)this) + 4) = r0; unsigned int r1 = ((Call_5ba280_1*)((unsigned int)data_5ba280_839740))->target((unsigned int)((unsigned int)data_5ba280_7dbce4), (unsigned int)((unsigned int)data_5ba280_7e63dc), (unsigned int)(1)); *(unsigned int*)(((unsigned int)this) + 0xc) = r1; return r1; }
