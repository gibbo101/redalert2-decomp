extern "C" void __cdecl release_4def10(void*);
class Leaf_4def10 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_4def10::get(unsigned int flags) { cleanup(); if (flags & 1) release_4def10(this); return this; }
