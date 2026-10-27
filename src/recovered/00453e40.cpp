
class Leaf_453e40 { public: unsigned int get(unsigned int a1, unsigned int a2, unsigned int a3); };
unsigned int Leaf_453e40::get(unsigned int a1, unsigned int a2, unsigned int a3) { unsigned int ecx = (unsigned int)this; unsigned int eax; unsigned int edx; eax = ecx; ecx = a1; edx = *(unsigned int*)(ecx); *(unsigned int*)(eax) = edx; ecx = *(unsigned int*)(ecx + 4); edx = a2; *(unsigned int*)(eax + 4) = ecx; ecx = a3; *(unsigned int*)(eax + 8) = edx; *(unsigned int*)(eax + 0xc) = ecx; return eax; }
