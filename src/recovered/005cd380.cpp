extern "C" unsigned char data_5cd380_7e740c[];
extern "C" unsigned char data_5cd380_7dbce4[];
extern "C" unsigned char data_5cd380_839740[];
class Call_5cd380_0 {public: unsigned int target(unsigned int p0, unsigned int p1, unsigned int p2);};
extern "C" unsigned int global_5cd380_a72c68;
class Leaf_5cd380 { public: unsigned int get(); };
unsigned int Leaf_5cd380::get() { unsigned int r0 = ((Call_5cd380_0*)((unsigned int)data_5cd380_839740))->target((unsigned int)((unsigned int)data_5cd380_7dbce4), (unsigned int)((unsigned int)data_5cd380_7e740c), (unsigned int)(0)); global_5cd380_a72c68 = r0; return r0; }
