bool FactoryClass::Start_Production_004B9670(bool suspend)
{
 if((Object || unknown_64) && unknown_6c && (!Object || Stage!=54) && (unknown_64==-1 || Stage!=54)) {
  unknown_6c=false;
  Set_Rate(Production_Rate_004B9780());
  if(Owner->Available_Money() >= Cost_Per_Tick_004B9950()) {
   unknown_6d=true;
   if(suspend) Suspend_004B9630(true);
   return true;
  }
 }
 return false;
}
