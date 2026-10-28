// void Speech_Play_Name(char const *name, int type, int priority) (0x00715B40):
// plays the VoxClass of a name; nothing for a null name (name hypothesis).
#include "shared/vox_speech.hpp"
// @ref ?Speech_Play@@YIXHHH@Z=007158c0
void __fastcall Speech_Play_Name(char const *name, int type, int priority)
{
    if (name != 0) {
        Speech_Play(VoxClass::Find_Index(name), type, priority);
    }
}
