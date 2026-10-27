extern "C" unsigned char table_47d0e0[]; extern "C" void* __cdecl storage_47d0e0(unsigned int);
class Storage_47d0e0 { unsigned int table_word; unsigned int* items; unsigned int count; unsigned char valid; unsigned char owns; public: void* get(unsigned int requested,unsigned int* buffer); };
void* Storage_47d0e0::get(unsigned int requested,unsigned int* buffer) { items=0; count=requested; valid=1; owns=0; table_word=(unsigned int)table_47d0e0; if(requested) { if(buffer) { items=buffer; return this; } items=(unsigned int*)storage_47d0e0(requested << 2); owns=1; } return this; }
