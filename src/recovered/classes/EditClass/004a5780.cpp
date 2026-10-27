extern "C" void __cdecl release_4a5780(void*);
class Leaf_4a5780 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_4a5780::get(unsigned int flags) { cleanup(); if (flags & 1) release_4a5780(this); return this; }
