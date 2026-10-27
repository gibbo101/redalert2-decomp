// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResourceTypeInputs.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
template<class F>void refuses(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}if(!caught)throw std::runtime_error("Unsafe resource profile accepted");}
int main(){try{
    ResourceTypeInputs t;ResourceTypeRegistry a,b;ResourceConstructionServices construction;ResourceIniServices ini;
    refuses([&]{constructResourceType(t,"Test",a,b,construction);});
    refuses([&]{readResourceTypeIni(t,ini);});
    ini.base=[](auto&){return false;};
    if(readResourceTypeIni(t,ini))throw std::runtime_error("Rejected base INI changed result");
    refuses([&]{mapResourceInputs(t);});
    OverlayTypeInputs image;image.index=71;t.image=&image;t.index=3;t.numImages=12;t.numSlopes=8;t.numFrames=12;t.value=25;
    const auto resource=mapResourceInputs(t);
    if(resource.index!=3||resource.imageIndex!=71||resource.numSlopes!=8)throw std::runtime_error("Stored image index was replaced by registry slot");
    ResourceListServices list;
    if(!readResourceTypeList(0,a,b,list)||!readResourceTypeList(-1,a,b,list))throw std::runtime_error("Empty resource list did not return true");
    refuses([&]{readResourceTypeList(1,a,b,list);});
    a.slots={&t};a.count=1;unsigned allocations=0,reads=0;
    list.entry=[](int){return ResourceListEntry{"-1","Ignored",1};};list.numericKey=[](auto){return -1;};
    list.allocate=[&]()->ResourceTypeInputs*{++allocations;return nullptr;};list.readIni=[&](auto&){++reads;return true;};
    refuses([&]{readResourceTypeList(1,a,b,list);});
    list.numericKey=[](auto){return 1;};refuses([&]{readResourceTypeList(1,a,b,list);});
    if(allocations!=1||reads)throw std::runtime_error("Refused list reached INI");
    // Signed nonpositive read results must skip parsing and allocation.
    list.entry=[](int){return ResourceListEntry{"-1","Ignored",-1};};
    if(!readResourceTypeList(1,a,b,list)||allocations!=1)throw std::runtime_error("Nonpositive read reached key parsing");
    // Existing numeric slots keep their identity even when the value differs.
    list.entry=[](int){return ResourceListEntry{"0","Different",1};};list.numericKey=[](auto){return 0;};
    list.readIni=[&](auto& v){if(&v!=&t)throw std::runtime_error("Wrong existing resource");++reads;return false;};
    if(!readResourceTypeList(1,a,b,list)||reads!=1||allocations!=1)throw std::runtime_error("Existing resource list association failed");
    std::cout<<"Resource registry/list/base/image safety boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
