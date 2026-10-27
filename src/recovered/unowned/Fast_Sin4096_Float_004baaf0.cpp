float __fastcall Fast_Sin4096_Float_004baaf0(float angle)
{
 int index=(int)(angle*unknown_sin4096_scale_007a0f80)%4096;
 if(index<0) index+=4096;
 return unknown_sin_table_80fde4[index];
}
