// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include <map>
#include <optional>
#include <span>
#include <array>

namespace ra2 {
std::uint32_t mixHash(std::string name);
struct MixEntry {
    std::uint32_t id, offset, length;
};
// Original signed midpoint search; equal IDs retain their original index order.
const MixEntry* findMixEntry(std::span<const MixEntry> entries, std::uint32_t id);
// Registration requests of the base bootstrap. Other startup/theater phases
// have separate ordering and are not established by this function.
std::vector<std::string> baseMixBootstrapNames(const std::array<bool,100>& expansions);
class Mix {
    Data data_;
    std::size_t body_ = 0;
    std::vector<MixEntry> entries_;
    std::uint32_t bodySize_=0;
    bool checksum_=false, encrypted_=false;
public:
    explicit Mix(Data data);
    std::optional<Data> find(const std::string& name) const;
    std::size_t count() const { return entries_.size(); }
    std::span<const MixEntry> index() const { return entries_; }
    std::size_t bodyOffset() const { return body_; }
    std::uint32_t bodySize() const { return bodySize_; }
    bool hasChecksum() const { return checksum_; }
    bool isEncrypted() const { return encrypted_; }
};
class AssetStore {
    std::vector<Mix> archives_;
    std::filesystem::path root_;
    std::map<std::string,std::filesystem::path> files_;
public:
    enum class Registration { LegacyPrototype, InitialTemperate };
    struct ArchiveSource { std::string name; std::filesystem::path file; std::size_t offset, bodyOffset; };
    struct Match { Data data; std::filesystem::path file; std::optional<std::size_t> archive; };
private:
    std::vector<ArchiveSource> sources_;
public:
    // Legacy remains the runtime default during coordinated patched migration.
    explicit AssetStore(const std::filesystem::path& root, Registration registration=Registration::LegacyPrototype);
    std::optional<Match> resolve(const std::string& name) const;
    std::span<const ArchiveSource> sources() const { return sources_; }
    const Mix& archive(std::size_t index) const { return archives_.at(index); }
    std::optional<Data> find(const std::string& name) const;
    Data require(const std::string& name) const;
};
}
