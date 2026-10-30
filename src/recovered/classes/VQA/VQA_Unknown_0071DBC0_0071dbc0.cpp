// int __fastcall VQA_Unknown_0071DBC0(int option) (0x0071DBC0): toggles the option bit; 1 when it is now set.
#include "shared/movie.hpp"
// @ref ?unknown_vqa_options_af9020@@3PAEA=00af9020

int __fastcall VQA_Unknown_0071DBC0(int option)
{
    int index = option >> 3;
    unsigned char shift = option & 7;
    if (unknown_vqa_options_af9020[index] & (1 << shift)) {
        VQA_Unknown_0071DB80(option);
        return 0;
    }
    VQA_Unknown_0071DB60(option);
    return 1;
}
