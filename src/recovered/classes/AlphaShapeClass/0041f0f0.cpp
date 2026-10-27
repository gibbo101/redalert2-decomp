
class Leaf_41f0f0 { public: unsigned int get(unsigned int a1, unsigned int a2); };
unsigned int Leaf_41f0f0::get(unsigned int a1, unsigned int a2) { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; eax = a1; edx = *(unsigned int*)(ecx + 0x24); if (eax != edx) goto L41f0ff; *(unsigned char*)(ecx + 0x3c) = 1; L41f0ff:; return eax; }
