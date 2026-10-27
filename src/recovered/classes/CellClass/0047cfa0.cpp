extern "C" void __cdecl release_47cfa0(void*);
class Leaf_47cfa0 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_47cfa0::get(unsigned int flags) { cleanup(); if (flags & 1) release_47cfa0(this); return this; }
