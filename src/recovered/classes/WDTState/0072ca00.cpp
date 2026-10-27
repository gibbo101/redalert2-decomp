extern "C" void __cdecl release_72ca00(void*);
class Leaf_72ca00 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_72ca00::get(unsigned int flags) { cleanup(); if (flags & 1) release_72ca00(this); return this; }
