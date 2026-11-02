// void Voc_Handle_Set(AudioEventHandle *handle, int voc) (0x00714D10)
// Points the handle at the event type of the sound effect type, when the index is valid (name hypothesis).
#include "shared/voc_class.hpp"

void __fastcall Voc_Handle_Set(AudioEventHandle *handle, int voc)
{
    if (voc >= 0 && voc < unknown_VocClass_list_00ad0818.Count()) {
        Audio_Event_Handle_Set(handle, 0, unknown_VocClass_list_00ad0818[voc]->Event);
    }
}
