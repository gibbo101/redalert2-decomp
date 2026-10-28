// int __fastcall Unknown_006A29B0(int pixel) (0x006A29B0): a screen rise back
// to leptons of height (the inverse of 0x006A2970; hypothesis).
#include "shared/tactical.hpp"
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref ?unknown_abe520@@3NA=00abe520
extern double unknown_abe520;   // leptons of height per pixel

int __fastcall Unknown_006A29B0(int pixel)
{
    return (int)((pixel - 0.5) * unknown_abe520);
}
