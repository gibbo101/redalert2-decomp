// SPDX-License-Identifier: GPL-3.0-or-later
{
RefreshSurfaceVirtuals table;table.width7C=refreshSurfaceWidth;table.height80=refreshSurfaceHeight;table.rect78=refreshSurfaceRect;
RefreshSurface record{&table,1,1};auto* previousSurface=surface;surface=&record;
SurfaceMarkBuckets roots{};auto* previousBuckets=buckets;buckets=&roots;
std::array<std::uint8_t,16> backing{};std::int32_t depth=0,bpp=2;std::uint32_t offset=0;int views=0,restored=0;
CopySurface owner{record,{record.width,depth,bpp,offset,backing,{},true},{},{},{},{}};
SurfaceCopyServices surfaces{[&](auto& receiver)->CopySurface&{++views;need(&receiver==&record);return owner;}};
std::array<std::uint8_t,8> bitmapBytes{};SurfaceMarkBitmap bitmap{bitmapBytes,0};auto* bitmapRef=&bitmap;std::span<const SurfaceMarkScheme*> registry;
std::int32_t n=0;std::uint32_t locale=0;RadarColorWorld colors{current,{},{},{}};SchemeResolverWorld resolver{registry,n,locale,{},{},{},{}};RadarPixelActorWorld actors{colors,mode,resolver,{},{},{},{}};
SurfaceMarkServices marks{surface,buckets,bitmapRef,registry,{},{},{},{},{},{},{}};SurfaceRefreshServices refresh{mode,surface,surface,{},{}};SurfaceRefreshScratch scratch{};std::array<RefreshSurfaceVirtuals*,1> tables{&table};
RadarRefreshBinding association(refresh,marks,s,actors,tables,surfaces);need(views==0&&association.binds(refresh,s));
TechnoCoverageServices target{current,{},{},{},{},{},{},{},{},{},[&]{++restored;},{},{}};
std::uint32_t flags=0;std::int32_t c130=0,c134=0,c13c=0;int fields=0;
RadarMapWorld map{floorWorld,[&](const auto&)->RadarMapDiscoveryFields{++fields;return {flags,c13c};}};
CoverageRadarWorld world{map,[&](auto&){++fields;return TechnoCoverageCell{flags,c130,c134,c13c};},{}};
mode=0;{CoverageRadarRefreshBinding bind(target,refresh,s,world,scratch,association);need(fields==0&&views==0);target.cell(0,0).count13C=3;target.refresh634030();need(c13c==3&&depth==0);}
target.refresh634030();need(restored==1);
SurfaceRefreshServices other{mode,surface,surface,{},{}};bool refused=false;
try{CoverageRadarRefreshBinding bind(target,other,s,world,scratch,association);}catch(const std::invalid_argument&){refused=true;}need(refused);target.refresh634030();need(restored==2);
bool propagated=false;table.height80=[](auto&)->std::int32_t{throw std::runtime_error("coverage mark fault");};
try{CoverageRadarRefreshBinding bind(target,refresh,s,world,scratch,association);target.refresh634030();}catch(const std::runtime_error&){propagated=true;}need(propagated);target.refresh634030();need(restored==3);
surface=previousSurface;buckets=previousBuckets;
}
