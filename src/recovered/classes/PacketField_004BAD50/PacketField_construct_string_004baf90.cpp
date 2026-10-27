PacketField_004BAD50::PacketField_004BAD50(char const *name,char const *value)
{
 strncpy(Name,name,4);
 Type=7;
 Length=(unsigned short)(strlen(value)+1);
 Data=new char[Length];
 memcpy(Data,value,Length);
 Next=0;
}
