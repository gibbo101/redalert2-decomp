#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/factory_class.hpp"
// @ref ?Factories@@=00a35e90
// @ref ?Unknown_006C22A0@TechnoClass@@=006c22a0
void __fastcall FactoryClass::Update_Rates(HouseClass *owner) {
 for (int i=0;i<Factories.Count();++i) {
  FactoryClass *factory=Factories[i];
  if(factory->Owner==owner) {
   int rate=0;
   if(factory->Object) rate=factory->Object->Unknown_006C22A0();
   rate/=54;
   if(rate<1) rate=1; else if(rate>255) rate=255;
   if(rate!=factory->Rate) factory->Rate=rate;
  }
 }
}
