// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamObserverConstruction.hpp"
namespace ra2 {
namespace {
void store(const TeamObserverConstructionStore& f,const void* p,std::int64_t off,
           std::uint32_t n,std::uint64_t v=0,const void* pointer=nullptr){if(f)f(p,off,n,v,pointer);}
// strncpy's source is read live after preceding constructor stores. Reconstruct
// its bounded zero padding rather than exposing uninitialized scratch bytes.
std::array<std::uint8_t,24> boundedIdentifier(std::span<const std::uint8_t> input){
    std::array<std::uint8_t,24> out{};
    for(std::size_t i=0;i<out.size();++i){
        if(i>=input.size())throw std::invalid_argument("Observer identifier backing ends before terminator");
        if(!input[i])break;
        out[i]=input[i];
    }
    return out;
}
}
void constructTeamObserverType(TeamObserverType& r,
        std::optional<std::span<const std::uint8_t>> identifier,
        const TeamObserverConstructionServices& s){
    const auto emit=[&](std::int64_t off,std::uint32_t n,std::uint64_t v=0,const void* p=nullptr){store(s.store,&r,off,n,v,p);};
    struct BaseAdapter {
        std::function<void(TeamObserverType&,unsigned)> projectInterfaces;
        MissionTagStore store;
    } base;
    base.projectInterfaces=[&](auto&,unsigned phase){if(s.projectInterfaces)s.projectInterfaces(&r,phase);};
    base.store=[&](const void*,auto off,auto v,const void* p){emit(off,off==0x14||off==0x20?1:4,v,p);};
    constructTeamAbstractBase(r,base); // existing complete40FF10 kernel
    r.identifier24[0]=0;emit(0x24,1);
    r.byte3D=0;emit(0x3d,1);
    r.name64[0]=0;emit(0x64,1);
    if(s.projectInterfaces)s.projectInterfaces(&r,3);
    std::array<std::uint8_t,24> name;
    if(identifier)name=boundedIdentifier(*identifier);
    else{
        if(!s.formatNullName)throw std::invalid_argument("Observer null-name CRT service unbound");
        name=s.formatNullName(&r);
        // The format result is copied through the same bounded strncpy service.
        name=boundedIdentifier(name);
    }
    for(unsigned i=0;i<6;++i){
        std::uint32_t word=0;for(unsigned j=0;j<4;++j){r.identifier24[i*4+j]=name[i*4+j];word|=std::uint32_t(name[i*4+j])<<(j*8);}
        emit(0x24+i*4,4,word);
    }
    r.identifier24[24]=0;emit(0x3c,1);
    // The second bounded copy reads the just-stored ID, including any post-store
    // instrumentation changes, not the earlier scratch/source buffer.
    std::array<std::uint8_t,49> display{};bool ended=false;
    for(unsigned i=0;i<48;++i){
        if(!ended){if(i>=r.identifier24.size())throw std::invalid_argument("Observer identifier lost its terminator");ended=r.identifier24[i]==0;if(!ended)display[i]=r.identifier24[i];}
    }
    for(unsigned i=0;i<12;++i){
        std::uint32_t word=0;for(unsigned j=0;j<4;++j){r.name64[i*4+j]=display[i*4+j];word|=std::uint32_t(display[i*4+j])<<(j*8);}
        emit(0x64+i*4,4,word);
    }
    r.name64[48]=0;emit(0x94,1);
    r.text60=s.emptyText;emit(0x60,4,0,r.text60);
    struct RegistryAdapter {MissionTagStore store;} registration;
    registration.store=[&](const void* owner,auto off,auto v,const void* p){store(s.store,owner,off,4,v,p);};
    registerConstructedTeam(s.abstractTypesA40928,&r,registration);
    // Complete41C5C0 starts here; base registration precedes derived fields.
    r.condition98=-1;emit(0x98,4,0xffffffffu);r.valueA8=-1;emit(0xa8,4,0xffffffffu);
    const auto half=[&](double& value,std::uint32_t off,bool high){
        auto bits=std::bit_cast<std::uint64_t>(value);
        bits=high?(bits&0xffffffffull)|0x3ff0000000000000ull:bits&0xffffffff00000000ull;
        value=std::bit_cast<double>(bits);emit(off,4,high?0x3ff00000u:0u);
    };
    half(r.weightB8,0xb8,false);half(r.minimumC0,0xc0,false);half(r.maximumC8,0xc8,false);
    half(r.weightB8,0xbc,true);half(r.minimumC0,0xc4,true);half(r.maximumC8,0xcc,true);
    for(unsigned i=2;i<5;++i){r.flagsD0[i]=1;emit(0xd0+i,1,1);}
    r.value9C=0;emit(0x9c,4);r.valueA0=0;emit(0xa0,4);r.byteA4=0;emit(0xa4,1);
    r.valueAC=0;emit(0xac,4);r.valueB0=0;emit(0xb0,4);
    r.flagsD0[0]=0;emit(0xd0,1);r.flagsD0[1]=0;emit(0xd1,1);
    r.objectD8=nullptr;emit(0xd8,4);r.teamDC=nullptr;emit(0xdc,4);r.teamE0=nullptr;emit(0xe0,4);
    r.successes104=0;emit(0x104,4);r.trials108=0;emit(0x108,4);
    if(s.projectInterfaces)s.projectInterfaces(&r,0);
    for(unsigned i=0;i<8;++i){r.conditionsE4[i]=0;emit(0xe4+4*i,4);}
    registerConstructedTeam(s.observersA3D260,&r,registration);
}
void setTeamObserverPrimaryType(TeamObserverType& r,const void* type,const TeamObserverConstructionStore& f){
    r.teamDC=type;store(f,&r,0xdc,4,0,type);
}
void initializeTeamObserverRegistry(TeamConstructionRegistry& r,std::uint8_t& valid,
        const std::function<void()>& project,const std::function<void()>& atExit,
        const TeamObserverConstructionStore& f){
    r.entries.slots={};store(f,r.entries.identity,4,4);
    r.capacity=0;store(f,r.entries.identity,8,4);
    valid=1;store(f,r.entries.identity,12,1,1);
    r.allocated=0;store(f,r.entries.identity,13,1);
    if(!project)throw std::invalid_argument("Observer registry interface unbound");project();
    r.increment=10;store(f,r.entries.identity,20,4,10);
    r.entries.count=0;store(f,r.entries.identity,16,4);
    if(!atExit)throw std::invalid_argument("Observer registry exit service unbound");atExit();
}
}
