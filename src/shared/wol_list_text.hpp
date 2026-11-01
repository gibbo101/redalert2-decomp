#ifndef RA2_SHARED_WOL_LIST_TEXT_HPP
#define RA2_SHARED_WOL_LIST_TEXT_HPP
#include "shared/wstring.hpp"
// Five comma-separated numbers followed by the next token as a Wstring.
void __fastcall Parse_Channel_Info_0073d070(char *text,int *first,int *second,int *third,int *fourth,int *fifth,Wstring *rest);
#endif
