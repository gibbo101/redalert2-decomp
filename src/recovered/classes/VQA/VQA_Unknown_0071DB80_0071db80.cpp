// void __fastcall VQA_Unknown_0071DB80(int option) (0x0071DB80): clears the option bit.
#include "shared/movie.hpp"
// @ref ?unknown_vqa_options_af9020@@3PAEA=00af9020

void __fastcall VQA_Unknown_0071DB80(int option)
{
    int index = option >> 3;
    unsigned char shift = option & 7;
    unsigned char mask = 1 << shift;
    unknown_vqa_options_af9020[index] &= ~mask;
}
