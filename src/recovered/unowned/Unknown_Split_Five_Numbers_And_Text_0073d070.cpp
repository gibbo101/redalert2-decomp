// void __fastcall Unknown_Split_Five_Numbers_And_Text_0073D070(char *text, int *first, int *second, int *third, int *fourth, int *fifth, UnknownStringSlot *rest) (0x0073D070)
// Splits a comma list: five numbers (0 for a missing token) and the next token as the text slot.
// @ref ?Assign@UnknownStringSlot@@QAEXPBD@Z=0076dbc0
// @ref _strtok=00782ec2
// @ref _atol=00782d72
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
#include "shared/crt_tokens.hpp"
#include "shared/wol_list_text.hpp"

extern "C" long __cdecl atol(char const *text);

void __fastcall Unknown_Split_Five_Numbers_And_Text_0073D070(char *text, int *first, int *second,
                                                             int *third, int *fourth, int *fifth,
                                                             UnknownStringSlot *rest)
{
    char *token = strtok(text, ",");
    *first = token != 0 ? atol(token) : 0;
    token = strtok(0, ",");
    *second = token != 0 ? atol(token) : 0;
    token = strtok(0, ",");
    *third = token != 0 ? atol(token) : 0;
    token = strtok(0, ",");
    *fourth = token != 0 ? atol(token) : 0;
    token = strtok(0, ",");
    *fifth = token != 0 ? atol(token) : 0;
    rest->Assign(strtok(0, ","));
}
