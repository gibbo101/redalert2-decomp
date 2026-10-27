// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <functional>
#include <stdexcept>
#include <utility>
namespace ra2 {
// A borrowed pointer field or pure logical-handle accessor pair. Copying a view
// borrows the same field; it never synchronizes a second pointer value. Accessors
// must not make gameplay queries or invoke observers. Owners outlive all views.
class MissionExpirationPointerView {
    std::function<const void*()> read_;
    std::function<void(const void*)> write_;
public:
    MissionExpirationPointerView(const void*& field)
        :read_([&field]{return field;}),write_([&field](const void* p){field=p;}){}
    MissionExpirationPointerView(std::function<const void*()> read,std::function<void(const void*)> write)
        :read_(std::move(read)),write_(std::move(write)) {
        if(!read_||!write_)throw std::invalid_argument("Expiration pointer requires live field access");
    }
    operator const void*()const{return read_();}
    MissionExpirationPointerView& operator=(const void* value){write_(value);return *this;}
};
}
