// VectorClass<wchar_t *>::operator=; called by ListClass copy construction.
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#endif
#include "shared/vector_class.hpp"
template class VectorClass<wchar_t *>;
