// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelSnapshot.hpp"
#include <algorithm>
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
void require(bool ok,const char* reason){if(!ok)throw std::invalid_argument(reason);}
unsigned word(std::span<const std::uint8_t> b,std::size_t p){
    require(p<b.size()&&b.size()-p>=2,"Truncated voxel snapshot word");return b[p]|unsigned(b[p+1])<<8;
}
void storeWord(Bytes& b,std::size_t p,unsigned v){b[p]=std::uint8_t(v);b[p+1]=std::uint8_t(v>>8);}
std::uint32_t offset(const Bytes& b,std::size_t p){return word(b,p)|std::uint32_t(word(b,p+2))<<16;}
std::span<const std::uint8_t> rowAt(const Bytes& pool,std::size_t p){
    const auto n=word(pool,p);require(n>=2&&n<=pool.size()-p,"Invalid voxel snapshot row length");
    return std::span<const std::uint8_t>(pool).subspan(p,n);
}
void rectangle(PixelRect r){for(int v:{r.x,r.y,r.width,r.height})require(std::abs(std::int64_t(v))<=1048576,"Cached voxel rectangle outside bounded profile");}
void copySpan(std::span<const std::uint8_t> row,int left,int count,std::span<std::uint8_t> destination,const IndexRemap& remap){
    std::size_t p=2;int x=0;
    // Match the selected span's skip through whole tokens; a clipped-left zero
    // run can overshoot left and advances the destination before any literal.
    auto token=[&](){require(p<row.size(),"Truncated cached voxel span");const auto v=row[p++];
        unsigned n=1;if(!v){require(p<row.size(),"Truncated cached voxel zero run");n=row[p++];require(n!=0,"Zero cached voxel run");}
        return std::pair<unsigned,unsigned>{v,n};};
    while(left>0){const auto [v,n]=token();(void)v;left-=int(n);}
    if(left<0){x=-left;count-=x;}
    while(count>0){const auto [v,n]=token();if(v){destination[std::size_t(x)]=remap[v];++x;--count;}
        else{x+=int(n);count-=int(n);}}
}
}
Bytes encodeVoxelRow(std::span<const std::uint8_t> source,int width){
    require(width>=0&&width<=4096&&source.size()>=std::size_t(width)+2,"Voxel row requires two readable padding bytes");
    Bytes out(2);std::size_t p=0;int remaining=width;
    while(remaining>0){const auto value=source[p];if(value){out.push_back(value);++p;--remaining;continue;}
        // Preserve the original inclusive comparison and lookahead-before-cap.
        // A trailing run can consume width+1, unlike a row-limited RLE encoder.
        int n=0;while(n<=remaining){const auto next=source[p+std::size_t(n)+1];++n;if(next)break;}
        n=std::min(n,255);out.push_back(0);out.push_back(std::uint8_t(n));p+=std::size_t(n);remaining-=n;
    }
    storeWord(out,0,unsigned(out.size()));return out;
}
Bytes decodeVoxelRow(std::span<const std::uint8_t> encoded){
    const auto length=word(encoded,0);require(length>=2&&length<=encoded.size(),"Invalid encoded voxel row");Bytes out;
    for(std::size_t p=2;p<length;){const auto v=encoded[p++];if(v)out.push_back(v);
        else{require(p<length,"Truncated encoded voxel zero run");const auto n=encoded[p++];out.insert(out.end(),n,0);}
        require(out.size()<=8192,"Decoded voxel row outside bounded profile");}
    return out;
}
std::optional<std::size_t> appendVoxelSnapshot(Bytes& pool,std::size_t& cursor,
    std::span<const std::uint8_t> source,int width,int height,const std::array<int,6>& crop){
    const auto [ox,oy,x,y,w,h]=crop;
    require(width>0&&height>0&&width<=256&&height<=256&&source.size()>=std::size_t(width)*height+2,"Invalid padded voxel surface");
    require(x>=0&&y>=0&&w>=0&&h>=0&&x<=width&&y<=height&&w<=width-x&&h<=height-y,"Invalid voxel snapshot crop");
    require(cursor<=pool.size()&&pool.size()<=0x1000000,"Invalid native voxel snapshot pool");
    if(pool.size()-cursor<12)return std::nullopt;
    const auto start=cursor;cursor+=12;
    storeWord(pool,start,unsigned(ox));storeWord(pool,start+2,unsigned(oy));storeWord(pool,start+4,unsigned(w));storeWord(pool,start+6,unsigned(h));
    storeWord(pool,start+8,unsigned(cursor));storeWord(pool,start+10,unsigned(cursor>>16));
    for(int row=0;row<h;++row){const auto at=std::size_t(y+row)*width+x;const auto bytes=encodeVoxelRow(source.subspan(at),w);
        if(bytes.size()>pool.size()-cursor)return std::nullopt;
        std::copy(bytes.begin(),bytes.end(),pool.begin()+std::ptrdiff_t(cursor));cursor+=bytes.size();}
    return start;
}
void drawOrdinaryCachedVoxelPart(const Bytes& pool,std::size_t snapshot,PixelPoint at,PixelRect clip,
    std::uint32_t flags,int brightness,const CachedVoxelPartServices& s,const IndexRemap& remap,Bytes& staging,PixelRect& dirty){
    require(snapshot<=pool.size()&&pool.size()-snapshot>=12,"Invalid voxel snapshot header");
    require((flags&~0x10u)==0u&&staging.size()==65536,"Alternate cached voxel part requires recovery");
    rectangle(clip);rectangle({at.x,at.y,0,0});rectangle(dirty);
    const auto w=int(word(pool,snapshot+4)),h=int(word(pool,snapshot+6));require(w<=256&&h<=256,"Cached voxel dimensions outside bounded profile");
    const auto x=at.x+std::bit_cast<std::int16_t>(std::uint16_t(word(pool,snapshot)));
    const auto y=at.y+std::bit_cast<std::int16_t>(std::uint16_t(word(pool,snapshot+2)));
    s.kind();s.selectBlitter(flags&~0x10u);s.kind();dirty=stagingUnion(dirty,{x,y,w,h});
    const auto c4=s.value2C4();const auto c0=s.value2C0();(void)c4;(void)c0;(void)brightness;
    if(clip.width<=0||clip.height<=0||w==0||h==0)return;
    const int dx=x+clip.x,dy=y+clip.y;
    const int left=std::max({0,clip.x,dx}),top=std::max({0,clip.y,dy});
    const int right=std::min({256,clip.x+clip.width,dx+w}),bottom=std::min({256,clip.y+clip.height,dy+h});
    if(left>=right||top>=bottom)return;
    std::size_t p=offset(pool,snapshot+8);
    for(int row=0;row<bottom-dy;++row){const auto bytes=rowAt(pool,p);if(row>=top-dy)
        copySpan(bytes,left-dx,right-left,std::span<std::uint8_t>(staging).subspan(std::size_t(dy+row)*256+left,std::size_t(right-left)),remap);
        p+=bytes.size();}
}
}
