PacketField_004BAD50::PacketField_004BAD50(char const *name,unsigned char value)
{
 strncpy(Name,name,4);
 Type=2;
 Length=1;
 Data=new char[Length];
 memcpy(Data,&value,Length);
 Next=0;
}
