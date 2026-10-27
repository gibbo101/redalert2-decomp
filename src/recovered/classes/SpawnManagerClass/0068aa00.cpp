extern "C" void __cdecl release_68aa00(void*);
class Leaf_68aa00 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_68aa00::get(unsigned int flags) { cleanup(); if (flags & 1) release_68aa00(this); return this; }
