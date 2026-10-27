extern "C" void __cdecl release_5a62b0(void*);
class Leaf_5a62b0 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_5a62b0::get(unsigned int flags) { cleanup(); if (flags & 1) release_5a62b0(this); return this; }
