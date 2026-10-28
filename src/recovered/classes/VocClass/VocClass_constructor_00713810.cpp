// VocClass::VocClass(char const *name) (0x00713810): joins the unit's VocClass
// list, then looks up the audio event type of the name.
#include "shared/voc_class.hpp"
// @ref ?Audio_Event_Type_Find@@YIPAUAudioEventType@@PBD@Z=004063c0

VocClass::VocClass(char const *name) : Event(0)
{
    unknown_VocClass_list_00ad0818.Add(this);
    Event = Audio_Event_Type_Find(name);
}
