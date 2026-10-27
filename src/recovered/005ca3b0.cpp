
class Leaf_5ca3b0 { public: unsigned int get(); };
unsigned int Leaf_5ca3b0::get() { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; ecx = *(unsigned int*)(ecx*4 + 0xa3fa98); eax = 0; if ((ecx & ecx) == 0) goto L5ca3d5; if (ecx == *(unsigned int*)(0xa72d34)) goto L5ca3db; if (ecx == *(unsigned int*)(0xa72d38)) goto L5ca3db; if (ecx == *(unsigned int*)(0xa72d3c)) goto L5ca3db; L5ca3d5:; if (*(unsigned int*)(ecx + 0x67) != 1) goto L5ca3e0; L5ca3db:; eax = 1; L5ca3e0:; return eax; }
