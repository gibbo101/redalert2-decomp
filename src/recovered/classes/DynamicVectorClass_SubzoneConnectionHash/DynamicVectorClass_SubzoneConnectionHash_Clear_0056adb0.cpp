// DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::Clear (0x0056ADB0; DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>> vtable 0x007a5a58 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class SubzoneConnectionStruct;

template <class A0, class A1>
struct HashObject;

template class DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct> >;
