#ifndef RA2_ALPHA_BLEND_CANDIDATES_HPP
#define RA2_ALPHA_BLEND_CANDIDATES_HPP
#include "shared/blit.hpp"
// Shared observed state of the two remapping alpha-blend routines:
// a Blitter-compatible first pointer, remapping table +4, channel mask +8.
// Original concrete class/template identity remains unknown.
class UnknownRemapAlphaBlitter : public Blitter {
public:
 void Blend_Destination_75(unsigned short *dest,unsigned char const *source,int count,int level,unsigned short *alpha,int unknown6,int unknown7,int unknown8) const;
 void Blend_Source_75(unsigned short *dest,unsigned char const *source,int count,int level,unsigned short *alpha,int unknown6,int unknown7,int unknown8) const;
 unsigned short const *Palette; // +4
 unsigned short ChannelMask; // +8
};
#endif
