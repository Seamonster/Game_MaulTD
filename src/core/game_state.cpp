#include "maultd/core/game_state.h"

#include <utility>

namespace maultd::core {

GameState::GameState(HexGrid grid)
    : grid_(std::move(grid))
{
}

void GameState::Update(double fixed_delta_seconds)
{
    elapsed_seconds_ += fixed_delta_seconds;
}

HexGrid& GameState::grid() noexcept
{
    return grid_;
}

const HexGrid& GameState::grid() const noexcept
{
    return grid_;
}

double GameState::elapsed_seconds() const noexcept
{
    return elapsed_seconds_;
}

} // namespace maultd::core
