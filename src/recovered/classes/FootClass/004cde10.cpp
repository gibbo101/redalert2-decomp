extern "C" void __cdecl release_4cde10(void*);
class Leaf_4cde10 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_4cde10::get(unsigned int flags) { cleanup(); if (flags & 1) release_4cde10(this); return this; }
