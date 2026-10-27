extern "C" void __cdecl release_58da50(void*);
class Leaf_58da50 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_58da50::get(unsigned int flags) { cleanup(); if (flags & 1) release_58da50(this); return this; }
