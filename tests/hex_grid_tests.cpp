#include "maultd/core/hex_grid.h"

#include <gtest/gtest.h>

#include <cmath>

namespace maultd::core {
namespace {

TEST(HexGrid, ValidatesBounds)
{
    const HexGrid grid{3, 4, 10.0F};

    EXPECT_TRUE(grid.IsInBounds({0, 0}));
    EXPECT_TRUE(grid.IsInBounds({2, 3}));
    EXPECT_FALSE(grid.IsInBounds({-1, 0}));
    EXPECT_FALSE(grid.IsInBounds({0, -1}));
    EXPECT_FALSE(grid.IsInBounds({3, 0}));
    EXPECT_FALSE(grid.IsInBounds({0, 4}));
}

TEST(HexGrid, TracksBuildableTilesSeparatelyFromPassability)
{
    HexGrid grid{3, 4, 10.0F};

    EXPECT_TRUE(grid.SetBuildable({1, 1}, false));

    EXPECT_FALSE(grid.IsBuildable({1, 1}));
    EXPECT_TRUE(grid.IsPassable({1, 1}));
    EXPECT_FALSE(grid.PlaceTower({1, 1}));
}

TEST(HexGrid, TowerPlacementOccupiesAndBlocksTile)
{
    HexGrid grid{3, 4, 10.0F};

    EXPECT_TRUE(grid.PlaceTower({0, 0}));
    EXPECT_TRUE(grid.IsOccupied({0, 0}));
    EXPECT_FALSE(grid.IsBuildable({0, 0}));
    EXPECT_FALSE(grid.IsPassable({0, 0}));
    EXPECT_FALSE(grid.PlaceTower({0, 0}));

    EXPECT_TRUE(grid.RemoveTower({0, 0}));
    EXPECT_FALSE(grid.IsOccupied({0, 0}));
    EXPECT_TRUE(grid.IsBuildable({0, 0}));
    EXPECT_TRUE(grid.IsPassable({0, 0}));
}

TEST(HexGrid, DerivesHexCentersFromRowColumnAndRowParity)
{
    const HexGrid grid{3, 4, 10.0F};
    constexpr float tolerance = 0.001F;

    const auto row_zero_col_zero = grid.HexCenter({0, 0});
    const auto row_zero_col_one = grid.HexCenter({0, 1});
    const auto row_one_col_zero = grid.HexCenter({1, 0});

    EXPECT_NEAR(row_zero_col_zero.x, 0.0F, tolerance);
    EXPECT_NEAR(row_zero_col_zero.y, 0.0F, tolerance);

    EXPECT_NEAR(row_zero_col_one.x, 10.0F * std::sqrt(3.0F), tolerance);
    EXPECT_NEAR(row_zero_col_one.y, 0.0F, tolerance);

    EXPECT_NEAR(row_one_col_zero.x, 10.0F * std::sqrt(3.0F) * 0.5F, tolerance);
    EXPECT_NEAR(row_one_col_zero.y, 15.0F, tolerance);
}

} // namespace
} // namespace maultd::core
