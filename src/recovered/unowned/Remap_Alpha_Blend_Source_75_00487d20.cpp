void UnknownRemapAlphaBlitter::Blend_Source_75(unsigned short *dest,unsigned char const *source,int count,int level,unsigned short *alpha,int,int,int) const {
 unsigned short *cursor=alpha;
 if(count>0) {
  int remaining=count;
  ABuffer *buffer=ABufferPtr;
  do {
   unsigned char index;
   if(level<*cursor && (index=*source)!=0) {
    *dest=((Palette[index]>>2)&ChannelMask)*3+((*dest>>2)&ChannelMask);
    *cursor=level;
    buffer=ABufferPtr;
   }
   ++source;++dest;
   cursor=Wrap_Alpha(buffer,cursor+1);
  } while(--remaining);
 }
}
