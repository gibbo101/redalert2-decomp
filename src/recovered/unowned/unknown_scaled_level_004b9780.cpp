int FactoryClass::Production_Rate_004B9780() const
{
 int duration=0;
 if(Object) duration=Object->Unknown_006C22A0();
 int rate=duration/54;
 if(rate<1) rate=1;
 else if(rate>255) rate=255;
 return rate;
}
