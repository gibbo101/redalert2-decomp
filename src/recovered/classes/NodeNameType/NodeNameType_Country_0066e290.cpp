// NodeNameType accessors defined in Session.CPP (0x0066E290-0x0066E320); the session members later in the unit
// expand them inline. The vector accessors this unit uses are implemented here (the first include of
// shared/vector_class.hpp in the unit).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/vector_class.hpp"
#include "shared/unknown_player_entry.hpp"

// The country (+0x4B); -2 when +0x4F marks it random.
int NodeNameType::unknown_66e290()
{
    if (unknown_4f == -2) {
        return -2;
    }
    return unknown_4b;
}
