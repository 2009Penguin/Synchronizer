cmake_minimum_required(VERSION 3.10)
project(Synchronizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/json)
add_subdirectory(deps/spdlog)

add_executable(Synchronizer
        main.cpp
        core/config/ConfigManager.cpp
        core/config/ConfigManager.h
        core/TimeProvider/ITimeProvider.h
        core/TimeSetter/ITimeSetter.h
        core/TimeProvider/SmbProvider.cpp
        core/TimeProvider/SmbProvider.h
        core/TimeProvider/HttpProvider.cpp
        core/TimeProvider/HttpProvider.h
        core/TimeProvider/TimeProvider.cpp
        core/TimeProvider/TimeProvider.h
)

target_link_libraries(Synchronizer PRIVATE
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)
