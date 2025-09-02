# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.14)

# Define the project name
project(RubiksCubeSolver)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake to place the final executable in the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# --- Download Dependencies ---
# Enable FetchContent for downloading dependencies
include(FetchContent)

# Declare and download the GoogleTest project
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# --- ADDED FOR SFML ---
# Declare and download the SFML graphics library
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG    2.6.x
)
FetchContent_MakeAvailable(SFML)
# --- END OF SFML SECTION ---

# Enable testing for our project
enable_testing()

# Tell CMake to look inside the 'src' and 'tests' directories
add_subdirectory(src)
add_subdirectory(tests)