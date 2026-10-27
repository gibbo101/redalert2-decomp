extern "C" void __cdecl release_6d9750(void*);
class Leaf_6d9750 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_6d9750::get(unsigned int flags) { cleanup(); if (flags & 1) release_6d9750(this); return this; }
