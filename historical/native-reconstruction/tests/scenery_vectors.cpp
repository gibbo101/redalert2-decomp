// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Scenery.hpp"
#include "assets/Archive.hpp"
#include "assets/TerrainTypes.hpp"
#include <openssl/evp.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
std::string hash(const ra2::Bytes& b) {
    unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr);
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();
}
ra2::Bytes words(const std::vector<std::uint16_t>& v){ra2::Bytes b;for(auto x:v){b.push_back(std::uint8_t(x));b.push_back(std::uint8_t(x>>8));}return b;}
int main(int argc,char** argv) {
 try {
    if(argc==4&&std::string(argv[1])=="--export") {
        const auto root=std::filesystem::weakly_canonical(argv[2]),out=std::filesystem::weakly_canonical(argv[3]);
        ra2::AssetStore store(root);std::vector<std::pair<std::string,ra2::Data>> files;
        std::vector<std::string> names{"isotem.pal","temperat.pal","rules.ini","art.ini","mp03t4.map"};
        for(int n=1;n<=28;++n){std::ostringstream name;name<<"tree"<<std::setw(2)<<std::setfill('0')<<n<<".tem";names.push_back(name.str());}
        for(const auto& id:ra2::stockStaticPropTypes())names.push_back(id+".tem");
        for(const auto& name:names) {
            const auto path=std::filesystem::path(argv[3])/name;
            for(auto p=path;!p.empty();) {
                if(std::filesystem::is_symlink(p))throw std::runtime_error("Symlink research export refused");
                if(std::filesystem::weakly_canonical(p)==root)throw std::runtime_error("Use output outside source installation");
                const auto next=p.parent_path();if(p==next)break;p=next;
            }
            const auto data=store.require(name);
            if(std::filesystem::exists(path)) {
                const auto old=ra2::readFile(path);
                if(data.size!=old.size||!std::equal(data.ptr(),data.ptr()+data.size,old.ptr()))throw std::runtime_error("Different existing research data refused");
            }
            files.emplace_back(name,data);
        }
        std::filesystem::create_directories(out);
        for(const auto& [name,data]:files)if(!std::filesystem::exists(out/name)) {
            std::ofstream f(out/name,std::ios::binary);f.write(reinterpret_cast<const char*>(data.ptr()),std::streamsize(data.size));if(!f)throw std::runtime_error("Research export failed");
        }
        return 0;
    }
    if(argc!=2)return 2;const auto render=ra2::readRenderData(ra2::readFile(argv[1]));std::string op;
    while(std::cin>>op) {
        if(op=="S") {
            int current,stock;std::cin>>current>>stock;std::cout<<ra2::terrainStrengthDefault(current,stock);
        } else if(op=="R") {
            bool force;int requested,previous,count;std::cin>>force>>requested>>previous>>count;
            struct Item {std::string id;bool theater,owned;std::uint32_t image,loaded;};
            std::vector<Item> types(std::size_t(count),Item{});std::ostringstream events;
            for(auto& type:types)std::cin>>type.id>>type.theater>>type.owned>>type.image>>type.loaded;
            for(std::size_t i=0;i<types.size();++i) {
                auto& t=types[i];const auto plan=ra2::terrainImageReload(t.id,t.theater,t.owned,t.image,force,requested,previous);
                if(!plan)continue;
                if(plan->releasePrevious)events<<" F "<<i<<' '<<t.image;
                t.image=0;events<<" W "<<i<<" 0 0";t.owned=false;events<<" W "<<i<<" 1 0";
                events<<" L "<<i<<' '<<plan->filename;t.image=t.loaded;events<<" W "<<i<<" 0 "<<t.image;
            }
            for(const auto& t:types)std::cout<<t.image<<' '<<int(t.owned)<<' ';
            std::cout<<events.str();
        } else if(op=="P") {
            int frames,h,light;std::cin>>frames>>h>>light;
            for(const auto& i:ra2::staticTerrainDrawInputs(frames,h,std::int16_t(light)))std::cout<<i.frame<<' '<<i.flags<<' '<<i.zAdjust<<' '<<i.gradient<<' '<<i.brightness<<' ';
        } else if(op=="B"||op=="I"||op=="F"||op=="G"||op=="H") {
            std::string path;int w,h,frame,gradient,z,brightness,flags;ra2::PixelPoint at;ra2::PixelRect clip;
            std::cin>>path>>w>>h>>frame>>at.x>>at.y>>clip.x>>clip.y>>clip.width>>clip.height>>flags>>z>>gradient>>brightness;
            ra2::ShpImage auxiliaryImage;ra2::SpriteDepthInput auxiliary;
            if(op=="H"){std::string auxPath;std::cin>>auxPath>>auxiliary.frame>>auxiliary.offset.x>>auxiliary.offset.y;auxiliaryImage=ra2::readShp(ra2::readFile(auxPath));auxiliary.image=&auxiliaryImage;}
            std::vector<std::uint16_t> colors(std::size_t(w)*h),depth(colors.size()),alpha(colors.size());
            for(auto* plane:{&colors,&depth,&alpha})for(auto& v:*plane)std::cin>>v;
            std::vector<ra2::Palette16> palettes;
            if(op=="B"||op=="F"||op=="G"||op=="H") {
                palettes.resize(53);for(auto& row:palettes)for(auto& v:row)std::cin>>v;
            } else {
                std::string pal;int shades;std::array<int,3> tint;std::cin>>pal>>tint[0]>>tint[1]>>tint[2]>>shades;
                std::array<std::uint8_t,256> mask;mask.fill(1);
                palettes=ra2::lightPalette(render,ra2::readPalette(ra2::readFile(pal)),tint,shades,mask);
            }
            const auto image=ra2::readShp(ra2::readFile(path));
            if(op=="F")for(const auto& input:ra2::staticTerrainDrawInputs(int(image.frames.size()),z,std::int16_t(brightness)))
                ra2::blitTerrainFrame(image,input,at,clip,palettes,w,h,colors,depth,alpha);
            else if(op=="G"||op=="H")ra2::blitOrdinarySpriteFrame(image,{frame,flags,z,gradient,brightness},at,clip,palettes,w,h,colors,depth,alpha,auxiliary);
            else ra2::blitTerrainFrame(image,{frame,flags,z,gradient,brightness},at,clip,palettes,w,h,colors,depth,alpha);
            std::cout<<hash(words(colors))<<' '<<hash(words(depth));
        } else if(op=="L") {
            std::string path;int shades;std::array<int,3> tint;std::cin>>path>>tint[0]>>tint[1]>>tint[2]>>shades;
            std::array<std::uint8_t,256> mask;mask.fill(1);
            std::vector<std::uint16_t> values;for(const auto& row:ra2::lightPalette(render,ra2::readPalette(ra2::readFile(path)),tint,shades,mask))values.insert(values.end(),row.begin(),row.end());
            std::cout<<hash(words(values));
        } else return 3;
        if(!std::cin)return 4;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
