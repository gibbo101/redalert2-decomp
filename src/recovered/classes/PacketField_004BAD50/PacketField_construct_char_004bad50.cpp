#include "shared/packet_field.hpp"
#include "shared/crt_memory.hpp"
extern "C" char *__cdecl strncpy(char *,char const *,unsigned int);
extern "C" unsigned int __cdecl strlen(char const *);
#pragma intrinsic(strlen)
extern "C" unsigned long __stdcall htonl(unsigned long);
extern "C" unsigned short __stdcall htons(unsigned short);
extern "C" unsigned long __stdcall ntohl(unsigned long);
extern "C" unsigned short __stdcall ntohs(unsigned short);
// @ref _htonl@4=00781b66
// @ref _htons@4=00781b6c
// @ref _ntohl@4=00781b72
// @ref _ntohs@4=00781b78
PacketField_004BAD50::PacketField_004BAD50(char const *name,char value)
{
 strncpy(Name,name,4);
 Type=1;
 Length=1;
 Data=new char[Length];
 memcpy(Data,&value,Length);
 Next=0;
}
