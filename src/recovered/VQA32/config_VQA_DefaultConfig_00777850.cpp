// void __fastcall VQA_Unknown_00777850(VQAConfig *config) -- 0x00777850
// Purpose: VQA_DefaultConfig (TS config.cpp): copies the library's default
// configuration (0x00801470, original data) into the caller's.
#include "shared/vqa_player.hpp"
// @ref ?unknown_vqa_default_config_801470@@3UVQAConfig@@A=00801470

extern VQAConfig unknown_vqa_default_config_801470;

void __fastcall VQA_Unknown_00777850(VQAConfig *config)
{
    *config = unknown_vqa_default_config_801470;
}
