extern "C" unsigned char table_4fb660[]; extern "C" void* __cdecl storage_4fb660(unsigned int);
class Storage_4fb660 { unsigned int table_word; unsigned int* items; unsigned int count; unsigned char valid; unsigned char owns; public: void* get(unsigned int requested,unsigned int* buffer); };
void* Storage_4fb660::get(unsigned int requested,unsigned int* buffer) { items=0; count=requested; valid=1; owns=0; table_word=(unsigned int)table_4fb660; if(requested) { if(buffer) { items=buffer; return this; } items=(unsigned int*)storage_4fb660(requested << 2); owns=1; } return this; }
