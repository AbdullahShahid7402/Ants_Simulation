cmake_minimum_required(VERSION 3.23)
project(Ants_Simulation)

set(CMAKE_CXX_STANDARD 23)



# Download and install SFML
include(FetchContent)
FetchContent_Declare(
        SFML
        URL https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip
)
FetchContent_GetProperties(SFML)
if(NOT SFML_POPULATED)
    FetchContent_Populate(SFML)
endif()

# Add SFML paths
set(SFML_DIR "C:/Users/wtcom/CLionProjects/Ants Simulation/cmake-build-debug/_deps/sfml-src/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

# Increase Stack Size
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,50000000")

# Add the executable
add_executable(Ants_Simulation main.cpp)

# Link SFML
target_link_libraries(Ants_Simulation PRIVATE sfml-graphics sfml-window)
