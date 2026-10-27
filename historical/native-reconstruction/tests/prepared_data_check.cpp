// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include "assets/RenderData.hpp"
#include "assets/RasterData.hpp"
#include <bit>
#include <iostream>

// Serialize decoded fields explicitly, without native struct padding. The digest
// proves input/decoder agreement, not execution or whole-game parity.
int main(int argc,char** argv) {
    try {
        if(argc!=5)throw std::runtime_error("Usage: prepared-data-check GAME.EXE DIRECTION RENDER RASTER");
        const auto exe=ra2::readFile(argv[1]);const auto source=ra2::verifiedEngineDataSource(exe);
        const auto drive=ra2::readDriveData(exe,ra2::readFile(argv[2]));
        const auto render=ra2::readRenderData(ra2::readFile(argv[3]),source);
        const auto raster=ra2::readRasterData(ra2::readFile(argv[4]),source);
        ra2::Bytes bytes;
        auto word=[&](std::uint32_t v){for(int n=0;n<4;++n)bytes.push_back(std::uint8_t(v>>(8*n)));};
        auto f32=[&](float v){word(std::bit_cast<std::uint32_t>(v));};
        auto f64=[&](double v){auto bits=std::bit_cast<std::uint64_t>(v);word(std::uint32_t(bits));word(std::uint32_t(bits>>32));};
        for(const auto& track:drive->tracks) {
            word(track.jumpIndex);word(track.entryIndex);word(track.cellIndex);word(std::uint32_t(track.points.size()));
            for(const auto& p:track.points){word(p.x);word(p.y);word(p.facing);}
        }
        for(const auto& t:drive->transitions){word(t.rawTrack);word(t.flags);word(t.facing);word(t.shortTrack);}
        f64(drive->stopScale);const auto& direction=drive->directionsToTargets;
        for(float v:direction.atan)f32(v);
        f32(direction.slopeStep);f32(direction.positiveHalfPi);f32(direction.negativeHalfPi);
        f64(direction.pi);f64(direction.halfPi);f64(direction.angleScale);
        for(const auto& normals:render.normals) {
            word(std::uint32_t(normals.size()));for(const auto& n:normals){f32(n.x);f32(n.y);f32(n.z);}
        }
        f64(render.paletteCoefficient);f32(render.shadeScale);f32(render.lightAngle);
        for(auto v:render.sqrtMantissas)word(v);
        for(const auto& row:raster.traversal)for(auto v:row)word(v);
        for(auto v:raster.sine)f32(v);
        f32(raster.sineScale);f32(raster.cosineScale);f64(raster.headingStep);f64(raster.degrees);
        const auto size=bytes.size();std::cout<<source<<' '<<size<<' '<<ra2::assetSha256(ra2::Data(std::move(bytes)))<<'\n';
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
