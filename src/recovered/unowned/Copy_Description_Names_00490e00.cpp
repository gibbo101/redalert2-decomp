#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/unknown_description_list.hpp"
extern "C" wchar_t *__cdecl wcscpy(wchar_t *,wchar_t const *);
bool UnknownDescriptionList_00490E00::Copy_Names(DynamicVectorClass<wchar_t *> &names) {
 if(Initialized) {
 names.Resize(Count,0);
 for(int i=0;i<Count;++i) {
  names[i]=new wchar_t[129];
  if(names[i]) wcscpy(names[i],Entries[i].Name);
 }
 return true;
 }
 return false;
}

