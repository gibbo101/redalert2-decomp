extern "C" char fixedA_006e5a20[]; extern "C" char fixedB_006e5a20[];
extern "C" int __cdecl compare_006e5a20(const char*,const char*);
extern "C" int count_006e5a20; extern "C" unsigned char** items_006e5a20;
extern "C" void* __cdecl storage_006e5a20(unsigned int);
class Entry_006e5a20 { public: void* finish(const char*); };
extern "C" void* __fastcall recover_006e5a20(const char* name) {
 if(!compare_006e5a20(fixedA_006e5a20,name)) return 0;
 if(!compare_006e5a20(fixedB_006e5a20,name)) return 0;
 for(int index=0;index<count_006e5a20;++index) {
  if(!compare_006e5a20((const char*)items_006e5a20[index]+36,name)) return items_006e5a20[index];
 }
 void* memory=storage_006e5a20(0x28cu);
 if(memory) return ((Entry_006e5a20*)memory)->finish(name);
 return 0;
}
