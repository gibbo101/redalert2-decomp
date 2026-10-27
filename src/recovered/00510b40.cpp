extern "C" void __cdecl release_510b40(void*);
class Leaf_510b40 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_510b40::get(unsigned int flags) { cleanup(); if (flags & 1) release_510b40(this); return this; }
