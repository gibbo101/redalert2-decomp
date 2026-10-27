#ifndef RA2_UNKNOWN_DESCRIPTION_LIST_HPP
#define RA2_UNKNOWN_DESCRIPTION_LIST_HPP
#include "shared/vector_class.hpp"
#include "shared/ccini_class.hpp"
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#endif
// Cooperative campaign record, 0x44 bytes. The original class name is unresolved.
struct UnknownDescriptionRecord_00490E00 {
 int Index;
 wchar_t *Name; // +04
 signed char MapCount;
 char unknown_09[3];
 char *Maps; // MapCount records of 0x30C bytes, each three 260-byte strings.
 DynamicVectorClass<char *> Players;
 DynamicVectorClass<char *> Enemies;
 char *AIName;
};
class UnknownDescriptionList_00490E00 {
public:
 UnknownDescriptionList_00490E00();
 ~UnknownDescriptionList_00490E00();
#ifdef DESCRIPTION_LIST_INLINE_GET_RECORD
 // The actual recovered00490C50 operation, shared by the campaign sender.
 bool Get_Record_00490C50(int index, UnknownDescriptionRecord_00490E00 **record)
 {
     if(index>=0 && index<Count) {
         *record=&Entries[index];
         return true;
     }
     *record=0;
     return false;
 }
#else
 bool Get_Record_00490C50(int index, UnknownDescriptionRecord_00490E00 **record);
#endif
 bool Get_Count_00490C90(int *count) const;
 bool Copy_Names(DynamicVectorClass<wchar_t *> &names);
 CCINIClass Ini; // +0, composition hypothesis: canonical sizeof(CCINIClass)==0x50
 UnknownDescriptionRecord_00490E00 *Entries; // +50
 int Count; // +54
 bool Initialized; // +58
};
#endif


typedef char DescriptionRecord_size_check[(sizeof(UnknownDescriptionRecord_00490E00)==0x44)?1:-1];

typedef char Description_INI_prefix_size_check[(sizeof(CCINIClass)==0x50)?1:-1];
