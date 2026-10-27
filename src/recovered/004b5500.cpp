
class Leaf_4b5500 { public: unsigned int get(unsigned int a1); };
unsigned int Leaf_4b5500::get(unsigned int a1) { unsigned int ecx = (unsigned int)this; unsigned int eax; unsigned int edx; eax = *(unsigned int*)(ecx + 4); ecx = a1; eax = *(unsigned int*)(eax + ecx*4); return eax; }
