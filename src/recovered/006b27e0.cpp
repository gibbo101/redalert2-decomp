
class Leaf_6b27e0 { public: unsigned char get(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4); };
unsigned char Leaf_6b27e0::get(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4) { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; eax = *(unsigned int*)(ecx + 0x74); edx = *(unsigned int*)(0xa40abc); ecx = *(unsigned int*)(ecx + 0x48); eax = *(unsigned int*)(edx + eax*4); *(unsigned int*)(eax + 0x55c) = ecx; eax = a1; if ((eax & eax) == 0) goto L6b2804; *(unsigned char*)(eax + 0x144) = 1; L6b2804:; al = 1; return al; }
