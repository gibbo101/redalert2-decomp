// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedData.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
namespace ra2 {
std::string assetSha256(const Data& data) {
    unsigned char digest[EVP_MAX_MD_SIZE];unsigned int length=0;
    if(!EVP_Digest(data.ptr(0,data.size),data.size,digest,&length,EVP_sha256(),nullptr))throw std::runtime_error("Cannot fingerprint supplied data");
    std::ostringstream hash;for(unsigned i=0;i<length;++i)hash<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(digest[i]);return hash.str();
}
std::string verifiedEngineDataSource(const Data& data) {
    auto digest=assetSha256(data);
    if(digest!=DiscEngineSha&&digest!=PatchedEngineSha)throw std::runtime_error("Unsupported GAME.EXE hash: use a separately verified base RA2 data profile");
    return digest;
}
void validatePreparedData(const Data& data,std::size_t size,std::string_view discHash,
    std::string_view patchedHash,std::string_view expectedSource) {
    if(data.size!=size)throw std::runtime_error("Invalid prepared data size");
    const auto digest=assetSha256(data);
    const auto source=digest==discHash?DiscEngineSha:digest==patchedHash?PatchedEngineSha:std::string_view{};
    if(source.empty())throw std::runtime_error("Invalid hash-pinned prepared data; run the corresponding preparation tool");
    if(!expectedSource.empty()&&source!=expectedSource)throw std::runtime_error("Prepared data source does not match GAME.EXE");
}
std::filesystem::path preparedDataPath(std::string_view source,const char* filename) {
    if(source==DiscEngineSha)return std::filesystem::path("private/derived")/filename;
    if(source==PatchedEngineSha)return std::filesystem::path("private/derived/ra2-1006")/filename;
    throw std::runtime_error("Unknown prepared data source");
}
}
