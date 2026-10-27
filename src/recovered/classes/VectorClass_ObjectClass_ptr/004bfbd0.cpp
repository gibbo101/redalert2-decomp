extern "C" unsigned char table_4bfbd0[]; extern "C" void* __cdecl storage_4bfbd0(unsigned int);
class Storage_4bfbd0 { unsigned int table_word; unsigned int* items; unsigned int count; unsigned char valid; unsigned char owns; public: void* get(unsigned int requested,unsigned int* buffer); };
void* Storage_4bfbd0::get(unsigned int requested,unsigned int* buffer) { items=0; count=requested; valid=1; owns=0; table_word=(unsigned int)table_4bfbd0; if(requested) { if(buffer) { items=buffer; return this; } items=(unsigned int*)storage_4bfbd0(requested << 2); owns=1; } return this; }
