
class Leaf_6e8590 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_6e8590::get(unsigned int a1) { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; eax = a1; if ((int)(eax) < (int)(0xff)) goto L6e85a0; eax = 0xff; L6e85a0:; *(unsigned int*)(ecx + 0xc) = eax; return eax; }
