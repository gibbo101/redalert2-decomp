
class Leaf_401170 { public: void get(); };
void Leaf_401170::get() { unsigned int ecx = (unsigned int)this; unsigned int eax; unsigned int edx; edx = *(unsigned int*)(ecx); eax = 0xfffffffd; edx = (edx) & (eax); *(unsigned int*)(ecx) = edx; edx = *(unsigned int*)(ecx + 0x50); edx = (edx) & (eax); *(unsigned int*)(ecx + 0x50) = edx; edx = *(unsigned int*)(ecx + 0x28); edx = (edx) & (eax); *(unsigned int*)(ecx + 0x28) = edx; }
