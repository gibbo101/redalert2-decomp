// ProgressScreenClass::~ProgressScreenClass() (0x0061ED50): frees the shape.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/progress_screen.hpp"
// @ref ??_7ProgressScreenClass@@6B@=007a843c

ProgressScreenClass::~ProgressScreenClass()
{
    Free_Shape();
}
