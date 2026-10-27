extern "C" void __cdecl release_766780(void*);
class Leaf_766780 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_766780::get(unsigned int flags) { cleanup(); if (flags & 1) release_766780(this); return this; }
