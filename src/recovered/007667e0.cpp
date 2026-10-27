extern "C" void __cdecl release_7667e0(void*);
class Leaf_7667e0 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_7667e0::get(unsigned int flags) { cleanup(); if (flags & 1) release_7667e0(this); return this; }
