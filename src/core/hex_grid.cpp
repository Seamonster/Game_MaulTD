#include "maultd/core/hex_grid.h"

#include <cstddef>
#include <cmath>
#include <stdexcept>

namespace maultd::core
{
namespace
{

constexpr float kSqrtThree = 1.7320508075688772F;

} // namespace

tHexGrid::tHexGrid(int rows, int cols, float hexRadius)
    : Rows(rows),
      Cols(cols),
      HexRadius(hexRadius)
{
    if (rows <= 0)
    {
        throw std::invalid_argument("HexGrid rows must be positive");
    }

    if (cols <= 0)
    {
        throw std::invalid_argument("HexGrid columns must be positive");
    }

    if (hexRadius <= 0.0F)
    {
        throw std::invalid_argument("HexGrid hex radius must be positive");
    }

    Tiles.resize(static_cast<std::size_t>(Rows * Cols));
}

int tHexGrid::rows() const noexcept
{
    return Rows;
}

int tHexGrid::cols() const noexcept
{
    return Cols;
}

float tHexGrid::hexRadius() const noexcept
{
    return HexRadius;
}

bool tHexGrid::isInBounds(tOffsetCoord coord) const noexcept
{
    return coord.Row >= 0 && coord.Row < Rows && coord.Col >= 0 && coord.Col < Cols;
}

bool tHexGrid::isBuildable(tOffsetCoord coord) const
{
    return isInBounds(coord) && Tiles[index(coord)].Buildable && !Tiles[index(coord)].Occupied;
}

bool tHexGrid::isOccupied(tOffsetCoord coord) const
{
    return isInBounds(coord) && Tiles[index(coord)].Occupied;
}

bool tHexGrid::isPassable(tOffsetCoord coord) const
{
    return isInBounds(coord) && !Tiles[index(coord)].Occupied;
}

bool tHexGrid::setBuildable(tOffsetCoord coord, bool buildable)
{
    if (!isInBounds(coord))
    {
        return false;
    }

    Tiles[index(coord)].Buildable = buildable;
    return true;
}

bool tHexGrid::placeTower(tOffsetCoord coord)
{
    if (!isBuildable(coord))
    {
        return false;
    }

    Tiles[index(coord)].Occupied = true;
    return true;
}

bool tHexGrid::removeTower(tOffsetCoord coord)
{
    if (!isOccupied(coord))
    {
        return false;
    }

    Tiles[index(coord)].Occupied = false;
    return true;
}

tWorldPosition tHexGrid::hexCenter(tOffsetCoord coord) const
{
    if (!isInBounds(coord))
    {
        throw std::out_of_range("Hex coordinate is outside the grid");
    }

    const auto rowOffset = static_cast<float>(coord.Row % 2) * 0.5F;
    const auto x = HexRadius * kSqrtThree * (static_cast<float>(coord.Col) + rowOffset);
    const auto y = HexRadius * 1.5F * static_cast<float>(coord.Row);

    return tWorldPosition{x, y};
}

int tHexGrid::index(tOffsetCoord coord) const
{
    return coord.Row * Cols + coord.Col;
}

} // namespace maultd::core
