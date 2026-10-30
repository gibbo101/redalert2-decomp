// WolRegistryOptions: the Westwood Online options word kept in the registry (Read 0x004FF200,
// Write 0x004FF2E0). Split from shared/wol_sink.hpp so that Init.CPP's CD check can use it without
// the WOL session headers (their rc_ptr<WDTTerritory> instances emit COMDATs Init.CPP does not have).
#ifndef RA2_SHARED_WOL_REGISTRY_OPTIONS_HPP
#define RA2_SHARED_WOL_REGISTRY_OPTIONS_HPP

struct WolRegistryOptions {
    WolRegistryOptions() : Options(0), HasOptions(false) {}
    bool Read_004ff200();
    bool unknown_004ff2b0() const;
    bool unknown_004ff2c0() const;
    bool unknown_004ff2d0() const;
    bool Write_004ff2e0(unsigned int options);
    unsigned int Options;
    bool HasOptions;
};

#endif
