// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>
namespace ra2 {
struct IniInputBufferOwner {
    void* data0=nullptr;
    std::int32_t size4=0;
    std::uint8_t owned8=0;
};
struct IniInputPipeOwner {
    IniInputPipeOwner* source4=nullptr;
    IniInputPipeOwner* downstream8=nullptr;
    // Destruction installs the base pipe dispatch before its first child.
    bool baseDispatch=false;
};
struct IniInputLifetimeServices {
    std::function<void*(std::int32_t)> allocate;
    std::function<void(void*)> release;
    // Virtual slot4 on a downstream pipe. Actual dispatch may recurse into the
    // recovered attach kernel; the original parent proof supplies this child.
    std::function<void(IniInputPipeOwner&,IniInputPipeOwner*)> attach;
    // Ordered post-store observation; pointer values remain native identities.
    std::function<void(const void*,std::int32_t,std::int64_t,const void*)> store;
};
// Complete438380/438410. Raw ownership bytes test nonzero, including null data.
IniInputBufferOwner& constructIniInputBuffer(IniInputBufferOwner&,std::int32_t,const IniInputLifetimeServices&);
void destroyIniInputBuffer(IniInputBufferOwner&,const IniInputLifetimeServices&);
// Complete69B050/69B010. Preserve live reads after callbacks and alias ordering.
void attachIniInputSource(IniInputPipeOwner&,IniInputPipeOwner*,const IniInputLifetimeServices&);
void destroyIniInputPipe(IniInputPipeOwner&,const IniInputLifetimeServices&);
}
