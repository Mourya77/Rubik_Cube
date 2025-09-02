#include "gtest/gtest.h" // The Google Test framework
#include "Cube.h"       // Our Cube class

// Test case to verify that a move followed by its inverse results in the original state.
TEST(CubeMoves, RotateAndInvert) {
    Cube c;
    
    // The cube should start in a solved state
    ASSERT_TRUE(c.isSolved());

    // Perform a sequence of moves
    c.applySequence("R U' B2 L");

    // The cube should now be scrambled
    ASSERT_FALSE(c.isSolved());

    // Perform the inverse sequence
    c.applySequence("L' B2 U R'");

    // The cube should be solved again
    ASSERT_TRUE(c.isSolved());
}

// Another test case to verify that 6 "sexy moves" is a cycle
TEST(CubeMoves, SexyMoveCycle) {
    Cube c;
    
    ASSERT_TRUE(c.isSolved());
    
    // A "sexy move" is R U R' U'
    for (int i = 0; i < 6; ++i) {
        c.applySequence("R U R' U'");
    }

    ASSERT_TRUE(c.isSolved());
}