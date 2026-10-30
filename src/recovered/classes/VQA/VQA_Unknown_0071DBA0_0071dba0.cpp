// bool __fastcall VQA_Unknown_0071DBA0(int option) (0x0071DBA0): the option bit is set.
#include "shared/movie.hpp"
// @ref ?unknown_vqa_options_af9020@@3PAEA=00af9020

bool __fastcall VQA_Unknown_0071DBA0(int option)
{
    int index = option >> 3;
    unsigned char shift = option & 7;
    unsigned char mask = 1 << shift;
    return (unknown_vqa_options_af9020[index] & mask) ? true : false;
}
