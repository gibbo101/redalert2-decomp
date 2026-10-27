extern "C" void __cdecl release_510b00(void*);
class Leaf_510b00 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_510b00::get(unsigned int flags) { cleanup(); if (flags & 1) release_510b00(this); return this; }
