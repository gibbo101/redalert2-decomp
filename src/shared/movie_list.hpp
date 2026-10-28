// The movie names (moved out of shared/ccini_extra.hpp).
#ifndef RA2_SHARED_MOVIE_LIST_HPP
#define RA2_SHARED_MOVIE_LIST_HPP

#include "shared/vector_class.hpp"

// The movie names at 0x00A71050 (the scenario's Intro/Brief/Action indices; Start_Scenario
// formats "%s.VQA" from one). Find_Index 0x00482E60 returns the index of a name, -1 for
// "<none>" or unknown.
extern DynamicVectorClass<char const *> unknown_names_a71050;
int __fastcall unknown_name_index_482e60(char const *name);

#endif
