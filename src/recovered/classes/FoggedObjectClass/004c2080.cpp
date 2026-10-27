extern "C" void __cdecl release_4c2080(void*);
class Leaf_4c2080 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_4c2080::get(unsigned int flags) { cleanup(); if (flags & 1) release_4c2080(this); return this; }
