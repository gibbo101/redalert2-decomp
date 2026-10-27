// SPDX-License-Identifier: GPL-3.0-or-later
{
RefreshSurfaceVirtuals sharedTable;sharedTable.width7C=refreshSurfaceWidth;sharedTable.height80=refreshSurfaceHeight;sharedTable.rect78=refreshSurfaceRect;
RefreshSurface sharedSurface{&sharedTable,1,1};auto* savedSurface=surface;surface=&sharedSurface;
std::array<std::uint8_t,16> pixelsBacking{};std::int32_t sharedDepth=0,sharedFormat=2;std::uint32_t sharedOffset=0;int ownerReads=0,restoredCalls=0;
CopySurface sharedOwner{sharedSurface,{sharedSurface.width,sharedDepth,sharedFormat,sharedOffset,pixelsBacking,{},true},{},{},{},{}};
SurfaceCopyServices owners{[&](auto& receiver)->CopySurface&{++ownerReads;need(&receiver==&sharedSurface);return sharedOwner;}};
SurfaceMarkBuckets emptyBuckets{};auto* savedBuckets=buckets;buckets=&emptyBuckets;
std::array<std::uint8_t,8> bitmapBytes{};SurfaceMarkBitmap bitmap{bitmapBytes,0};auto* bitmapRef=&bitmap;std::span<const SurfaceMarkScheme*> registry;
std::int32_t count=0;std::uint32_t locale=0;RadarColorWorld colors{current,{},{},{}};SchemeResolverWorld resolver{registry,count,locale,{},{},{},{}};
RadarPixelActorWorld actors{colors,mode,resolver,{},{},{},{}};
SurfaceMarkServices marks{surface,buckets,bitmapRef,registry,{},{},[&](auto){++restoredCalls;return std::uint8_t(9);},{},{},{},{}};
SurfaceRefreshServices refresh{mode,surface,surface,[&]{++restoredCalls;},[&](auto&){++restoredCalls;}};
sharedTable.copy8=[&](auto&,auto*,auto*,auto*,auto,auto){++restoredCalls;};std::array<RefreshSurfaceVirtuals*,1> tables{&sharedTable};SurfaceRefreshScratch scratch{};
mode=0;
{RadarRefreshBinding bind(refresh,marks,s,actors,tables,owners);need(ownerReads==0);refreshSurfaces(refresh,scratch);need(sharedDepth==0);mode=1;refreshSurfaces(refresh,scratch);}
need(marks.actorC0(nullptr)==9);refresh.finish6324A0();refresh.pixel632000(point);sharedTable.copy8(sharedSurface,&point,&sharedSurface,&point,0,1);need(restoredCalls==4);
bool fault=false;sharedTable.width7C=[](auto&)->std::int32_t{throw std::runtime_error("shared width fault");};mode=0;
try{RadarRefreshBinding bind(refresh,marks,s,actors,tables,owners);refreshSurfaces(refresh,scratch);}catch(const std::runtime_error&){fault=true;}need(fault);refresh.finish6324A0();need(restoredCalls==5);
std::span<const SurfaceMarkScheme*> foreignRegistry;SurfaceMarkServices foreign{surface,buckets,bitmapRef,foreignRegistry,{},{},{},{},{},{},{}};
bool refused=false;try{RadarRefreshBinding bind(refresh,foreign,s,actors,tables,owners);}catch(const std::invalid_argument&){refused=true;}need(refused);
std::array<RefreshSurfaceVirtuals*,2> duplicate{&sharedTable,&sharedTable};refused=false;try{RadarRefreshBinding bind(refresh,marks,s,actors,duplicate,owners);}catch(const std::invalid_argument&){refused=true;}need(refused);
// Retaining a device copy is explicit, including absent-entry refusal. Pixel
// virtuals resolve the actual receiver even when the saved table differs.
sharedTable.width7C=refreshSurfaceWidth;
RadarRefreshSurfacePolicy retain{[](auto*){return true;}};
const auto oldCopy=sharedTable.copy8;sharedTable.copy8={};refused=false;
try{RadarRefreshBinding bind(refresh,marks,s,actors,tables,owners,{},retain);}catch(const std::invalid_argument&){refused=true;}
need(refused&&!sharedTable.copy8);sharedTable.copy8=oldCopy;
int locks=0,unlocks=0,formats=0;bool nullLock=false;
sharedOwner.lock5C=[&](auto x,auto y)->std::optional<std::uint32_t>{++locks;need(x==0&&y==0);if(nullLock)return {};return 0;};
sharedOwner.bytes70=[&]{++formats;return 2;};sharedOwner.unlock60=[&]{++unlocks;};
RefreshRect pixelPoint{};
{
    RadarRefreshBinding bind(refresh,marks,s,actors,tables,owners,{},retain);
    const auto beforeCalls=restoredCalls;mode=0;refreshSurfaces(refresh,scratch);
    need(restoredCalls==beforeCalls+1&&locks==0); // Retained copy, empty marks.
    s.pixels(&sharedTable).set24(sharedSurface,pixelPoint,0xabcd);
    need(s.pixels(&sharedTable).get28(sharedSurface,pixelPoint)==0xabcd&&locks==2&&unlocks==2&&formats==2&&sharedDepth==0);
    nullLock=true;s.pixels(&sharedTable).set24(sharedSurface,pixelPoint,0);
    need(s.pixels(&sharedTable).get28(sharedSurface,pixelPoint)==0&&locks==4&&unlocks==2&&formats==2&&pixelsBacking[0]==0xcd);
    nullLock=false;sharedOwner.unlock60={};refused=false;
    try{s.pixels(&sharedTable).get28(sharedSurface,pixelPoint);}catch(const std::invalid_argument&){refused=true;}
    need(refused&&locks==4); // Incomplete alternate services refuse before entry.
}
surface=savedSurface;buckets=savedBuckets;
}
