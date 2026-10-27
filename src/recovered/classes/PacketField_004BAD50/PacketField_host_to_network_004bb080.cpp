void PacketField_004BAD50::Host_To_Network_004BB080()
{
 switch(Type) {
 case 3:case 4:*(unsigned short *)Data=htons(*(unsigned short *)Data);break;
 case 5:case 6:*(unsigned long *)Data=htonl(*(unsigned long *)Data);break;
 }
 Type=htons(Type);
 Length=htons(Length);
}
