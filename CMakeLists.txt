cmake_minimum_required(VERSION 3.24)

project(
    MaulTD
    VERSION 0.1.0
    DESCRIPTION "A learning-focused C++ tower defense game inspired by Wintermaul TD"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
)

FetchContent_MakeAvailable(raylib)

add_library(maultd_core
    src/core/game_state.cpp
    src/core/hex_grid.cpp
)

target_include_directories(maultd_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(maultd_core PUBLIC cxx_std_20)

add_executable(maultd
    src/main.cpp
)

target_link_libraries(maultd
    PRIVATE
        maultd_core
        raylib
)

include(CTest)

if(BUILD_TESTING)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(maultd_core_tests
        tests/hex_grid_tests.cpp
    )

    target_link_libraries(maultd_core_tests
        PRIVATE
            maultd_core
            GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(maultd_core_tests)
endif()
