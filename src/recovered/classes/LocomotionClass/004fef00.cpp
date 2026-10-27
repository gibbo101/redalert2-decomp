extern "C" void __cdecl release_4fef00(void*);
class Leaf_4fef00 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_4fef00::get(unsigned int flags) { cleanup(); if (flags & 1) release_4fef00(this); return this; }
