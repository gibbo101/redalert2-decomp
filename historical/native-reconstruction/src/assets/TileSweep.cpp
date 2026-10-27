// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileSweep.hpp"
#include <bit>
#include <stdexcept>

namespace ra2 {
TileSweepCursor resetTileSweepCursor(int width) {
    if (width < 2 || width > 255)
        throw std::invalid_argument("Unsupported sweep map width");
    return {1, width, width - 1, std::uint32_t(width) * 512u + 1u};
}

int advanceTileSweepCursor(TileSweepCursor& cursor, int width, std::span<const int> slots) {
    if (width < 2 || width > 255 || slots.size() != 512u * 512u ||
        cursor.x < 0 || cursor.x >= 512 || cursor.y < 0 || cursor.y >= 512 ||
        cursor.remaining < 0 || cursor.remaining >= width ||
        cursor.index != std::uint32_t(cursor.y) * 512u + std::uint32_t(cursor.x))
        throw std::invalid_argument("Sweep iterator outside bounded geometry");

    // Return the old slot, even when it is null, after advancing the cursor.
    const auto current = slots[cursor.index];
    if (cursor.remaining) {
        ++cursor.x;
        --cursor.y;
        --cursor.remaining;
        cursor.index -= 511;
    } else {
        const int oldX = cursor.x, oldY = cursor.y;
        cursor.x = oldY;
        cursor.y = oldX;
        cursor.remaining = width;
        if ((oldY - width + oldX - 1) & 1) {
            ++cursor.y;
            --cursor.remaining;
        } else {
            ++cursor.x;
            cursor.remaining -= 2;
        }
        cursor.index = std::uint32_t(cursor.y) * 512u + std::uint32_t(cursor.x);
    }
    return current;
}

TileSweepResult sweepTileImages(int width, std::span<const int> slots,
    std::span<const TileSweepCell> cells, std::span<const int> primary,
    std::span<TileSweepType> types, int clearTile, TileSweepCursor initialCursor,
    std::uint8_t force, std::uint8_t keepRMG, TileVariantCache& cache,
    const TileVariantTables& tables, const std::function<std::uint32_t()>& next,
    const std::function<Data(const std::string&)>& read, const TileSweepObserver& observer) {
    if (width < 2 || width > 255 || types.size() > 65536 || primary.size() > 65536)
        throw std::invalid_argument("Sweep registry/geometry outside bounded profile");

    auto typeAt = [&](int index) -> TileSweepType& {
        if (index < 0 || std::size_t(index) >= types.size())
            throw std::invalid_argument("Missing sweep type");
        return types[std::size_t(index)];
    };
    auto primaryAt = [&](int index) {
        if (index < 0 || std::size_t(index) >= primary.size())
            throw std::invalid_argument("Missing primary sweep type");
        return primary[std::size_t(index)];
    };
    auto image = [&](int index) -> const Data* {
        auto& type = typeAt(index);
        if (!type.image && type.lazy) {
            if (!read) throw std::invalid_argument("Missing supplied sweep file reader");
            auto data = read(type.filename);
            auto prepared = prepareTileImage(data);
            type.image = std::move(data);
            type.prepared = std::move(prepared);
            type.owned = 1;
        }
        return type.image ? &*type.image : nullptr;
    };

    TileSweepResult result;
    result.cursor = initialCursor;
    if (!force) {
        result.cursor = resetTileSweepCursor(width);
        for (std::size_t visited = 0; ; ++visited) {
            if (visited > slots.size())
                throw std::invalid_argument("Sweep iterator has no terminal null");
            const int member = advanceTileSweepCursor(result.cursor, width, slots);
            if (observer.visit) observer.visit(member);
            if (member == -1) break;
            if (member < 0 || std::size_t(member) >= cells.size())
                throw std::invalid_argument("Missing sweep cell");

            const auto& cell = cells[std::size_t(member)];
            int tile = cell.tile, raw = 0;
            const bool valid = tile != 65535 && tile >= 0 && std::size_t(tile) < primary.size();
            if (tile < 0)
                throw std::invalid_argument("Negative sweep tile outside supported registry");
            if (!valid) tile = clearTile;
            int node = primaryAt(tile);
            auto& type = typeAt(node);
            if (type.variants <= 0)
                throw std::invalid_argument("Nonpositive sweep variant count");

            // Fallback always selects, even for a single variant. A valid
            // single-variant type bypasses both GetImage and the selector.
            bool choose = !valid;
            if (valid && type.variants > 1) {
                const auto* data = image(node);
                bool forced = false;
                if (data) {
                    const auto count = std::int64_t(data->i32(0)) * data->i32(4);
                    if (count <= 0 || count > 16384)
                        throw std::invalid_argument("Unsupported sweep image geometry");
                    const auto ref = data->u32(16 + std::size_t(cell.sub % count) * 4);
                    forced = ref && (data->u32(ref + 0x24) & 4u) != 0;
                }
                if (forced) raw = int((cell.flags >> 13) & 1u);
                else choose = true;
            }
            if (choose) {
                // The child queries GetImage only for nonzero sub-tile. Its
                // first-use cache/RNG initialization still precedes null return.
                const auto* data = cell.sub ? image(node) : nullptr;
                TileVariantImage dimensions;
                if (data) dimensions = {data->i32(0), data->i32(4)};
                raw = selectTileVariant(cache, tables, cell.position.x, cell.position.y,
                    cell.sub, type.variants, data ? &dimensions : nullptr, next);
            }
            if (raw > type.variants - 1) raw %= type.variants;
            if (raw < 0)
                throw std::invalid_argument("Negative sweep variant outside bounded chain");
            for (int i = 0; i < raw; ++i) node = typeAt(node).next;
            auto& selected = typeAt(node);
            ++selected.usage;
            if (observer.usage) observer.usage(node, selected.usage);
        }
    }

    for (int root : primary) {
        if (root == -1) continue;
        int node = root;
        for (std::size_t links = 0; node != -1; ++links) {
            if (links >= types.size()) throw std::invalid_argument("Cyclic sweep type chain");
            auto& type = typeAt(node);
            if (type.lazy && !type.filename.empty()) {
                if (force || type.usage || (keepRMG && type.requiredForRMG)) {
                    // Loads during the earlier usage pass are not in this total.
                    if (!type.image) {
                        const auto* data = image(node);
                        result.bytes += std::uint32_t(data->size);
                        ++result.loaded;
                    }
                } else if (type.image) {
                    // The original frees regardless of ownership; metadata and
                    // color ramps survive. Native storage uses local ownership.
                    if (observer.release) observer.release(node);
                    type.image.reset();
                    type.owned = 0;
                }
            }
            node = type.next;
        }
    }
    result.kibibytes = std::bit_cast<std::int32_t>(result.bytes) / 1024;
    return result;
}
}
