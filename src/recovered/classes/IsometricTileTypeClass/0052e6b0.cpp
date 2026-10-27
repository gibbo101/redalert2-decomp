extern "C" void __cdecl release_52e6b0(void*);
class Leaf_52e6b0 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_52e6b0::get(unsigned int flags) { cleanup(); if (flags & 1) release_52e6b0(this); return this; }
