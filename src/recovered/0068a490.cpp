
class Leaf_68a490 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_68a490::get(unsigned int a1) { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; eax = a1; edx = *(unsigned int*)(ecx + 0x68); if (eax == edx) goto L68a49e; *(unsigned int*)(ecx + 0x6c) = eax; L68a49e:; return eax; }
