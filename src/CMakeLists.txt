add_library(
    CubeLogic
    Cube.cpp
)

target_include_directories(CubeLogic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
    main
    main.cpp
)

target_link_libraries(
    main 
    PRIVATE CubeLogic sfml-graphics
)

# Copy the Python helper script to the build directory
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/kociemba_helper.py
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kociemba_helper.py
    COPYONLY
)

# Copy the font file to the build directory
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/arial.ttf
    COPYONLY
)