// TypeList<T> declaration only (shared/type_list.hpp documents it and holds
// the member definitions; see shared/vector_class_decl.hpp for why a class
// with a TypeList member includes this one).

#ifndef SHARED_TYPE_LIST_DECL_HPP
#define SHARED_TYPE_LIST_DECL_HPP

#include "shared/vector_class_decl.hpp"

struct IStream;

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

#endif
