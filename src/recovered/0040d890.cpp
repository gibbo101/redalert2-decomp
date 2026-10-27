extern "C" unsigned char data_40d890_839010[];
class Call_40d890_0 {public: unsigned int __fastcall target(unsigned int registerArg, unsigned int p0);};
extern "C" unsigned char data_40d890_839110[];
class Call_40d890_1 {public: unsigned int __fastcall target(unsigned int registerArg, unsigned int p0);};
extern "C" unsigned int global_40d890_839210;
class Leaf_40d890 { public: unsigned int get(); };
unsigned int Leaf_40d890::get() { unsigned int r0 = ((Call_40d890_0*)((unsigned int)data_40d890_839010))->target((unsigned int)(0), (unsigned int)(0x40)); unsigned int r1 = ((Call_40d890_1*)((unsigned int)data_40d890_839110))->target((unsigned int)(0), (unsigned int)(0x40)); global_40d890_839210 = 0; return r1; }
