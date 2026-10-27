extern "C" char fixedA_005dcf70[]; extern "C" char fixedB_005dcf70[];
extern "C" int __cdecl compare_005dcf70(const char*,const char*);
extern "C" int count_005dcf70; extern "C" unsigned char** items_005dcf70;
extern "C" void* __cdecl storage_005dcf70(unsigned int);
class Entry_005dcf70 { public: void* finish(const char*); };
extern "C" void* __fastcall recover_005dcf70(const char* name) {
 if(!compare_005dcf70(fixedA_005dcf70,name)) return 0;
 if(!compare_005dcf70(fixedB_005dcf70,name)) return 0;
 for(int index=0;index<count_005dcf70;++index) {
  if(!compare_005dcf70((const char*)items_005dcf70[index]+36,name)) return items_005dcf70[index];
 }
 void* memory=storage_005dcf70(0x288u);
 if(memory) return ((Entry_005dcf70*)memory)->finish(name);
 return 0;
}
