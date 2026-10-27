extern "C" unsigned char table_58f040[]; extern "C" void* __cdecl storage_58f040(unsigned int);
class Storage_58f040 { unsigned int table_word; unsigned int* items; unsigned int count; unsigned char valid; unsigned char owns; public: void* get(unsigned int requested,unsigned int* buffer); };
void* Storage_58f040::get(unsigned int requested,unsigned int* buffer) { items=0; count=requested; valid=1; owns=0; table_word=(unsigned int)table_58f040; if(requested) { if(buffer) { items=buffer; return this; } items=(unsigned int*)storage_58f040(requested << 2); owns=1; } return this; }
