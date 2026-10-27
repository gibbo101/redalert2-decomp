extern "C" void __cdecl release_4deef0(void*);
class Leaf_4deef0 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_4deef0::get(unsigned int flags) { cleanup(); if (flags & 1) release_4deef0(this); return this; }
