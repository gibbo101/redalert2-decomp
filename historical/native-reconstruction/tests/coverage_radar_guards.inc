// SPDX-License-Identifier: GPL-3.0-or-later
{
int coverageQueries=0,oldCellCalls=0,oldRefreshCalls=0,oldPixelCalls=0;
std::int32_t c130=0,c134=0,c13c=0;std::uint32_t cFlags=0,otherFlags=0;
TechnoCoverageServices service{current,{},{},{},{},{},{},{},{},[&](auto,auto){++oldCellCalls;return TechnoCoverageCell{cFlags,c130,c134,c13c};},[&]{++oldRefreshCalls;},{},{}};
SurfaceRefreshServices refresh{mode,surface,surface,{},[&](auto&){++oldPixelCalls;}};SurfaceRefreshScratch scratch{};
RadarMapWorld map{floorWorld,[&](const auto&)->RadarMapDiscoveryFields{++coverageQueries;return {cFlags,c13c};}};
CoverageRadarWorld owners{map,[&](auto&){++coverageQueries;return TechnoCoverageCell{cFlags,c130,c134,c13c};},{}};
{CoverageRadarBinding bind(service,refresh,s,owners,scratch);need(coverageQueries==0);auto c=service.cell(0,0);c.count13C=7;need(c13c==7&&coverageQueries==2);}
service.cell(0,0);service.refresh634030();refresh.pixel632000(point);need(oldCellCalls==1&&oldRefreshCalls==1&&oldPixelCalls==1);
bool mismatch=false;owners.coverage=[&](auto&){return TechnoCoverageCell{otherFlags,c130,c134,c13c};};
try{CoverageRadarBinding bind(service,refresh,s,owners,scratch);service.cell(0,0);}catch(const std::invalid_argument&){mismatch=true;}
need(mismatch);service.refresh634030();need(oldRefreshCalls==2);
const void* different=current;TechnoCoverageServices foreign{different,{},{},{},{},{},{},{},{},{},{},{},{}};
bool refusedOwner=false;try{CoverageRadarBinding bind(foreign,refresh,s,owners,scratch);}catch(const std::invalid_argument&){refusedOwner=true;}need(refusedOwner);
bool refusedZero=false;mode=0;try{CoverageRadarBinding bind(service,refresh,s,owners,scratch);service.refresh634030();}catch(const std::invalid_argument&){refusedZero=true;}need(refusedZero);service.refresh634030();need(oldRefreshCalls==3);
}
