// void IME_Get_Candidate_00737dd0(HIMC context, DWORD index, char *buffer, unsigned size) (0x00737DD0)
// Copies the selected entry of the IME candidate list index into buffer (at most size characters,
// terminated). As in the original, the list is allocated at the reported size but never filled
// (ImmGetCandidateListA is only asked for the size), and the selection's offset is used as the
// string pointer itself.
#include "shared/win_stub.hpp"
#include "shared/crt_string.hpp"

struct CANDIDATELIST {
    DWORD dwSize;                   // +0x00
    DWORD dwStyle;                  // +0x04
    DWORD dwCount;                  // +0x08
    DWORD dwSelection;              // +0x0C
    DWORD dwPageStart;              // +0x10
    DWORD dwPageSize;               // +0x14
    DWORD dwOffset[1];              // +0x18
};
extern "C" DWORD __stdcall ImmGetCandidateListA(HIMC context, DWORD index, CANDIDATELIST *list, DWORD length);   // 0x00781C2C
extern "C" void *__cdecl malloc(unsigned int size);
extern "C" void __cdecl free(void *block);
extern "C" char *__cdecl strncat(char *destination, char const *source, unsigned int count);
void __fastcall IME_Get_Candidate_00737dd0(HIMC context, DWORD index, char *buffer, unsigned int size);
// @ref _ImmGetCandidateListA@16=00781c2c
// @ref _malloc=00782630
// @ref _free=007825e8
// @ref _strncat=00784750

void __fastcall IME_Get_Candidate_00737dd0(HIMC context, DWORD index, char *buffer, unsigned int size)
{
    if (context) {
        DWORD length = ImmGetCandidateListA(context, index, 0, 0);
        if (length) {
            CANDIDATELIST *list = (CANDIDATELIST *)malloc(length);
            if (list) {
                if (list->dwCount && list->dwSelection < list->dwCount) {
                    strncat(buffer, (char const *)list->dwOffset[list->dwSelection], size);
                    buffer[size - 1] = 0;
                }
                free(list);
            }
        }
    }
}
