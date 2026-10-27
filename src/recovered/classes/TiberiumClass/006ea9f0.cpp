extern "C" void __cdecl release_6ea9f0(void*);
class Leaf_6ea9f0 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_6ea9f0::get(unsigned int flags) { cleanup(); if (flags & 1) release_6ea9f0(this); return this; }
