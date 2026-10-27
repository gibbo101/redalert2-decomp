
class Leaf_7399d0 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_7399d0::get(unsigned int a1) { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; eax = a1; edx = *(unsigned int*)(ecx + 0x20); if (eax == edx) goto L7399e2; *(unsigned int*)(ecx + 0x20) = eax; *(unsigned char*)(ecx + 8) = 1; L7399e2:; return eax; }
