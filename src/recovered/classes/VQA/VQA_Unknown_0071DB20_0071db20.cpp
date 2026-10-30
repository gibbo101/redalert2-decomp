// void __fastcall VQA_Unknown_0071DB20() (0x0071DB20): clears the 18 VQA options, then sets option 6.
#include "shared/movie.hpp"
// @ref ?unknown_vqa_options_af9020@@3PAEA=00af9020

void __fastcall VQA_Unknown_0071DB20()
{
    for (int option = 0; option < 18; option++) {
        VQA_Unknown_0071DB80(option);
    }
    VQA_Unknown_0071DB60(6);
}

