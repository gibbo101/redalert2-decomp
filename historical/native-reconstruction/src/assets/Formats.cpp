// SPDX-License-Identifier: GPL-3.0-or-later
// Format layouts informed by OpenRA readers; attribution in THIRD_PARTY.md.
#include "assets/Formats.hpp"
#include <lzo/lzo1x.h>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <limits>

namespace ra2 {
std::uint8_t iniBooleanValue(std::string_view value,std::uint8_t fallback) {
    if(value.empty())return fallback;
    auto first=static_cast<unsigned char>(value.front());
    if(first>='a'&&first<='z')first-=32;
    switch(first) {
        case '0':case 'F':case 'N':return 0;
        case '1':case 'T':case 'Y':return 1;
        default:return fallback;
    }
}
static std::string trim(std::string s) {
    auto a=s.find_first_not_of(" \t\r\n");if(a==std::string::npos) return {};
    return s.substr(a,s.find_last_not_of(" \t\r\n")-a+1);
}
Ini::Ini(const std::string& text) {
    std::istringstream input(text);std::string line,section;
    while(std::getline(input,line)) {
        line=trim(line.substr(0,line.find(';')));if(line.empty()) continue;
        if(line.front()=='[') {auto e=line.find(']');if(e==std::string::npos) throw std::runtime_error("Malformed INI section");section=lower(trim(line.substr(1,e-1)));sections_.try_emplace(section);}
        else if(auto p=line.find('=');p!=std::string::npos) sections_[section][lower(trim(line.substr(0,p)))]=trim(line.substr(p+1));
    }
}
bool Ini::hasSection(const std::string& name) const {return sections_.contains(lower(name));}
const Section& Ini::section(const std::string& name) const {
    static const Section empty;auto it=sections_.find(lower(name));return it==sections_.end()?empty:it->second;
}
std::string Ini::get(const std::string& s,const std::string& k,const std::string& fallback) const {
    const auto& sec=section(s);auto it=sec.find(lower(k));return it==sec.end()?fallback:it->second;
}
int Ini::integer(const std::string& s,const std::string& k,int fallback) const {
    const auto v=get(s,k);return v.empty()?fallback:std::stoi(v);
}
double Ini::number(const std::string& s,const std::string& k,double fallback) const {
    const auto v=get(s,k);const auto n=v.empty()?fallback:std::stod(v);
    if(!std::isfinite(n)) throw std::runtime_error("Non-finite INI value");return n;
}
std::uint8_t Ini::boolean(const std::string& s,const std::string& k,std::uint8_t fallback) const {
    return iniBooleanValue(get(s,k),fallback);
}
std::vector<int> integers(const std::string& text) {
    std::vector<int> out;std::istringstream in(text);std::string s;while(std::getline(in,s,',')) out.push_back(std::stoi(s));return out;
}
Bytes decodeBase64(const std::string& text) {
    const std::string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    Bytes out;std::uint32_t bits=0;int count=0;bool padded=false;
    for(unsigned char ch:text) {
        if(ch==' '||ch=='\r'||ch=='\n'||ch=='\t') continue;
        if(ch=='=') {padded=true;continue;}
        const auto p=alphabet.find(char(ch));if(p==std::string::npos || padded) throw std::runtime_error("Invalid map base64");
        bits=(bits<<6)|std::uint32_t(p);count+=6;
        if(count>=8) {count-=8;out.push_back(std::uint8_t(bits>>count));}
    }
    return out;
}
Bytes unpackMap(const Bytes& packed) {
    Data data(packed);Bytes out;std::size_t pos=0;
    while(pos<data.size) {
        auto len=data.u16(pos), wanted=data.u16(pos+2);pos+=4;
        if(!len&&!wanted) {if(pos!=data.size) throw std::runtime_error("Trailing map pack bytes");break;}
        if(!len || !wanted || wanted>8192 || out.size()+wanted>64*1024*1024) throw std::runtime_error("Invalid map LZO block size");
        const auto old=out.size();out.resize(old+wanted);lzo_uint actual=wanted;
        const auto result=lzo1x_decompress_safe(data.ptr(pos,len),len,out.data()+old,&actual,nullptr);
        if(result!=LZO_E_OK || actual!=wanted) throw std::runtime_error("Invalid map LZO block");pos+=len;
    }
    return out;
}
Palette readPalette(const Data& data) {
    if(data.size!=768) throw std::runtime_error("Expected 256-color 6-bit palette");Palette out{};
    for(std::size_t i=0;i<256;++i) {
        for(std::size_t j=0;j<3;++j) if(data.u8(i*3+j)>63) throw std::runtime_error("Invalid 6-bit palette value");
        out[i]={std::uint8_t(data.u8(3*i)<<2),std::uint8_t(data.u8(3*i+1)<<2),std::uint8_t(data.u8(3*i+2)<<2),std::uint8_t(i?255:0)};
    }
    return out;
}
std::vector<TileImage> readTmp(const Data& d) {
    const auto cols=d.u32(0),rows=d.u32(4),w=d.u32(8),h=d.u32(12);
    if(!cols||!rows||cols>128||rows>128||w!=60||h!=30) throw std::runtime_error("Unsupported TMP geometry (expected RA2 60x30)");
    const auto count=cols*rows;d.check(16,count*4);std::vector<TileImage> out(count);
    for(std::size_t i=0;i<count;++i) {
        auto p=d.u32(16+4*i);if(!p) continue;d.check(p,52);
        const auto ex=d.i32(p+20)-d.i32(p),ey=d.i32(p+24)-d.i32(p+4);
        const auto ew=d.i32(p+28),eh=d.i32(p+32);const bool extra=(d.u32(p+36)&1)!=0;
        if(extra && (ew<0||eh<0||ew>2048||eh>2048||std::abs(std::int64_t(ex))>2048||std::abs(std::int64_t(ey))>2048)) throw std::runtime_error("Invalid TMP extra bounds");
        auto& t=out[i];t.flags=d.u32(p+36);t.x=extra?std::min(0,ex):0;t.y=extra?std::min(0,ey):0;
        t.width=(extra?std::max(60,ex+ew):60)-t.x;t.height=(extra?std::max(30,ey+eh):30)-t.y;
        t.terrain=d.u8(p+41);t.ramp=d.u8(p+42);t.pixels.resize(t.width*t.height);t.depth.resize(t.pixels.size());t.coverage.resize(t.pixels.size());
        std::size_t cursor=p+52;
        for(auto* dst:{&t.pixels,&t.depth}) {
            int width=4;
            for(int y=0;y<30;++y) {
                const int x=(60-width)/2;const auto* row=d.ptr(cursor,std::size_t(width));
                std::copy(row,row+width,dst->begin()+(y-t.y)*t.width+x-t.x);cursor+=width;
                if(dst==&t.pixels)std::fill_n(t.coverage.begin()+(y-t.y)*t.width+x-t.x,width,1);
                width+=y<14?4:-4;
            }
        }
        t.basePixels=t.pixels;t.baseDepth=t.depth;
        t.extraPixels.resize(t.pixels.size());t.extraDepth.resize(t.pixels.size());
        if(extra) {
            // Stored offsets are relative to this sub-tile header, not the file.
            const auto colorOffset=d.u32(p+8),depthOffset=d.u32(p+16);
            for(int kind=0;kind<2;++kind) {
                const auto base=std::size_t(p)+(kind?depthOffset:colorOffset);
                d.check(base,std::size_t(ew)*eh);
                auto& dst=kind?t.depth:t.pixels;
                for(int y=0;y<eh;++y) for(int x=0;x<ew;++x) {
                    const auto value=d.u8(base+std::size_t(y)*ew+x);
                    const auto at=(y+ey-t.y)*t.width+x+ex-t.x;
                    if(!kind&&value){t.extraPixels[at]=value;t.coverage[at]|=2;}
                    if(kind)t.extraDepth[at]=value;
                    if((kind && value<32)||(!kind && value)) dst[(y+ey-t.y)*t.width+x+ex-t.x]=value;
                }
            }
        }
    }
    return out;
}
MapData readMap(const Ini& ini) {
    if(lower(ini.get("Map","Theater"))!="temperate") throw std::runtime_error("Only TEMPERATE maps are currently verified");
    MapData map;auto size=integers(ini.get("Map","Size"));map.local=integers(ini.get("Map","LocalSize"));
    if(size.size()!=4||map.local.size()!=4||size[2]<1||size[3]<1||size[2]>512||size[3]>512) throw std::runtime_error("Invalid map dimensions");
    map.width=size[2];map.height=size[3];
    std::map<int,std::string> ordered;for(const auto& [k,v]:ini.section("IsoMapPack5")) ordered.emplace(std::stoi(k),v);
    std::string encoded;for(const auto& [k,v]:ordered) encoded+=v;
    Data raw(unpackMap(decodeBase64(encoded)));const auto count=std::size_t(2*map.width-1)*map.height;
    if(raw.size!=count*11 && raw.size!=count*11+4) throw std::runtime_error("Unexpected IsoMapPack5 cell count");
    std::map<std::pair<int,int>,bool> seen;
    for(std::size_t i=0;i<count;++i) {
        const auto p=i*11;MapCell c{raw.u16(p),raw.u16(p+2),raw.u32(p+4),raw.u8(p+8),raw.u8(p+9)};
        if(c.x>=1024||c.y>=1024||c.z>31||!seen.emplace(std::pair{c.x,c.y},true).second) throw std::runtime_error("Invalid or duplicate map cell");
        map.cells.push_back(c);
    }
    for(const auto& [k,v]:ini.section("Waypoints")) {int n=std::stoi(v);map.waypoints[std::stoi(k)]={n%1000,n/1000};}
    map.tint={ini.number("Lighting","Red",1),ini.number("Lighting","Green",1),ini.number("Lighting","Blue",1)};
    map.ambient=ini.number("Lighting","Ambient",1);map.ground=ini.number("Lighting","Ground",0);map.level=ini.number("Lighting","Level",0);
    return map;
}
static Matrix matrix(const Data& d,std::size_t p) {
    Matrix m{};for(std::size_t i=0;i<12;++i) {m[i]=d.f32(p+4*i);if(!std::isfinite(m[i])||std::abs(m[i])>100000) throw std::runtime_error("Invalid HVA/VXL matrix");}return m;
}
VoxelModel readVxl(const Data& d) {
    if(d.name(0,16)!="Voxel Animation") throw std::runtime_error("Invalid VXL magic");
    const auto n=d.u32(20),tails=d.u32(24),bodySize=d.u32(28);
    if(n==0||n>128||n!=tails) throw std::runtime_error("Invalid VXL section count");
    const std::size_t body=802+28*n,footer=body+bodySize;d.check(footer,92*n);VoxelModel model;
    for(std::size_t i=0;i<n;++i) {
        const auto p=footer+92*i;VoxelSection s;s.name=d.name(802+28*i,16);s.scale=d.f32(p+12);s.base=matrix(d,p+16);
        s.min={d.f32(p+64),d.f32(p+68),d.f32(p+72)};s.max={d.f32(p+76),d.f32(p+80),d.f32(p+84)};
        s.size={d.u8(p+88),d.u8(p+89),d.u8(p+90)};s.normalType=d.u8(p+91);
        if(!std::isfinite(s.scale)||s.scale<=0||s.scale>100||s.size[0]==0||s.size[1]==0||s.size[2]==0||(s.normalType!=2&&s.normalType!=4)) throw std::runtime_error("Invalid VXL bounds/type");
        for(auto f:{s.min.x,s.min.y,s.min.z,s.max.x,s.max.y,s.max.z}) if(!std::isfinite(f)||std::abs(f)>10000) throw std::runtime_error("Invalid VXL coordinate");
        if(s.max.x<=s.min.x||s.max.y<=s.min.y||s.max.z<=s.min.z) throw std::runtime_error("Inverted VXL bounds");
        const auto spanStart=d.u32(p),spanEnd=d.u32(p+4),spanData=d.u32(p+8);
        Data b=d.slice(body,bodySize);const auto columns=std::size_t(s.size[0])*s.size[1];b.check(spanStart,4*columns);b.check(spanEnd,4*columns);
        s.spans.resize(columns);
        for(std::size_t col=0;col<columns;++col) {
            const int start=b.i32(spanStart+4*col),end=b.i32(spanEnd+4*col);if(start==-1&&end==-1) continue;
            if(start<0||end<start) throw std::runtime_error("Invalid VXL span offsets");
            Data span=b.slice(std::size_t(spanData)+start,std::size_t(end-start)+1);std::size_t pos=0;int z=0;
            while(z<s.size[2]) {
                const int skip=span.u8(pos++),count=span.u8(pos++);z+=skip;
                if(z+count>s.size[2] || (!skip&&!count)) throw std::runtime_error("Invalid VXL run");
                for(int j=0;j<count;++j) {s.voxels.push_back({std::uint8_t(col%s.size[0]),std::uint8_t(col/s.size[0]),std::uint8_t(z++),span.u8(pos),span.u8(pos+1)});pos+=2;}
                if(span.u8(pos++)!=count) throw std::runtime_error("Invalid VXL duplicate count");
            }
            if(pos!=span.size) throw std::runtime_error("Trailing VXL span bytes");
            s.spans[col].assign(span.ptr(),span.ptr()+span.size);
        }
        model.sections.push_back(std::move(s));
    }
    return model;
}
Animation readHva(const Data& d) {
    Animation a;a.frames=int(d.u32(16));const auto count=d.u32(20);
    if(a.frames<=0||a.frames>4096||count==0||count>128) throw std::runtime_error("Invalid HVA dimensions");
    d.check(24,16*count+std::size_t(a.frames)*count*48);
    for(std::size_t i=0;i<count;++i) a.names.push_back(d.name(24+16*i,16));
    for(std::size_t i=0;i<std::size_t(a.frames)*count;++i) a.transforms.push_back(matrix(d,24+16*count+48*i));return a;
}
const Matrix& Animation::at(int frame,std::size_t section) const {
    if(frame<0||frame>=frames||section>=names.size()) throw std::runtime_error("HVA frame/section out of bounds");
    return transforms.at(std::size_t(frame)*names.size()+section);
}
}
