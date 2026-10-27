extern "C" void __cdecl release_58dd90(void*);
class Cleanup_58dd90 { unsigned char pad0[4]; unsigned int* items; int count; unsigned char pad12[1]; unsigned char owns; unsigned char pad14[2]; int capacity; public: void get(); };
void Cleanup_58dd90::get() { unsigned int* pointer=items; capacity=0; if(pointer && owns) { release_58dd90(pointer); items=0; } owns=0; count=0; }
