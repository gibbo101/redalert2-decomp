
class Leaf_66e2b0 { public: unsigned int get(); };
unsigned int Leaf_66e2b0::get() { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; edx = *(unsigned int*)(ecx + 0x57); eax = 0xfffffffe; if (edx != eax) goto L66e2c2; if (*(unsigned int*)(ecx + 0x53) == -1) goto L66e2c5; L66e2c2:; eax = *(unsigned int*)(ecx + 0x53); L66e2c5:; return eax; }
