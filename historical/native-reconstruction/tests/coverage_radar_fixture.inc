// SPDX-License-Identifier: GPL-3.0-or-later
std::uint8_t activeCoverage=coverageFields[1];std::int32_t coverageRange=coverageFields[2];
const std::int8_t coverageTypeRange=coverageFields[3];
std::array<std::int32_t,3> coveragePosition{std::int32_t(coverageFields[5]),std::int32_t(coverageFields[6]),std::int32_t(coverageFields[7])};
std::array<std::uint8_t,3> coverageHouseDirty{255,254,253};
std::uint8_t coverage13D=coverageFields[8],coverage566A=coverageFields[9];
std::array<std::int32_t,4> coverage130,coverage134;coverage130.fill(coverageFields[10]);coverage134.fill(coverageFields[11]);
// The actor direct Owner is shared with radar.
owners[0]=&houses[coverageFields[12]];
auto cstore=[&](char kind,int offset,int value){std::cout<<"u "<<kind<<' '<<offset<<' '<<value<<' ';};
TechnoCoverageServices coverage{current,{},{},{},[&]{return owners[0];},
 [&](const void* h){const auto i=hid(h);const auto value=std::uint8_t(unitOwnerTypeVisible(houseMode,humanFlags[i],controlFlags[i],h==current));std::cout<<"l "<<i<<' '<<unsigned(value)<<' ';return value;},
 [&](const void* h,const void* q){const auto i=hid(h),j=hid(q);const auto value=std::uint8_t(unitOwnerAlliedToCurrent(q!=nullptr,h==q,houseIndexes[i],j<0?0:houseIndexes[j],houseAllies[i]));std::cout<<"b "<<i<<' '<<j<<' '<<unsigned(value)<<' ';return value;},
 [&](const void* h){return TechnoCoverageHouse{coverage13D,coverage566A,coverageHouseDirty[hid(h)]};},
 [&](std::int32_t z){const auto value=projectVisibilityHeight(z,.125);std::cout<<"z "<<z<<' '<<value<<' ';return value;}, {},{},
 [](auto value){std::cout<<"d "<<value<<' ';},cstore};
// Stock30C/80->84/3C share this actor/type/Owner with the radar services.
const void* coverageType=&typeIds[0];std::int32_t coverageHealth=1,coverageDummy=0;
std::uint8_t coverageEnabled=coverageFields[4],coverageZero=0;const void* coverageNull=nullptr;
MissionBuildingTargetServices availability;
availability.type=[&](const void* p){need(p==coverageType);return MissionBuildingTargetType{coverageZero,coverageDummy,coverageZero,coverageZero};};
StockTechnoCoverageServices stock{coverageType,[&](const void* p)->const std::int8_t&{need(p==coverageType);return coverageTypeRange;},[&]{return owners[0];},
 [&]{return MissionBuildingTarget{&actors[0],coverageHealth,coverageDummy,coverageDummy,coverageZero,coverageEnabled,coverageDummy,coverageDummy,coverageType,MissionExpirationOwnerView{[&]{return owners[0];},[](const void*){throw std::logic_error("Unexpected coverage Owner write");}},coverageZero,coverageZero,coverageNull,coverageNull,coverageDummy,coverageNull,coverageNull};},availability};
StockTechnoCoverageBinding stockBinding(coverage,actorKinds[0]==RadarColorActorKind::building?StockCoverageKind::Building:StockCoverageKind::Infantry,stock);
const auto allowed=coverage.allowed30C;const auto rangeGetter=coverage.typeRangeADE;const auto ownerGetter=coverage.owner3C;
coverage.allowed30C=[&]{const auto result=allowed();std::cout<<"p "<<unsigned(result)<<' ';return result;};
coverage.typeRangeADE=[&]{const auto result=rangeGetter();std::cout<<"a "<<int(result)<<' ';return result;};
coverage.owner3C=[&]{const auto result=ownerGetter();std::cout<<"o "<<hid(result)<<' ';return result;};
#ifdef RA2_COVERAGE_RADAR_REFRESH
#define RA2_REFRESH_SETUP_ONLY
#include "radar_refresh_fixture.inc"
#undef RA2_REFRESH_SETUP_ONLY
CoverageRadarWorld coverageWorld{radarMap,[&](MapCellInput& c){const auto i=&c-terrain.data();need(i>=0&&i<4);return TechnoCoverageCell{flags12c[i],coverage130[i],coverage134[i],counts[i]};},[](auto p){std::cout<<"w "<<p.x<<' '<<p.y<<' ';}};
for(int stage=0;stage<refreshFields[1];++stage){
 mode=refreshFields[0]^stage;std::cout<<"step "<<mode<<' ';
 CoverageRadarRefreshBinding bind(coverage,refresh,s,coverageWorld,scratch,shared);
 changeTechnoCoverage(bool(coverageFields[0])^(stage!=0),{activeCoverage,coverageRange,coveragePosition[0],coveragePosition[1],coveragePosition[2]},coverage);
}
#else
SurfaceRefreshScratch coverageScratch{};
SurfaceRefreshServices coverageRefresh{mode,first,second,{}, {}};
CoverageRadarWorld coverageWorld{radarMap,[&](MapCellInput& c){const auto i=&c-terrain.data();need(i>=0&&i<4);return TechnoCoverageCell{flags12c[i],coverage130[i],coverage134[i],counts[i]};},[](auto p){std::cout<<"w "<<p.x<<' '<<p.y<<' ';}};
{CoverageRadarBinding bind(coverage,coverageRefresh,s,coverageWorld,coverageScratch);
 changeTechnoCoverage(bool(coverageFields[0]),{activeCoverage,coverageRange,coveragePosition[0],coveragePosition[1],coveragePosition[2]},coverage);}
// Match the last borrowed stack point only when a radar pixel actually ran.
// Coverage early exits leave the caller's original point untouched.
if(coverageRadarDrew)
 point=coverageScratch.source;

#endif
