extern "C" void __cdecl release_59cb80(void*);
class Leaf_59cb80 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_59cb80::get(unsigned int flags) { cleanup(); if (flags & 1) release_59cb80(this); return this; }
