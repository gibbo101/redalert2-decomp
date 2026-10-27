extern "C" void __cdecl release_4a57a0(void*);
class Leaf_4a57a0 { public: void cleanup();void* get(unsigned int flags); };
void* Leaf_4a57a0::get(unsigned int flags) { cleanup(); if (flags & 1) release_4a57a0(this); return this; }
