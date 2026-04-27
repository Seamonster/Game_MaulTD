# Roadmap

## Milestone 1: Repo and Build Scaffold

- Create the CMake project.
- Add a minimal Raylib desktop app.
- Add a graphics-free core library.
- Add GoogleTest unit tests.
- Document project rules and assistant context.

## Milestone 2: Hex Grid and Tile Validation

- Expand the grid model.
- Add buildable, occupied, spawn, waypoint, and exit tile state.
- Add coordinate display helpers for debug views.
- Test tile validation rules.

## Milestone 3: Waypoints and Pathfinding

- Define ordered waypoint routes.
- Add pathfinding between waypoint targets.
- Prevent normal paths from using occupied tiles.
- Detect when no valid path exists.
- Test normal path and blocked-path scenarios.

## Milestone 4: Enemy Movement and Breach Mode

- Add enemy state and movement along computed paths.
- Add waypoint progression.
- Add breach mode movement when pathfinding fails.
- Track enemies that exit the map.
- Test movement and breach transitions.

## Milestone 5: Tower Placement and Debug Overlays

- Add basic tower placement input.
- Validate tower placement against buildability rules.
- Add debug overlays for coordinates, buildability, occupancy, paths, and waypoints.
- Add an event log for placement, movement, and combat events.

## Later Milestones

- Basic tower targeting and attacks.
- Economy with passive income and kill rewards.
- Upgrade paths for fire, ice, and lightning towers.
- Enemy classes and elemental strengths or weaknesses.
- Data-driven balancing.
- Mobile portability review.
