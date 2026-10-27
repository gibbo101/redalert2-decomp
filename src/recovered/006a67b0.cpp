
class Leaf_6a67b0 { public: void get(unsigned int a1); };
void Leaf_6a67b0::get(unsigned int a1) { unsigned int ecx = (unsigned int)this; unsigned int eax; unsigned int edx; eax = a1; edx = *(unsigned int*)(ecx + 0xd64); *(unsigned int*)(eax) = edx; ecx = *(unsigned int*)(ecx + 0xd68); *(unsigned int*)(eax + 4) = ecx; }
