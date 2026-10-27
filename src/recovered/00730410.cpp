
class Leaf_730410 { public: unsigned int get(); };
unsigned int Leaf_730410::get() { unsigned int ecx = (unsigned int)this; unsigned int eax; unsigned int edx; eax = ecx; *(unsigned int*)(eax + 8) = (*(unsigned int*)(eax + 8)) + 1; return eax; }
