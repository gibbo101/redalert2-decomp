PacketField_004BAD50::PacketField_004BAD50(char const *name,void const *value,unsigned short length)
{
 strncpy(Name,name,4);
 Type=20;
 Length=length;
 Data=new char[Length];
 memcpy(Data,value,Length);
 Next=0;
}
