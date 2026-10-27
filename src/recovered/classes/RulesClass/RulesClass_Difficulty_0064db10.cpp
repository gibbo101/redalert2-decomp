// RulesClass::Difficulty (0x0064DB10)
// Reads the [Easy], [Normal] and [Difficult] modifiers (Difficulty_Get 0x0064DB60).
// @ref ??_C@_04PPCI@Easy?$AA@=007ceaec
// @ref ??_C@_06BILL@Normal?$AA@=007d1b30
// @ref ??_C@_09IPG@Difficult?$AA@=007f1ac8
// @ref ?Difficulty_Get@@YIXAAVCCINIClass@@AAUDifficultyClass@@PBD@Z=0064db60
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"

void __fastcall Difficulty_Get(CCINIClass &ini, DifficultyClass &diff, char const *section);

bool RulesClass::Difficulty(CCINIClass &ini)
{
    Difficulty_Get(ini, Diff[0], "Easy");
    Difficulty_Get(ini, Diff[1], "Normal");
    Difficulty_Get(ini, Diff[2], "Difficult");
    return true;
}
