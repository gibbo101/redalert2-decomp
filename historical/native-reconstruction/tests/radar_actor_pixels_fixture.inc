// SPDX-License-Identifier: GPL-3.0-or-later
// Included inside the shared vector fixture; every view names its live records.
std::int32_t houseMode=std::int32_t(actorFields[0]);
std::array<RadarColorActorKind,3> actorKinds;std::array<std::uint8_t,3> actorFlags,typeFlags,humanFlags,controlFlags;
std::array<const void*,3> alternates;int typeIds[3]={0,1,2};
std::array<std::int32_t,3> houseIndexes=actorFields[4]==0?std::array<std::int32_t,3>{0,1,2}:actorFields[4]==1?std::array<std::int32_t,3>{-1,31,32}:actorFields[4]==2?std::array<std::int32_t,3>{7,7,7}:std::array<std::int32_t,3>{INT32_MIN,INT32_MAX,-1};
std::array<std::uint32_t,3> houseAllies;houseAllies.fill(std::uint32_t(actorFields[3]));std::array<std::array<std::uint8_t,3>,3> houseColors;
for(int i=0;i<3;++i){actorKinds[i]=(actorFields[2]==1||(actorFields[2]>=2&&((i+actorFields[2])&1)))?RadarColorActorKind::building:RadarColorActorKind::infantry;actorFlags[i]=(f[17]>>i&1)?255:0;typeFlags[i]=std::uint8_t(f[15]>>i&1);humanFlags[i]=std::uint8_t(f[14]>>i&1);controlFlags[i]=std::uint8_t(actorFields[1]>>i&1);alternates[i]=f[18]<0?nullptr:&houses[f[18]];houseColors[i]={std::uint8_t(19+i*77),std::uint8_t(37+i*33),std::uint8_t(251-i*61)};}
bool radarChanged=false,resolverChanged=false;
RadarColorWorld colorWorld{current,[&](const void* p){const auto i=aid(p);return RadarColorActor{actorKinds[i],actorFlags[i],[&,i]{return owners[i];},[&,i]{return alternates[i];}};},[&](const void* p){const auto i=hid(p);need(i>=0);return RadarColorHouse{houseIndexes[i],houseAllies[i]};},
[&](const void* p,const void* owner,const void* other,bool allied){const auto i=aid(p);std::cout<<"j "<<i<<' '<<hid(owner)<<' '<<hid(other)<<' '<<allied<<' ';const auto m=actorFields[5];if(m&&!radarChanged){radarChanged=true;if(m&1)owners[i]=&houses[2];if(m&2)current=&houses[2];if(m&4)alternates[i]=&houses[2];if(m&8){houseIndexes[2]=-1;houseAllies[0]^=UINT32_MAX;}}}};
SurfaceMarkScheme extraSchemes[2]{{nullptr,0x2345},{nullptr,0x3456}};std::array<SurfaceMarkScheme*,3> schemeRecords{&scheme,&extraSchemes[0],&extraSchemes[1]};
std::array<std::array<const SurfaceMarkScheme*,3>,2> schemeRegistries{{{schemeRecords[0],schemeRecords[1],schemeRecords[2]},{schemeRecords[2],schemeRecords[1],schemeRecords[0]}}};
std::span<const SurfaceMarkScheme*> schemeRegistry=schemeRegistries[0];std::int32_t schemeCount=3;std::uint32_t schemeLocale=0;
std::array<std::string,3> schemeNames{"LightGrey",actorFields[6]?"Other":"LightGrey","LightGrey"};std::array<std::int32_t,3> schemeCategories{0,1,1};
auto schemeId=[&](const auto* p){for(int i=0;i<3;++i)if(p==schemeRecords[i])return i;throw std::invalid_argument("Foreign radar scheme");};
auto resolverMutate=[&](int stage,std::uint32_t at){const auto bits=stage==1?actorFields[8]&7:actorFields[8]>>3&7;if(resolverChanged||!bits||at!=actorFields[7])return;resolverChanged=true;if(bits&1)schemeRegistry=schemeRegistries[1];if(bits&2)schemeCategories[1]=-1;if(bits&4)schemeNames[1]="Other";};
SchemeResolverWorld schemeWorld{schemeRegistry,schemeCount,schemeLocale,[&](auto p)->std::string_view{return schemeNames[schemeId(p)];},[&](auto p){return schemeCategories[schemeId(p)];},
[&](auto at,auto p,int value){std::cout<<"q "<<at<<' '<<schemeId(p)<<' '<<value<<' ';resolverMutate(1,at);},[&](auto at,auto p,auto value){std::cout<<"v "<<at<<' '<<schemeId(p)<<' '<<value<<' ';resolverMutate(2,at);}};
RadarPixelActorWorld actorWorld{colorWorld,houseMode,schemeWorld,[&](const void* p)->const void*{return &typeIds[aid(p)];},[&](const void* p)->const std::uint8_t&{for(int i=0;i<3;++i)if(p==&typeIds[i])return typeFlags[i];throw std::invalid_argument("Foreign radar type");},[&](const void* p){const auto i=hid(p);need(i>=0);return RadarPixelHouseFields{humanFlags[i],controlFlags[i],houseColors[i]};},[&](const void* p)->RadarPixelTimer{const auto i=aid(p);return {starts[i],remaining[i]};}};
RadarPixelActorProbes actorProbes{
[&](const void* p,auto value){std::cout<<"L "<<hid(p)<<' '<<unsigned(value)<<' ';mutate(5);},[&](const void* p,const void*){std::cout<<"T "<<aid(p)<<' ';mutate(6);},
[&](const void* h,const void* p,auto value){std::cout<<"A "<<hid(h)<<' '<<aid(p)<<' '<<unsigned(value)<<' ';mutate(7);},
{[&](const void* p,auto value){std::cout<<"C "<<aid(p)<<' '<<unsigned(value)<<' ';mutate(8);},[&](const void* p,auto arg,const void* h){need(arg==0);std::cout<<"O "<<aid(p)<<' '<<hid(h)<<' ';mutate(9);}},
[&](const auto* p){std::cout<<"r "<<schemeId(p)<<" S ";mutate(10);}};
RadarActorsBinding actorBinding(s,actorWorld,actorProbes);
