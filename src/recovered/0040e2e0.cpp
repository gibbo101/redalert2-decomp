extern "C" void __cdecl release_40e2e0(void*);
class Leaf_40e2e0 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_40e2e0::get(unsigned int flags) { cleanup(); if (flags & 1) release_40e2e0(this); return this; }
