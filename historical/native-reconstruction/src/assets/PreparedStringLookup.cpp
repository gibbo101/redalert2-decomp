// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedStringLookup.hpp"
#include <algorithm>
namespace ra2 {
PreparedStringLookup::PreparedStringLookup(const Data& data):table_(readStringTable(data)){
    for(const auto& [key,rows]:table_){
        if(key.size()>31||std::any_of(key.begin(),key.end(),[](unsigned char c){return c>=128;}))
            throw std::invalid_argument("Prepared CSF lookup requires bounded ASCII labels");
        labels_.push_back({key,std::uint32_t(values_.size())});
        handles_.push_back(std::uint32_t(values_.size()+1));
        values_.push_back(rows.size()==1?&rows.front().utf8:nullptr);
    }
}
const std::string& PreparedStringLookup::text(std::string_view key)const{
    const auto handle=lookupString(key,nullptr,{!labels_.empty(),labels_,std::uint32_t(labels_.size()),handles_,{},0});
    if(!handle||handle>values_.size()||!values_[handle-1])
        throw std::invalid_argument("Unavailable/ambiguous prepared CSF lookup");
    return *values_[handle-1];
}
}
