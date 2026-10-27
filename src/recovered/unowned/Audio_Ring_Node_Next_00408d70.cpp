// AudioStreamNode *__fastcall Audio_Ring_Node_Next(AudioStreamNode *node) -- 0x00408D70
// Purpose: the next node round the ring (AudioStreamNode::Ring_Next).
#include "shared/audio.hpp"

AudioStreamNode *__fastcall Audio_Ring_Node_Next(AudioStreamNode *node)
{
    return node->Ring_Next();
}
