extern "C" char fixedA_006883d0[]; extern "C" char fixedB_006883d0[];
extern "C" int __cdecl compare_006883d0(const char*,const char*);
extern "C" int count_006883d0; extern "C" unsigned char** items_006883d0;
extern "C" void* __cdecl storage_006883d0(unsigned int);
class Entry_006883d0 { public: void* finish(const char*); };
extern "C" void* __fastcall recover_006883d0(const char* name) {
 if(!compare_006883d0(fixedA_006883d0,name)) return 0;
 if(!compare_006883d0(fixedB_006883d0,name)) return 0;
 for(int index=0;index<count_006883d0;++index) {
  if(!compare_006883d0((const char*)items_006883d0[index]+36,name)) return items_006883d0[index];
 }
 void* memory=storage_006883d0(0x274u);
 if(memory) return ((Entry_006883d0*)memory)->finish(name);
 return 0;
}
