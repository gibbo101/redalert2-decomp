PacketField_004BAD50::PacketField_004BAD50(char const *name,short value)
{
 strncpy(Name,name,4);
 Type=3;
 Length=2;
 Data=new char[Length];
 memcpy(Data,&value,Length);
 Next=0;
}
