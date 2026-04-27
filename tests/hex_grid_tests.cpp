#include "maultd/core/hex_grid.h"

#include <gtest/gtest.h>

#include <cmath>

namespace maultd::core
{
namespace
{

TEST(HexGrid, ValidatesBounds)
{
    const tHexGrid grid{3, 4, 10.0F};

    EXPECT_TRUE(grid.isInBounds({0, 0}));
    EXPECT_TRUE(grid.isInBounds({2, 3}));
    EXPECT_FALSE(grid.isInBounds({-1, 0}));
    EXPECT_FALSE(grid.isInBounds({0, -1}));
    EXPECT_FALSE(grid.isInBounds({3, 0}));
    EXPECT_FALSE(grid.isInBounds({0, 4}));
}

TEST(HexGrid, TracksBuildableTilesSeparatelyFromPassability)
{
    tHexGrid grid{3, 4, 10.0F};

    EXPECT_TRUE(grid.setBuildable({1, 1}, false));

    EXPECT_FALSE(grid.isBuildable({1, 1}));
    EXPECT_TRUE(grid.isPassable({1, 1}));
    EXPECT_FALSE(grid.placeTower({1, 1}));
}

TEST(HexGrid, TowerPlacementOccupiesAndBlocksTile)
{
    tHexGrid grid{3, 4, 10.0F};

    EXPECT_TRUE(grid.placeTower({0, 0}));
    EXPECT_TRUE(grid.isOccupied({0, 0}));
    EXPECT_FALSE(grid.isBuildable({0, 0}));
    EXPECT_FALSE(grid.isPassable({0, 0}));
    EXPECT_FALSE(grid.placeTower({0, 0}));

    EXPECT_TRUE(grid.removeTower({0, 0}));
    EXPECT_FALSE(grid.isOccupied({0, 0}));
    EXPECT_TRUE(grid.isBuildable({0, 0}));
    EXPECT_TRUE(grid.isPassable({0, 0}));
}

TEST(HexGrid, DerivesHexCentersFromRowColumnAndRowParity)
{
    const tHexGrid grid{3, 4, 10.0F};
    constexpr float tolerance = 0.001F;

    const auto rowZeroColZero = grid.hexCenter({0, 0});
    const auto rowZeroColOne = grid.hexCenter({0, 1});
    const auto rowOneColZero = grid.hexCenter({1, 0});

    EXPECT_NEAR(rowZeroColZero.X, 0.0F, tolerance);
    EXPECT_NEAR(rowZeroColZero.Y, 0.0F, tolerance);

    EXPECT_NEAR(rowZeroColOne.X, 10.0F * std::sqrt(3.0F), tolerance);
    EXPECT_NEAR(rowZeroColOne.Y, 0.0F, tolerance);

    EXPECT_NEAR(rowOneColZero.X, 10.0F * std::sqrt(3.0F) * 0.5F, tolerance);
    EXPECT_NEAR(rowOneColZero.Y, 15.0F, tolerance);
}

} // namespace
} // namespace maultd::core
