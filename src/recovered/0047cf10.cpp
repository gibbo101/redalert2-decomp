
class Leaf_47cf10 { public: unsigned int get(); };
unsigned int Leaf_47cf10::get() { unsigned int ecx = (unsigned int)this; unsigned int eax; unsigned int edx; eax = *(unsigned int*)(ecx + 0x140); ecx = *(signed char*)(ecx + 0x11b); eax = (eax) >> (7); eax = (eax) & (1); eax = ecx + eax*4; return eax; }
