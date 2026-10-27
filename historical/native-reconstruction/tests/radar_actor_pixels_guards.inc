// SPDX-License-Identifier: GPL-3.0-or-later
{
int actor=0,house=0,typeId=0;const void* owner=&house;const void* liveHouse=&house;std::uint8_t byte170=255,typeByte=1,human=0,control=1;std::int32_t index=0,localMode=0;std::uint32_t mask=0;std::array<std::uint8_t,3> rgb{1,2,3};int borrowedReads=0;
RadarColorWorld colors{liveHouse,[&](const void* p){need(p==&actor);++borrowedReads;return RadarColorActor{RadarColorActorKind::infantry,byte170,[&]{return owner;},[]{return nullptr;}};},[&](const void*){return RadarColorHouse{index,mask};},{}};
SurfaceMarkScheme onlyScheme{nullptr,0x3456};std::array<const SurfaceMarkScheme*,1> one{&onlyScheme};std::span<const SurfaceMarkScheme*> registry=one;std::int32_t n=1;std::uint32_t locale=0;SchemeResolverWorld resolver{registry,n,locale,[](auto){return std::string_view("LightGrey");},[](auto){return 1;},{},{}};
RadarPixelActorWorld worldActors{colors,localMode,resolver,[&](auto)->const void*{return &typeId;},[&](auto)->const std::uint8_t&{return typeByte;},[&](auto){return RadarPixelHouseFields{human,control,rgb};},[&](auto)->RadarPixelTimer{return {index,index};}};RadarPixelActorProbes probes;
const void* savedCurrent=current;current=liveHouse;// Rebind to the service's actual current reference owner.
RadarColorWorld sameCurrent{current,colors.actor,colors.house,{}};RadarPixelActorWorld sharedActors{sameCurrent,localMode,resolver,worldActors.type,worldActors.typeByte1FF,worldActors.house,worldActors.timer};
int restored=0;s.actorC0=[&](auto){++restored;return std::uint8_t(7);};
{RadarActorsBinding bind(s,sharedActors,probes);need(borrowedReads==0);need(s.local4F52B0(owner)==1&&s.typeFlag1FF(&actor)==1&&s.alliedObject4E5580(owner,&actor)==1&&s.actorC0(&actor)==255&&s.actorCC(&actor,0)==owner&&s.resolve663D30(1)==&onlyScheme);}
need(s.actorC0(&actor)==7&&restored==1);
bool actorFault=false;try{RadarActorsBinding bind(s,sharedActors,probes);locale=1;s.resolve663D30(1);}catch(const std::invalid_argument&){actorFault=true;}need(actorFault&&s.actorC0(&actor)==7&&restored==2);current=savedCurrent;
}
