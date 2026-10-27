void PacketField_004BAD50::Network_To_Host_004BB0F0()
{
 Length=ntohs(Length);
 Type=ntohs(Type);
 switch(Type) {
 case 3:case 4:*(unsigned short *)Data=ntohs(*(unsigned short *)Data);break;
 case 5:case 6:*(unsigned long *)Data=ntohl(*(unsigned long *)Data);break;
 }
}
