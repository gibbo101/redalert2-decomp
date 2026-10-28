// UnknownPathEstimator::~UnknownPathEstimator() (0x004281E0)
// Frees the estimator's blocks and tables; the three vectors at +0x74 are
// destroyed as members.
#ifndef VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#endif
#ifndef VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#endif
#include "shared/path_estimator.hpp"
// @ref ??_7?$VectorClass@I@@6B@=0079c4fc

UnknownPathEstimator::~UnknownPathEstimator()
{
    UnknownPathEstimatorBlock *block = unknown_14;
    if (block) {
        delete block->unknown_08;
        delete block;
    }
    unknown_14 = 0;
    block = unknown_68;
    if (block) {
        delete block->unknown_08;
        delete block;
    }
    unknown_68 = 0;
    if (unknown_10) {
        delete unknown_10;
    }
    unknown_10 = 0;
    if (unknown_0c) {
        delete unknown_0c;
    }
    unknown_0c = 0;
    if (unknown_18) {
        delete unknown_18;
        unknown_18 = 0;
    }
    if (unknown_1c) {
        delete unknown_1c;
        unknown_1c = 0;
    }
    if (unknown_24) {
        delete unknown_24;
        unknown_24 = 0;
    }
    if (unknown_20) {
        delete unknown_20;
        unknown_20 = 0;
    }
    for (int index = 0; index < 3; index++) {
        if (unknown_40[index]) {
            delete unknown_40[index];
            unknown_40[index] = 0;
        }
        if (unknown_4c[index]) {
            delete unknown_4c[index];
            unknown_4c[index] = 0;
        }
        if (unknown_58[index]) {
            delete unknown_58[index];
            unknown_58[index] = 0;
        }
    }
    delete unknown_64;
}
