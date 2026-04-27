#pragma once

#include "maultd/core/hex_grid.h"

namespace maultd::core {

class GameState {
public:
    explicit GameState(HexGrid grid);

    void Update(double fixed_delta_seconds);

    [[nodiscard]] HexGrid& grid() noexcept;
    [[nodiscard]] const HexGrid& grid() const noexcept;
    [[nodiscard]] double elapsed_seconds() const noexcept;

private:
    HexGrid grid_;
    double elapsed_seconds_{0.0};
};

} // namespace maultd::core
