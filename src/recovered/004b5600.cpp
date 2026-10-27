extern "C" void __cdecl release_4b5600(void*);
class Cleanup_4b5600 { unsigned char pad0[4]; unsigned int* items; int count; unsigned char pad12[1]; unsigned char owns; public: void get(); };
void Cleanup_4b5600::get() { unsigned int* pointer=items; if(pointer && owns) { release_4b5600(pointer); items=0; } owns=0; count=0; }
