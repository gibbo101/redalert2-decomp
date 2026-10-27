
class Leaf_5394f0 { public: unsigned int get(); };
unsigned int Leaf_5394f0::get() { unsigned int ecx=(unsigned int)this, eax=0, edx=0; unsigned char al=0; eax = *(unsigned int*)(ecx + 4); edx = 0; if (eax == edx) goto L539502; *(unsigned int*)(eax + 0x94) = edx; *(unsigned int*)(ecx + 4) = edx; L539502:; return eax; }
