
class Leaf_602a90 { public: void get(unsigned int a1); };
void Leaf_602a90::get(unsigned int a1) { unsigned int ecx = (unsigned int)this; unsigned int eax; unsigned int edx; eax = a1; edx = *(unsigned int*)(ecx + 4); *(unsigned int*)(eax + 0xc) = edx; *(unsigned int*)(ecx + 4) = eax; }
