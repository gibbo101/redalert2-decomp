// Test a prospective foundation and scatter allied mobile occupants.
// Private complete461-byte nonvirtual BuildingType member; source name/CV hypothesis.
#include "shared/building_view.hpp"
#include "shared/unit.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/foot.hpp"
#include "shared/rules.hpp"
#include "shared/house.hpp"
// @ref ?Unknown_0054AAB0@MapClass@@=0054aab0
// @ref ?unknown_44d900@BuildingClass@@=0044d900
// @ref ?Is_Ally@HouseClass@@QBE_NPBVHouseClass@@@Z=004e5540
// @ref ?unknown_476920@CellClass@@=00476920
inline FootClass *Mobile_Occupant_00458B10(TechnoClass *techno)
{
 bool mobile;
 if(techno)mobile=techno->unknown_14_bit2;
 if(!techno || !mobile)return 0;
 return static_cast<FootClass *>(techno);
}
inline bool Scatter_Allied_Occupant_00458B10(TechnoClass *techno,Cell const &cell,bool &scattered)
{
 FootClass *foot=Mobile_Occupant_00458B10(techno);
 if(!foot)return false;
 scattered=true;
 if(foot->unknown_494) {
  CoordStruct position=foot->Coord;
  if(&Map[position]!=foot->unknown_494)return true;
 }
 Map[cell].unknown_476920(&unknown_geometry_l,true,true,false);
 return true;
}
int BuildingTypeClass::unknown_458b10(Cell const &origin,HouseClass *house) const
{
 bool scattered=false;
 Cell const *offset;
 if(origin==unknown_geometry_k)goto no_placement;
 offset=unknown_slot36(1);
 while(true) {
  if(offset->X==0x7fff && offset->Y==0x7fff)break;
  Cell cell;
  cell=origin+*offset++;
  if(!Map.Unknown_0054AAB0(cell))continue;
  CellClass &map_cell=Map[cell];
  if(map_cell.OverlayIndex!=-1) {
   if(this!=Rules->unknown_78c || map_cell.OverlayIndex!=2)return 2;
  }
  ObjectClass *object=map_cell.OccupierPtr;
  if(!object)continue;
  if(object->Kind_Of()==0x24)return 2;
  if(!object->unknown_14_bit0)continue;
  if(object->Kind_Of()==6) {
   if(!static_cast<BuildingClass *>(object)->unknown_44d900(const_cast<BuildingTypeClass *>(this),house))return 2;
   continue;
  }
  TechnoClass *techno=static_cast<TechnoClass *>(object);
  if(!techno->House->Is_Ally(house))return 2;
  if(!Scatter_Allied_Occupant_00458B10(techno,cell,scattered))return 2;
 }
 if(scattered)return 1;
no_placement:
 return 0;
}
