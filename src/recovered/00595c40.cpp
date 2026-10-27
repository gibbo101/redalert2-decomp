extern "C" void __cdecl release_595c40(void*);
class Leaf_595c40 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_595c40::get(unsigned int flags) { cleanup(); if (flags & 1) release_595c40(this); return this; }
