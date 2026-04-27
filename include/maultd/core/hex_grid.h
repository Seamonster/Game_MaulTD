#pragma once

#include <vector>

namespace maultd::core
{

struct tOffsetCoord
{
    int Row{0};
    int Col{0};

    [[nodiscard]] constexpr bool operator==(const tOffsetCoord&) const = default;
};

struct tWorldPosition
{
    float X{0.0F};
    float Y{0.0F};
};

class tHexGrid
{
public:
    tHexGrid(int rows, int cols, float hexRadius);

    [[nodiscard]] int rows() const noexcept;
    [[nodiscard]] int cols() const noexcept;
    [[nodiscard]] float hexRadius() const noexcept;

    [[nodiscard]] bool isInBounds(tOffsetCoord coord) const noexcept;
    [[nodiscard]] bool isBuildable(tOffsetCoord coord) const;
    [[nodiscard]] bool isOccupied(tOffsetCoord coord) const;
    [[nodiscard]] bool isPassable(tOffsetCoord coord) const;

    bool setBuildable(tOffsetCoord coord, bool buildable);
    bool placeTower(tOffsetCoord coord);
    bool removeTower(tOffsetCoord coord);

    [[nodiscard]] tWorldPosition hexCenter(tOffsetCoord coord) const;

private:
    struct tTile
    {
        bool Buildable{true};
        bool Occupied{false};
    };

    [[nodiscard]] int index(tOffsetCoord coord) const;

    int Rows{0};
    int Cols{0};
    float HexRadius{0.0F};
    std::vector<tTile> Tiles;
};

} // namespace maultd::core
