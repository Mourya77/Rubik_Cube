# Create the test executable
add_executable(
    runTests
    CubeTests.cpp
)

# Link our tests against the CubeLogic library and the GoogleTest library
target_link_libraries(
    runTests
    PRIVATE CubeLogic GTest::gtest_main
)

# Add the test to CMake's test runner (CTest)
add_test(
    NAME CubeLogicTests
    COMMAND runTests
)