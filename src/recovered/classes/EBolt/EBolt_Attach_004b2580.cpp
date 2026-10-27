void EBolt::Attach_004B2580(TechnoClass *owner,int index)
{
 if(owner && owner->Kind_Of()==1 && owner->unknown_7d && !owner->unknown_76) {
  Owner=static_cast<UnitClass *>(owner);
  unknown_24=index;
 }
}
