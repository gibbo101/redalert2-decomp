#define VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#include "shared/vector_class.hpp"
// Original callers6456D1/645BC1 take the TypeList<int> returned by Get_Voc_List.
// The caller copies TypeList's+18 separately after this DynamicVector assignment.
template class DynamicVectorClass<int>;
