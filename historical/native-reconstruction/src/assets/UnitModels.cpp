// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitModels.hpp"
#include <algorithm>
#include <stdexcept>

namespace ra2 {
bool loadOrdinaryUnitModels(OrdinaryUnitModels& type,const UnitModelServices& s) {
    // Native safety/domain guards, not recovered malformed-input behavior.
    if(!type.turret || type.turretCount!=0 || type.image.empty() || type.image.size()>24 ||
       type.image.find_first_of("/\\:\0",0,4)!=std::string::npos)
        throw std::invalid_argument("Ordinary Unit models require a bounded image, turret and zero turret count");
    auto stored=[&](ModelField field,int index,ModelToken value){if(s.stored)s.stored(field,index,value);};
    auto kind=[&]{if(s.queryKind)s.queryKind();};
    auto multiple=[&]{if(s.queryMultipleTurrets)s.queryMultipleTurrets();};
    auto discard=[&](ModelKind k,ModelToken& value,int part,bool clear) {
        if(!value)return;
        s.destroy(k,value);s.release(value);
        if(clear){value=0;stored(k==ModelKind::Voxel?ModelField::Voxel:ModelField::Animation,part,0);}
    };
    bool failed=false;
    auto loadPair=[&](int part,std::string_view stem,ModelToken voxelFile) {
        auto& pair=type.parts[part];
        discard(ModelKind::Voxel,pair.voxel,part,false);
        const auto voxel=s.allocate(ModelKind::Voxel);
        if(voxel)s.construct(ModelKind::Voxel,voxel,voxelFile);
        pair.voxel=voxel;
        stored(ModelField::Voxel,part,pair.voxel);
        if(!pair.voxel || s.errorByte(pair.voxel))failed=true;
        const auto animationFile=s.open(std::string(stem)+".HVA");
        discard(ModelKind::Animation,pair.animation,part,false);
        const auto animation=s.allocate(ModelKind::Animation);
        if(animation)s.construct(ModelKind::Animation,animation,animationFile);
        pair.animation=animation;
        stored(ModelField::Animation,part,pair.animation);
        if(!pair.animation || s.errorByte(pair.animation))failed=true;
        else s.associateAnimation(pair.animation,s.section(pair.voxel,0).animationAssociation);
        s.close(animationFile);
    };
    const auto bodyFile=s.open(type.image+".VXL");
    if(s.available(bodyFile))loadPair(0,type.image,bodyFile);
    else failed=true;
    kind();kind();multiple();
    const std::string turretStem=type.image+"TUR";
    const auto turretFile=s.open(turretStem+".VXL");
    // Missing optional parts retain their old records; they do not set failure.
    if(s.available(turretFile))loadPair(1,turretStem,turretFile);
    s.close(turretFile);
    kind();kind();multiple();
    const std::string barrelStem=type.image+"BARL";
    const auto barrelFile=s.open(barrelStem+".VXL");
    if(s.available(barrelFile))loadPair(2,barrelStem,barrelFile);
    s.close(barrelFile);
    if(failed) {
        discard(ModelKind::Voxel,type.parts[0].voxel,0,true);
        discard(ModelKind::Animation,type.parts[0].animation,0,true);
        kind();multiple();
        discard(ModelKind::Voxel,type.parts[1].voxel,1,true);
        discard(ModelKind::Animation,type.parts[1].animation,1,true);
        // The ordinary original failure branch does not clear the barrel.
    } else {
        const auto body=type.parts[0].voxel;
        int maximum=s.section(body,0).dimensions[0];
        for(int i=0;i<s.sectionCount(body);++i)for(int axis=0;axis<3;++axis) {
            const int candidate=s.section(body,i).dimensions[axis];
            // Equality deliberately repeats the getter, just like a larger value.
            if(maximum<=candidate)maximum=s.section(body,i).dimensions[axis];
        }
        type.maximumDimension=std::max(8,maximum);
        stored(ModelField::MaximumDimension,0,ModelToken(type.maximumDimension));
        for(int i=0;i<4;++i) {
            auto& c=type.caches[i];s.release(c.pointer);
            c.pointer=0;stored(ModelField::CachePointer,i,0);
            c.count=0;stored(ModelField::CacheCount,i,0);
            c.capacity=0;stored(ModelField::CacheCapacity,i,0);
            c.flag=0;stored(ModelField::CacheFlag,i,0);
            c.tail=0;stored(ModelField::CacheTail,i,0);
        }
    }
    s.close(bodyFile);
    return !failed;
}
}
