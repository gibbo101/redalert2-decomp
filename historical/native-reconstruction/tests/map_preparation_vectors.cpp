// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapPreparation.hpp"
#include "assets/MapCellChildren.hpp"
#include "render/MapLighting.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
std::string digest(const std::uint8_t* p,std::size_t size) {
    unsigned char h[32];unsigned n=0;if(!EVP_Digest(p,size,h,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Digest failed");
    std::ostringstream out;for(auto b:h)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(b);return out.str();
}
std::string digest(const Words& v) {Bytes b;for(auto n:v)for(int i=0;i<4;++i)b.push_back(std::uint8_t(n>>(i*8)));return digest(b.data(),b.size());}
std::uint32_t position(MapInputPosition p){return std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16);}
}
int main(int argc,char** argv){try{
    if(argc!=2)throw std::invalid_argument("Usage: map-preparation-vectors RENDER_DATA");
    const auto render=readRenderData(readFile(argv[1]));std::string line;
    while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op=0;int width=0,height=0,hole=-1;unsigned seed=0,cliff=0;
        MapLightSettings light;std::array<int,16> mapping;MapLATSettings lat;std::array<MapInputPosition,8> directions;std::array<float,11> speeds;
        in>>op>>width>>height>>seed>>hole>>cliff>>light.ambient>>light.tint[0]>>light.tint[1]>>light.tint[2]>>light.ground>>light.level;
        if((op!='P'&&op!='Q')||width<2||height<1||width+height>256||cliff>2)throw std::invalid_argument("Unsupported map preparation fixture");
        for(auto& n:mapping)in>>n;for(auto& n:lat)in>>n;
        for(auto& d:directions){std::uint32_t n=0;in>>n;d={std::bit_cast<std::int16_t>(std::uint16_t(n)),std::bit_cast<std::int16_t>(std::uint16_t(n>>16))};}
        for(auto& f:speeds){std::uint32_t n=0;in>>n;f=std::bit_cast<float>(n);}
        ResidentMapPreparationInputs resident;
        resident.width=width;resident.height=height;resident.permission={width,0,0,width,height};
        resident.landMap=mapping;resident.lat=lat;resident.directions=directions;resident.cliffMode=std::uint8_t(cliff);
        for(unsigned i=0;i<11;++i)resident.land[i].speed[unsigned(LandSpeed::Wheel)]=speeds[i];
        if(op=='Q') {
            for(auto& row:resident.land){for(auto& f:row.speed){std::uint32_t n=0;in>>n;f=std::bit_cast<float>(n);}unsigned b=0;in>>b;if(b>255)throw std::invalid_argument("Bad land byte");row.buildable=std::uint8_t(b);}
            auto& p=resident.permission;in>>p.dimension0>>p.originX>>p.originY>>p.width>>p.height;
            if(p.dimension0!=width)throw std::invalid_argument("Permission geometry differs");
            for(unsigned i=0;i<11;++i)if(std::bit_cast<std::uint32_t>(resident.land[i].speed[unsigned(LandSpeed::Wheel)])!=std::bit_cast<std::uint32_t>(speeds[i]))throw std::invalid_argument("Wheel fixture differs");
        }
        unsigned count=0;in>>count;if(count<1||count>1024)throw std::invalid_argument("Invalid registry capacity");
        std::vector<MapTileImageInput> images(count);std::vector<MapTileAttributes> types(count);
        for(unsigned i=0;i<count;++i) {
            int present=0;auto& image=images[i];in>>present;
            if(present!=0&&present!=1)throw std::invalid_argument("Bad image presence");
            if(op=='P') {
                int valid=0,ramp=0,land=0,extra=0;MapSubTileInput sub;
                in>>valid>>ramp>>land>>image.height>>sub.y>>sub.extraY>>extra;
                if((valid!=0&&valid!=1)||ramp<0||ramp>255||land<0||land>15||(extra!=0&&extra!=1))throw std::invalid_argument("Invalid TMP fixture");
                image.columns=image.rows=1;image.width=60;sub.ramp=std::uint8_t(ramp);sub.land=std::uint8_t(land);sub.extra=extra;
                image.subTiles.push_back(valid?std::optional{sub}:std::nullopt);
            } else {
                in>>image.columns>>image.rows>>image.width>>image.height;
                if(image.columns<1||image.columns>60||image.rows<1||image.rows>60||image.columns*image.rows>60)throw std::invalid_argument("Unsupported general TMP fixture");
                for(int j=0;j<image.columns*image.rows;++j){int valid=0,land=0,ramp=0,extra=0;MapSubTileInput sub;
                    in>>valid>>land>>ramp>>sub.y>>sub.extraY>>extra;
                    if((valid!=0&&valid!=1)||land<0||land>15||ramp<0||ramp>255||(extra!=0&&extra!=1))throw std::invalid_argument("Bad general TMP subheader");
                    sub.land=std::uint8_t(land);sub.ramp=std::uint8_t(ramp);sub.extra=extra;
                    image.subTiles.push_back(valid?std::optional{sub}:std::nullopt);
                }
            }
            if(present)types[i].image=&image;
        }
        in>>count;if(count>16384)throw std::invalid_argument("Too many map cells");std::vector<MapPreparationCell> cells(count);std::vector<int> slots(512*512,-1);std::vector<MapCellInput*> table(512*512);
        for(unsigned i=0;i<count;++i){auto& c=cells[i];auto& v=c.attributes.input;int x=0,y=0,sub=0,level=0,slope=0,extra=0,overlayData=0,ice=0;
            in>>x>>y>>v.tile>>sub>>level>>v.flags>>v.tube>>v.land>>slope>>extra>>overlayData>>ice>>c.attributes.passability>>c.field30;
            if(x<0||x>=512||y<0||y>=512||level<0||level>31||sub<0||sub>255||slope<0||slope>255||extra<0||extra>255||overlayData<0||overlayData>255||ice<0||ice>255||slots[std::size_t(y)*512+x]!=-1)throw std::invalid_argument("Invalid Cell fixture");
            v.position={std::int16_t(x),std::int16_t(y)};v.subTile=std::uint8_t(sub);v.level=std::int8_t(level);v.slope=std::uint8_t(slope);v.ice=std::uint8_t(ice);c.attributes.extraHeight=std::uint8_t(extra);c.attributes.overlayData=std::uint8_t(overlayData);
            const auto index=std::size_t(y)*512+x;slots[index]=int(i);table[index]=&v;
        }
        if(!in)throw std::invalid_argument("Incomplete map preparation fixture");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing map preparation fixture");
        if(hole>=0){if(std::size_t(hole)>=cells.size())throw std::invalid_argument("Missing hole cell");auto p=cells[std::size_t(hole)].attributes.input.position;slots[std::size_t(p.y)*512+p.x]=-1;table[std::size_t(p.y)*512+p.x]=nullptr;}
        Words events,visits;auto event=[&](unsigned id,unsigned field,std::uint32_t n){events.insert(events.end(),{id,field,n});};
        MapCellInput fallback;fallback.tile=65535;fallback.tube=-1;fallback.position={-1,-1};
        MapAttributeLookup world{table,&fallback,[&](MapInputPosition p){events.insert(events.end(),{304,position(p)});},[&](MapInputPosition p){events.insert(events.end(),{0xffffffffu,0,position(p)});}};
        const auto capacity=std::size_t(width+height+1)*(width+height+1);Bytes b4(capacity*4,0xa5),b10(capacity*10,0xa5);std::vector<std::array<std::uint32_t,9>> lights(cells.size());
        for(auto& l:lights){l.fill(0xa5a5u);l[0]=0;l[1]=0xa5a5a5a5u;}
        const auto attributes=[&](int id,unsigned entry){const auto& c=cells[std::size_t(id)].attributes;const auto& v=c.input;events.insert(events.end(),{entry,unsigned(id),unsigned(v.tile),unsigned(v.land),v.slope,std::uint8_t(v.level),c.extraHeight,unsigned(c.passability)});};
        MapPreparationServices services;
        services.visit=[&](int n){visits.push_back(unsigned(n));};
        services.store=[&](int id,MapPreparationField field,std::uint32_t v){event(unsigned(id),field==MapPreparationField::Field30?8u:9u,v);};
        services.initializeLighting=[&](int id){events.insert(events.end(),{301,unsigned(id)});const auto& v=cells[std::size_t(id)].attributes.input;const auto l=cellLight(render,light,v.position.x,v.position.y,v.level);auto& out=lights[std::size_t(id)];
            out={0,unsigned(l.scale),std::uint16_t(l.sourceIntensity),std::uint16_t(l.ambient),std::uint16_t(l.terrain),std::uint16_t(l.bridge),std::uint16_t(l.tint[0]),std::uint16_t(l.tint[1]),std::uint16_t(l.tint[2])};
            for(unsigned i=0;i<out.size();++i)event(unsigned(id),10+i,out[i]);
        };
        services.recalculate=[&](int id,int level){events.insert(events.end(),{302,unsigned(id),303,unsigned(id)});auto& c=cells[std::size_t(id)].attributes;
            const auto index=std::size_t(mapAttributeBufferIndex(c.input.position,width,height,int(capacity)));MapAttributeServices s;s.tiles=types;s.landMap=mapping;s.cliffMode=std::uint8_t(cliff);
            s.neighborLevel=[&](MapInputPosition p){return mapAttributeCell(p,world).level;};
            s.setupLAT=[&](const MapCellAttributes& state){attributes(id,305);auto copy=state.input;setupMapLAT(copy,lat,directions,world,int(types.size()),[&](int tile){event(unsigned(id),1,unsigned(tile));});return copy.tile;};
            s.updatePassability=[&](const MapCellAttributes& state){attributes(id,306);const bool permitted=mapCellPermitted(state.input.position,true,{width,0,0,width,height},world);const int n=emptyCellPassability(state.input,permitted,speeds);event(unsigned(id),7,unsigned(n));return n;};
            s.store=[&](MapAttributeField field,std::uint32_t n){switch(field){case MapAttributeField::Tile:event(unsigned(id),1,n);break;case MapAttributeField::SubTile:event(unsigned(id),2,n);break;case MapAttributeField::Land:event(unsigned(id),3,n);break;case MapAttributeField::Slope:event(unsigned(id),4,n);break;case MapAttributeField::Level:event(unsigned(id),5,n);break;case MapAttributeField::ExtraHeight:event(unsigned(id),6,n);break;case MapAttributeField::Buffer4:event(0xfffffffeu,unsigned(index*4+(n>>8)),n&255);break;case MapAttributeField::Overlay:case MapAttributeField::OverlayData:throw std::invalid_argument("Overlay stores outside tile-only parent fixture");case MapAttributeField::Buffer10:event(0xfffffffdu,unsigned(index*10+(n>>8)),n&255);break;}};
            recalculateMapCellAttributes(c,level,std::span<std::uint8_t,4>(b4.data()+index*4,4),std::span<std::uint8_t,10>(b10.data()+index*10,10),s);
        };
        const auto attributeEvent=[&](int id,MapAttributeField field,std::uint32_t n){
            const auto index=std::size_t(mapAttributeBufferIndex(cells[std::size_t(id)].attributes.input.position,width,height,int(capacity)));
            switch(field){case MapAttributeField::Tile:event(unsigned(id),1,n);break;case MapAttributeField::SubTile:event(unsigned(id),2,n);break;case MapAttributeField::Land:event(unsigned(id),3,n);break;case MapAttributeField::Slope:event(unsigned(id),4,n);break;case MapAttributeField::Level:event(unsigned(id),5,n);break;case MapAttributeField::ExtraHeight:event(unsigned(id),6,n);break;case MapAttributeField::Buffer4:event(0xfffffffeu,unsigned(index*4+(n>>8)),n&255);break;case MapAttributeField::Overlay:case MapAttributeField::OverlayData:throw std::invalid_argument("Overlay stores outside tile-only parent fixture");case MapAttributeField::Buffer10:event(0xfffffffdu,unsigned(index*10+(n>>8)),n&255);break;}
        };
        ResidentMapPreparationServices joined;
        joined.initializeLighting=services.initializeLighting;joined.visit=services.visit;joined.parentStore=services.store;
        joined.query=world.query;joined.fallbackStore=world.fallbackStore;
        joined.beforeRecalculation=[&](int id){events.insert(events.end(),{302,unsigned(id),303,unsigned(id)});};
        joined.beforeLAT=[&](int id){attributes(id,305);};joined.beforePassability=[&](int id){attributes(id,306);};
        joined.passabilityStore=[&](int id,int n){event(unsigned(id),7,unsigned(n));};joined.attributeStore=attributeEvent;
        resident.slots=slots;resident.tiles=types;
        const auto cursor=op=='P'?prepareMapCells(width,slots,cells,services):prepareResidentMapCells(resident,cells,fallback,b4,b10,joined);
        Words state;
        for(std::size_t i=0;i<cells.size();++i){const auto& c=cells[i];const auto& v=c.attributes.input;state.insert(state.end(),{position(v.position),unsigned(v.tile),unsigned(v.land),std::uint16_t(v.tube),v.subTile,std::uint8_t(v.level),v.slope,v.flags,c.attributes.extraHeight,c.attributes.overlayData,v.ice,unsigned(c.attributes.passability),c.field30});state.insert(state.end(),lights[i].begin(),lights[i].end());}
        std::cout<<digest(state)<<' '<<digest(events)<<' '<<digest(visits)<<' '<<digest(b4.data(),b4.size())<<' '<<digest(b10.data(),b10.size())<<' '<<digest(Words{unsigned(cursor.x),unsigned(cursor.y),unsigned(cursor.remaining),cursor.index,position(fallback.position)})<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
