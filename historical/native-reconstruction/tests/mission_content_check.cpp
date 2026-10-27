// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MissionDefinition.hpp"
#include "assets/StringTable.hpp"
#include "assets/PreparedStringLookup.hpp"
#include <iostream>
using namespace ra2;
namespace {
void require(bool value){if(!value)throw std::runtime_error("Mission content check failed");}
template<class F>void rejects(F f){bool failed=false;try{f();}catch(const std::exception&){failed=true;}require(failed);}
void word(Bytes& bytes,std::uint32_t value){for(int i=0;i<4;++i)bytes.push_back(std::uint8_t(value>>(i*8)));}
Bytes csf(const std::u16string& text,bool extra=false) {
    Bytes bytes;for(auto value:{0x43534620u,3u,1u,1u,0u,0u,0x4c424c20u,1u,4u})word(bytes,value);
    bytes.insert(bytes.end(),{'T','e','s','t'});word(bytes,extra?0x53545257:0x53545220);word(bytes,std::uint32_t(text.size()));
    for(auto c:text){const auto inverted=c^65535;bytes.push_back(std::uint8_t(inverted));bytes.push_back(std::uint8_t(inverted>>8));}
    if(extra){word(bytes,3);bytes.insert(bytes.end(),{'t','a','g'});}return bytes;
}
}
int main(){try {
    const std::string source="[Basic]\nNewINIFormat=4\nPlayer=Blue\nBriefing=Test\n[Houses]\n0=Blue\n[Triggers]\nAlpha=Blue,<none>,Start,0,1,1,1,0\nBeta=Blue,Alpha,End,1,1,1,1,0\n[Events]\nAlpha=1,33,0,0\nBeta=2,36,0,2,13,0,9\n[Actions]\nAlpha=2,11,4,Test,0,0,0,0,AB,53,2,Beta,0,0,0,0,A\nBeta=0\n[Tags]\nTagA=0,Player,Alpha\n[CellTags]\n12034=TagA\n[VariableNames]\n2=Counter,0\n[Infantry]\n10=Blue,Scout,256,2,4,3,Guard,64,TagA,0,-1,0,1,0\n2=Blue,Scout,200,1,4,2,Guard,0,None,0,-1,0,1,0\n";
    const auto mission=readMissionDefinition(Ini(source));require(mission.triggers.size()==2&&mission.actors.size()==2&&mission.actors[0].key==2&&mission.actors[1].key==10);
    require(mission.actors[1].fields[5]=="3"&&mission.actors[1].tag=="taga"&&mission.actors[1].facing==64);
    require(mission.cellTags.at({34,12})=="taga"&&mission.variables.at(2).name=="Counter");
    const auto& start=mission.triggers.at("alpha");require(start.actions.size()==2&&start.actions[0].arguments[5]=="AB"&&start.actions[1].arguments[0]=="Beta");
    const auto structures=readMissionDefinition(Ini(source+"[Structures]\n7=Blue,Tower,256,3,4,128,TagA,1,0,1,0,0,None,None,None,0,0\n"));
    require(structures.actors.back().kind==MissionActorKind::Structure&&structures.actors.back().fields.size()==17&&structures.actors.back().facing==128);
    require(mission.triggers.at("beta").events[0].kind==36&&mission.triggers.at("beta").events[1].kind==13);
    for(const auto& tail:{"[Actions]\nAlpha=1,11,4,Test\n","[Tags]\nBad=0,Bad,Absent\n","[CellTags]\n999=Absent\n","[Infantry]\n3=Blue,Scout,broken\n","[Events]\nBeta=-1\n","[Triggers]\nBeta=Blue,Missing,End,0,0,0,0,0\n","[Infantry]\n02=Blue,Scout,256,2,4,3,Guard,64,None,0,-1,0,1,0\n"})
        rejects([&]{(void)readMissionDefinition(Ini(source+tail));});
    rejects([&]{(void)readMissionDefinition(Ini("[Basic]\nNewINIFormat=3\n"));});
    auto table=readStringTable(Data(csf(u"Hello \u00e9 \U0001f680",true)));
    require(localizedText(table,"TEST")=="Hello \xc3\xa9 \xf0\x9f\x9a\x80"&&table.at("test")[0].extra=="tag");
    const PreparedStringLookup prepared(Data(csf(u"Hello \u00e9 \U0001f680",true)));
    require(prepared.text("tEsT")==localizedText(table,"TEST"));
    rejects([&]{(void)prepared.text("Missing");});
    rejects([&]{(void)localizedText(table,"Missing");});
    for(const std::u16string text:{std::u16string{char16_t(0xd800)},std::u16string{char16_t(0xdc00)},std::u16string{char16_t(0xd800),u'a'}})
        rejects([&]{(void)readStringTable(Data(csf(text)));});
    const auto valid=csf(u"Hello");
    auto duplicate=valid;duplicate[8]=2;duplicate[12]=2;duplicate.insert(duplicate.end(),valid.begin()+24,valid.end());
    const auto repeated=readStringTable(Data(duplicate));require(repeated.at("test").size()==2);rejects([&]{(void)localizedText(repeated,"Test");});
    const PreparedStringLookup ambiguous{Data(duplicate)};rejects([&]{(void)ambiguous.text("TEST");});
    for(std::size_t length=0;length<valid.size();++length)rejects([&]{(void)readStringTable(Data(Bytes(valid.begin(),valid.begin()+length)));});
    auto trailing=valid;trailing.push_back(0);rejects([&]{(void)readStringTable(Data(trailing));});
    std::cout<<"Mission content, graph references, UTF-8/surrogate and truncation checks PASS\n";return 0;
}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
