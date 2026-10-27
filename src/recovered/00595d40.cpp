extern "C" void __cdecl release_595d40(void*);
class Leaf_595d40 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_595d40::get(unsigned int flags) { cleanup(); if (flags & 1) release_595d40(this); return this; }
