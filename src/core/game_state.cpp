#include "maultd/core/game_state.h"

#include <utility>

namespace maultd::core
{

tGameState::tGameState(tHexGrid grid)
    : Grid(std::move(grid))
{
}

void tGameState::update(double fixedDeltaSeconds)
{
    ElapsedSeconds += fixedDeltaSeconds;
}

tHexGrid& tGameState::grid() noexcept
{
    return Grid;
}

const tHexGrid& tGameState::grid() const noexcept
{
    return Grid;
}

double tGameState::elapsedSeconds() const noexcept
{
    return ElapsedSeconds;
}

} // namespace maultd::core
