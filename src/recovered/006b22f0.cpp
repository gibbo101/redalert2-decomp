
class Leaf_6b22f0 { public: unsigned char get(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4); };
unsigned char Leaf_6b22f0::get(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4) { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; eax = a1; if ((eax & eax) == 0) goto L6b2301; ecx = *(unsigned int*)(ecx + 0x74); *(unsigned int*)(eax + 0x554c) = ecx; L6b2301:; al = 1; return al; }
