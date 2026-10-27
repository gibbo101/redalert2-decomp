// Placement new, as VC6's <new.h> provides it (used to rebuild members in
// place, e.g. CCFileClass::Close re-creating its Buffer).
#ifndef RA2_SHARED_CRT_NEW_HPP
#define RA2_SHARED_CRT_NEW_HPP

#ifndef __PLACEMENT_NEW_INLINE
#define __PLACEMENT_NEW_INLINE
inline void *__cdecl operator new(unsigned int, void *where)
{
    return where;
}
#endif

#endif
