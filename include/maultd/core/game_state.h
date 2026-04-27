#pragma once

#include "maultd/core/hex_grid.h"

namespace maultd::core
{

class tGameState
{
public:
    explicit tGameState(tHexGrid grid);

    void update(double fixedDeltaSeconds);

    [[nodiscard]] tHexGrid& grid() noexcept;
    [[nodiscard]] const tHexGrid& grid() const noexcept;
    [[nodiscard]] double elapsedSeconds() const noexcept;

private:
    tHexGrid Grid;
    double ElapsedSeconds{0.0};
};

} // namespace maultd::core
