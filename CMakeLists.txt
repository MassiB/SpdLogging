cmake_minimum_required(VERSION 3.10)

# -----------------------------------------------
# Set the project name
project(SPDLOGGING VERSION 1.0 LANGUAGES CXX)

# -----------------------------------------------
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -----------------------------------------------
# List the source files
set(SOURCES
    main.cpp
)

# -----------------------------------------------
# Add the executable target
add_executable(SPDLOGGING ${SOURCES})

# -----------------------------------------------
# Add spdlog as an external project
add_subdirectory(spdlog)

# -----------------------------------------------
# Include the directory with the header files
target_include_directories(SPDLOGGING PRIVATE ${PROJECT_SOURCE_DIR}/spdlog/include)

# -----------------------------------------------
# Add libraries
target_link_libraries(SPDLOGGING spdlog::spdlog)
