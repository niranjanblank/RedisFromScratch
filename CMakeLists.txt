
cmake_minimum_required(VERSION 3.16)

# Project name and language
project(RedisFromScratch LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify where the compiled executables will be placed
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

# -------------------------------
# Build redis_server executable
# -------------------------------
# This will compile src/server.cpp into an executable named "redis_server"
add_executable(server
    src/server.cpp
)

# -------------------------------
# Build redis_client executable
# -------------------------------
# This will compile src/client.cpp into an executable named "redis_client"
add_executable(client
    src/client.cpp
)

# -------------------------------
# Compiler warnings (for GCC/Clang)
# -------------------------------
# Enables common warning flags to help catch potential bugs early.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(server PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(client PRIVATE -Wall -Wextra -Wpedantic)
endif()

