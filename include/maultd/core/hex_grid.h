#pragma once

#include <vector>

namespace maultd::core {

struct OffsetCoord {
    int row{0};
    int col{0};

    [[nodiscard]] constexpr bool operator==(const OffsetCoord&) const = default;
};

struct WorldPosition {
    float x{0.0F};
    float y{0.0F};
};

class HexGrid {
public:
    HexGrid(int rows, int cols, float hex_radius);

    [[nodiscard]] int rows() const noexcept;
    [[nodiscard]] int cols() const noexcept;
    [[nodiscard]] float hex_radius() const noexcept;

    [[nodiscard]] bool IsInBounds(OffsetCoord coord) const noexcept;
    [[nodiscard]] bool IsBuildable(OffsetCoord coord) const;
    [[nodiscard]] bool IsOccupied(OffsetCoord coord) const;
    [[nodiscard]] bool IsPassable(OffsetCoord coord) const;

    bool SetBuildable(OffsetCoord coord, bool buildable);
    bool PlaceTower(OffsetCoord coord);
    bool RemoveTower(OffsetCoord coord);

    [[nodiscard]] WorldPosition HexCenter(OffsetCoord coord) const;

private:
    struct Tile {
        bool buildable{true};
        bool occupied{false};
    };

    [[nodiscard]] int Index(OffsetCoord coord) const;

    int rows_{0};
    int cols_{0};
    float hex_radius_{0.0F};
    std::vector<Tile> tiles_;
};

} // namespace maultd::core
