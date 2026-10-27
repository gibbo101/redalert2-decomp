// TypeList<T>: Westwood's typed list, a DynamicVectorClass<T> with its own
// vtable.
//
// Evidence: 14 TypeList<...> RTTI vtables in the base RA2 executable (SHA256
// e6418111...), e.g. TypeList<int> 0x0079D9F4 (CCINI unit, slots 0x0046CDD0
// ...). TypeList adds one 4-byte field that no constructor touches (see
// unknown_0x18) and overrides only the destructor slot; its scalar deleting destructor stores
// the VectorClass vptr only, so ~TypeList and ~DynamicVectorClass are
// implicit and ~VectorClass is the user-declared one (shared/vector_class.hpp).
//
// Constructors observed out of line (COMDAT copies, one per unit that kept
// one):
//   TypeList()                     34 bytes, no arguments (DynamicVectorClass
//                                  with size 0 and no array, VectorClass
//                                  constructor expanded); e.g. 0x00652BD0
//   TypeList(NoInitClass const &)  11 bytes, vptr store only; e.g. 0x0050B0F0
//   TypeList(TypeList const &)     136 bytes: DynamicVectorClass's implicit
//                                  copy (VectorClass copy constructor
//                                  expanded, then ActiveCount and
//                                  GrowthStep), +0x18 not copied; e.g.
//                                  0x0046CBF0
// CCINIClass's list readers (0x0046B1B0 ...) construct a local TypeList()
// with the VectorClass constructor called out of line and return the list
// by value through the copy constructor.
//
// Compiling one constructor at a time: VC6 cannot explicitly instantiate a
// constructor, and `template class TypeList<T>;` also emits the implicit
// ~TypeList, which has no original copy. A recovery source therefore defines
// the base guards it needs (VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR, ..._NOINIT_
// or the VectorClass copy/assign/destructor guards), includes this header and
// writes the one constructor as an explicit specialization with the generic
// body below (build/class-work/TypeList/generate.py writes them). Any
// constructor emits the TypeList vtable, the scalar deleting destructor, the
// VectorClass vtable and VectorClass::Clear; sources bind those to the
// original copies with @ref. The generic definitions (TYPELIST_IMPLEMENT_*
// or VECTOR_IMPLEMENT_ALL) serve ordinary users such as the CCINIClass list
// readers, where the members are instantiated implicitly. Include this
// header, not shared/vector_class.hpp, first: it sets the base guards.

#ifndef SHARED_TYPE_LIST_HPP
#define SHARED_TYPE_LIST_HPP

#ifdef VECTOR_IMPLEMENT_ALL
#define TYPELIST_IMPLEMENT_DEFAULT_CONSTRUCTOR
#define TYPELIST_IMPLEMENT_NOINIT_CONSTRUCTOR
#define TYPELIST_IMPLEMENT_COPY_CONSTRUCTOR
#endif

// Each constructor expands its base versions.
#ifdef TYPELIST_IMPLEMENT_DEFAULT_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#endif
#ifdef TYPELIST_IMPLEMENT_NOINIT_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_NOINIT_CONSTRUCTOR
#endif
#ifdef TYPELIST_IMPLEMENT_COPY_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_COPY_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#endif

#include "shared/vector_class.hpp"

#include "shared/com_persist.hpp"

template <class T>
class TypeList : public DynamicVectorClass<T> {
public:
    TypeList();
    TypeList(NoInitClass const &noinit);
    TypeList(TypeList<T> const &list);

    // Writes Count(), then each active element (TechnoType.cpp copy
    // 0x006DF7F0; name hypothesis).
    void Save(IStream *stream);

    // Rebuilds the list in place (an empty list) from a saved count and its
    // elements (WarheadTypeClass 0x00720DB0, TiberiumClass 0x006E9160 expand
    // it inline; name hypothesis).
    void Load(IStream *stream);

    // +0x18: sizeof(TypeList) is 0x1C (callers reserve 0x1C bytes for a
    // by-value list argument, e.g. 0x006214B1, and the CCINIClass readers
    // pop 0x1C bytes for it), but no constructor writes or copies this
    // field, so the copy constructor is user-declared.
    int unknown_0x18;

    // The implicit assignment, written out so a recovery source can define
    // one instance as an explicit specialization (the Rules unit keeps
    // out-of-line copies, e.g. 0x006528A0): DynamicVectorClass's assignment
    // expanded, then +0x18. The generic definition is inline, as the implicit one is.
    TypeList<T> &operator=(TypeList<T> const &list);
};

template <class T>
inline TypeList<T> &TypeList<T>::operator=(TypeList<T> const &list)
{
    DynamicVectorClass<T>::operator=(list);
    unknown_0x18 = list.unknown_0x18;
    return *this;
}

#ifdef TYPELIST_IMPLEMENT_DEFAULT_CONSTRUCTOR
// An empty list growing by 10 (no storage until the first Add).
template <class T>
TypeList<T>::TypeList()
{
}
#endif

#ifdef TYPELIST_IMPLEMENT_NOINIT_CONSTRUCTOR
// Installs the vtable only (objects restored in place).
template <class T>
TypeList<T>::TypeList(NoInitClass const &noinit)
    : DynamicVectorClass<T>(noinit)
{
}
#endif

#ifdef TYPELIST_IMPLEMENT_COPY_CONSTRUCTOR
// Deep copy of the storage (VectorClass copy constructor) and both counters.
template <class T>
TypeList<T>::TypeList(TypeList<T> const &list)
    : DynamicVectorClass<T>(list)
{
}
#endif

// The writer of each TypeList member's elements (TechnoType.cpp's copy
// is 0x006DF7F0; other units expand it inline).
template <class T>
void TypeList<T>::Save(IStream *stream)
{
    int count = Count();
    stream->Write(&count, sizeof(count), 0);
    for (int index = 0; index < count; index++) {
        stream->Write(&(*this)[index], sizeof(T), 0);
    }
}


template <class T>
void TypeList<T>::Load(IStream *stream)
{
    new (this) TypeList<T>;
    int count;
    stream->Read(&count, sizeof(count), 0);
    for (int index = 0; index < count; index++) {
        T value;
        stream->Read(&value, sizeof(value), 0);
        Add(value);
    }
}

#endif
