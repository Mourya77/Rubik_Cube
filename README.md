Rubik's Cube Solver in C++

An interactive 2D Rubik's Cube solver built from the ground up in C++ with the SFML graphics library. This project features a robust, multi-file structure, a CMake build system, and a reliable Python-based solver back-end.

✨ Features
Interactive 2D GUI: Visualizes all six faces of the cube in a classic unfolded layout.

Scramble & Solve: Instantly scramble the cube to a random state or solve it with the press of a key.

Professional Structure: The project is organized using modern C++ principles, a CMake build system, and includes a suite of unit tests with Google Test to verify the core logic.

Cross-Platform: Uses CMake and SFML to ensure the project can be built and run on Windows, macOS, and Linux.

🛠️ Tech Stack & Libraries
C++17: For the core application logic and display.

SFML: A simple and fast multimedia library for handling the window, graphics, and user input.

Python: The kociemba library is used as a fast and reliable back-end for the solving algorithm.

CMake: For managing the build process and dependencies in a cross-platform way.

Google Test: For writing and running unit tests to ensure the cube's move logic is correct.

⚙️ Setup and Build Instructions
Prerequisites
Before you begin, ensure you have the following installed:

A modern C++ compiler (like g++ from MSYS2 on Windows).

CMake (version 3.14 or higher).

Git.

Python and the kociemba library: pip install kociemba

Build Steps
You can build the project by running the following commands from the project's root directory:
# 1. Clone the repository (if you haven't already)
# git clone https://github.com/YourUsername/YourRepoName.git
# cd YourRepoName

# 2. Create a build directory
mkdir build
cd build

# 3. Configure the project with CMake
# (On Windows with MinGW)
cmake -G "MinGW Makefiles" ..

# 4. Compile the project
cmake --build .

⌨️ How to Use
Run the executable from the build directory:
./main
Use the following keys to interact with the solver:

S: Scrambles the cube.

Enter: Solves the cube.

Esc: Resets the cube to its initial, solved state.

🚀 Future Improvements
Full 3D Rendering: Upgrade the 2D view to a fully interactive 3D cube using OpenGL.

Computer Vision: Integrate OpenCV to read a physical cube's state using a webcam.