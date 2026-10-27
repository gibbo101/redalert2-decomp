extern "C" void __cdecl release_730290(void*);
class Leaf_730290 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_730290::get(unsigned int flags) { cleanup(); if (flags & 1) release_730290(this); return this; }
