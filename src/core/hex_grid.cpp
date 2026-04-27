#include "maultd/core/hex_grid.h"

#include <cstddef>
#include <cmath>
#include <stdexcept>

namespace maultd::core {
namespace {

constexpr float kSqrtThree = 1.7320508075688772F;

} // namespace

HexGrid::HexGrid(int rows, int cols, float hex_radius)
    : rows_(rows),
      cols_(cols),
      hex_radius_(hex_radius)
{
    if (rows <= 0) {
        throw std::invalid_argument("HexGrid rows must be positive");
    }

    if (cols <= 0) {
        throw std::invalid_argument("HexGrid columns must be positive");
    }

    if (hex_radius <= 0.0F) {
        throw std::invalid_argument("HexGrid hex radius must be positive");
    }

    tiles_.resize(static_cast<std::size_t>(rows_ * cols_));
}

int HexGrid::rows() const noexcept
{
    return rows_;
}

int HexGrid::cols() const noexcept
{
    return cols_;
}

float HexGrid::hex_radius() const noexcept
{
    return hex_radius_;
}

bool HexGrid::IsInBounds(OffsetCoord coord) const noexcept
{
    return coord.row >= 0 && coord.row < rows_ && coord.col >= 0 && coord.col < cols_;
}

bool HexGrid::IsBuildable(OffsetCoord coord) const
{
    return IsInBounds(coord) && tiles_[Index(coord)].buildable && !tiles_[Index(coord)].occupied;
}

bool HexGrid::IsOccupied(OffsetCoord coord) const
{
    return IsInBounds(coord) && tiles_[Index(coord)].occupied;
}

bool HexGrid::IsPassable(OffsetCoord coord) const
{
    return IsInBounds(coord) && !tiles_[Index(coord)].occupied;
}

bool HexGrid::SetBuildable(OffsetCoord coord, bool buildable)
{
    if (!IsInBounds(coord)) {
        return false;
    }

    tiles_[Index(coord)].buildable = buildable;
    return true;
}

bool HexGrid::PlaceTower(OffsetCoord coord)
{
    if (!IsBuildable(coord)) {
        return false;
    }

    tiles_[Index(coord)].occupied = true;
    return true;
}

bool HexGrid::RemoveTower(OffsetCoord coord)
{
    if (!IsOccupied(coord)) {
        return false;
    }

    tiles_[Index(coord)].occupied = false;
    return true;
}

WorldPosition HexGrid::HexCenter(OffsetCoord coord) const
{
    if (!IsInBounds(coord)) {
        throw std::out_of_range("Hex coordinate is outside the grid");
    }

    const auto row_offset = static_cast<float>(coord.row % 2) * 0.5F;
    const auto x = hex_radius_ * kSqrtThree * (static_cast<float>(coord.col) + row_offset);
    const auto y = hex_radius_ * 1.5F * static_cast<float>(coord.row);

    return WorldPosition{x, y};
}

int HexGrid::Index(OffsetCoord coord) const
{
    return coord.row * cols_ + coord.col;
}

} // namespace maultd::core
