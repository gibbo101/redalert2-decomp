PacketField_004BAD50::PacketField_004BAD50(char const *name,unsigned int value)
{
 strncpy(Name,name,4);
 Type=6;
 Length=4;
 Data=new char[Length];
 memcpy(Data,&value,Length);
 Next=0;
}
