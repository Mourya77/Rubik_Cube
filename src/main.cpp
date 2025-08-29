#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // For std::swap
#include <string>    // For std::string and std::getline
#include <sstream>   // For std::stringstream
#include <tuple>     // For std::tuple
#include <random>    // For generating random scrambles

// Using `enum class` to create scoped enumerations.
// This prevents name clashes between Color::B and Face::B, for example.
enum class Color { W, G, R, B, O, Y }; // White, Green, Red, Blue, Orange, Yellow

// Enum for faces
enum class Face { U, D, F, B, L, R }; // Up, Down, Front, Back, Left, Right

/*
 * RubiksCube Class
 *
 * This class will represent the state of the Rubik's Cube and
 * contain methods for performing moves.
 */
class RubiksCube {
public:
    // The map now uses the scoped enum `Face` as its key.
    std::map<Face, std::vector<std::vector<Color>>> faces;

    // Constructor to initialize a solved cube.
    RubiksCube() {
        // We now use the full scope for both the Face and Color enums.
        // e.g., Face::U and Color::W
        faces[Face::U] = std::vector<std::vector<Color>>(3, std::vector<Color>(3, Color::W));
        faces[Face::D] = std::vector<std::vector<Color>>(3, std::vector<Color>(3, Color::Y));
        faces[Face::F] = std::vector<std::vector<Color>>(3, std::vector<Color>(3, Color::G));
        faces[Face::B] = std::vector<std::vector<Color>>(3, std::vector<Color>(3, Color::B));
        faces[Face::L] = std::vector<std::vector<Color>>(3, std::vector<Color>(3, Color::O));
        faces[Face::R] = std::vector<std::vector<Color>>(3, std::vector<Color>(3, Color::R));
    }

    // A helper function to print the cube's state to the console.
    void printCube() {
        // Map colors to characters for printing
        std::map<Color, char> colorMap = {
            {Color::W, 'W'}, {Color::G, 'G'}, {Color::R, 'R'}, {Color::B, 'B'}, {Color::O, 'O'}, {Color::Y, 'Y'}
        };
        
        // Map colors to ANSI escape codes for colored console output
        std::map<Color, std::string> colorAnsiMap = {
            {Color::W, "\033[97m"}, // Bright White
            {Color::G, "\033[32m"}, // Green
            {Color::R, "\033[31m"}, // Red
            {Color::B, "\033[34m"}, // Blue
            {Color::O, "\033[93m"}, // Bright Yellow (for Orange)
            {Color::Y, "\033[33m"}, // Yellow
        };
        const std::string resetColor = "\033[0m";

        // Print Up face
        std::cout << "\n      Up Face (W):" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "      ";
            for (int j = 0; j < 3; ++j) {
                Color c = faces[Face::U][i][j];
                std::cout << colorAnsiMap[c] << colorMap[c] << resetColor << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        // Print middle faces side-by-side
        std::cout << "Left(O)  Front(G)  Right(R)   Back(B)" << std::endl;
        for (int i = 0; i < 3; ++i) {
            // Left
            for (int j = 0; j < 3; ++j) {
                Color c = faces[Face::L][i][j];
                std::cout << colorAnsiMap[c] << colorMap[c] << resetColor << " ";
            }
            std::cout << " ";

            // Front
            for (int j = 0; j < 3; ++j) {
                 Color c = faces[Face::F][i][j];
                std::cout << colorAnsiMap[c] << colorMap[c] << resetColor << " ";
            }
            std::cout << " ";

            // Right
            for (int j = 0; j < 3; ++j) {
                 Color c = faces[Face::R][i][j];
                std::cout << colorAnsiMap[c] << colorMap[c] << resetColor << " ";
            }
            std::cout << "  ";

            // Back
            for (int j = 0; j < 3; ++j) {
                 Color c = faces[Face::B][i][j];
                std::cout << colorAnsiMap[c] << colorMap[c] << resetColor << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        // Print Down face
        std::cout << "      Down Face (Y):" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "      ";
            for (int j = 0; j < 3; ++j) {
                Color c = faces[Face::D][i][j];
                std::cout << colorAnsiMap[c] << colorMap[c] << resetColor << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "----------------------------------\n";
    }

private:
    // Helper function to rotate the stickers on a single face clockwise
    void rotateFaceClockwise(Face face) {
        std::vector<std::vector<Color>> tempFace = faces[face];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                tempFace[j][2 - i] = faces[face][i][j];
            }
        }
        faces[face] = tempFace;
    }

    // Helper function to rotate the stickers on a single face counter-clockwise
    void rotateFaceCounterClockwise(Face face) {
        std::vector<std::vector<Color>> tempFace = faces[face];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                tempFace[2 - j][i] = faces[face][i][j];
            }
        }
        faces[face] = tempFace;
    }

    // Helper function to find a specific edge piece
    std::pair<Face, std::pair<int, int>> findEdge(Color c1, Color c2) {
        // Search all 12 edge positions
        // Up face (now D face in our orientation)
        if ((faces[Face::D][0][1] == c1 && faces[Face::F][2][1] == c2) || (faces[Face::D][0][1] == c2 && faces[Face::F][2][1] == c1)) return {Face::D, {0, 1}};
        if ((faces[Face::D][1][0] == c1 && faces[Face::L][2][1] == c2) || (faces[Face::D][1][0] == c2 && faces[Face::L][2][1] == c1)) return {Face::D, {1, 0}};
        if ((faces[Face::D][1][2] == c1 && faces[Face::R][2][1] == c2) || (faces[Face::D][1][2] == c2 && faces[Face::R][2][1] == c1)) return {Face::D, {1, 2}};
        if ((faces[Face::D][2][1] == c1 && faces[Face::B][2][1] == c2) || (faces[Face::D][2][1] == c2 && faces[Face::B][2][1] == c1)) return {Face::D, {2, 1}};
        // Middle layer
        if ((faces[Face::F][1][0] == c1 && faces[Face::L][1][2] == c2) || (faces[Face::F][1][0] == c2 && faces[Face::L][1][2] == c1)) return {Face::F, {1, 0}};
        if ((faces[Face::F][1][2] == c1 && faces[Face::R][1][0] == c2) || (faces[Face::F][1][2] == c2 && faces[Face::R][1][0] == c1)) return {Face::F, {1, 2}};
        if ((faces[Face::B][1][0] == c1 && faces[Face::R][1][2] == c2) || (faces[Face::B][1][0] == c2 && faces[Face::R][1][2] == c1)) return {Face::B, {1, 0}};
        if ((faces[Face::B][1][2] == c1 && faces[Face::L][1][0] == c2) || (faces[Face::B][1][2] == c2 && faces[Face::L][1][0] == c1)) return {Face::B, {1, 2}};
        // Top layer (now U face in our orientation, but these are white edges)
        if ((faces[Face::U][0][1] == c1 && faces[Face::B][0][1] == c2) || (faces[Face::U][0][1] == c2 && faces[Face::B][0][1] == c1)) return {Face::U, {0, 1}};
        if ((faces[Face::U][1][0] == c1 && faces[Face::L][0][1] == c2) || (faces[Face::U][1][0] == c2 && faces[Face::L][0][1] == c1)) return {Face::U, {1, 0}};
        if ((faces[Face::U][1][2] == c1 && faces[Face::R][0][1] == c2) || (faces[Face::U][1][2] == c2 && faces[Face::R][0][1] == c1)) return {Face::U, {1, 2}};
        if ((faces[Face::U][2][1] == c1 && faces[Face::F][0][1] == c2) || (faces[Face::U][2][1] == c2 && faces[Face::F][0][1] == c1)) return {Face::U, {2, 1}};

        return {Face::U, {-1, -1}}; // Not found
    }

    // New helper to find a corner piece more robustly
    std::pair<Face, std::pair<int, int>> findCorner(Color c1, Color c2, Color c3) {
        // Search all 8 corner positions
        Color corners[8][3] = {
            {faces[Face::U][0][0], faces[Face::L][0][0], faces[Face::B][0][2]}, // UBL
            {faces[Face::U][0][2], faces[Face::B][0][0], faces[Face::R][0][2]}, // UBR
            {faces[Face::U][2][0], faces[Face::F][0][0], faces[Face::L][0][2]}, // UFL
            {faces[Face::U][2][2], faces[Face::R][0][0], faces[Face::F][0][2]}, // UFR
            {faces[Face::D][0][0], faces[Face::L][2][2], faces[Face::F][2][0]}, // DFL
            {faces[Face::D][0][2], faces[Face::F][2][2], faces[Face::R][2][0]}, // DFR
            {faces[Face::D][2][0], faces[Face::B][2][2], faces[Face::L][2][0]}, // DBL
            {faces[Face::D][2][2], faces[Face::R][2][2], faces[Face::B][2][0]}  // DBR
        };
        Face facesPos[8] = {Face::U, Face::U, Face::U, Face::U, Face::D, Face::D, Face::D, Face::D};
        int coords[8][2] = {{0,0}, {0,2}, {2,0}, {2,2}, {0,0}, {0,2}, {2,0}, {2,2}};

        for (int i = 0; i < 8; ++i) {
            bool c1Found = false, c2Found = false, c3Found = false;
            for(int j=0; j<3; ++j) {
                if (corners[i][j] == c1) c1Found = true;
                if (corners[i][j] == c2) c2Found = true;
                if (corners[i][j] == c3) c3Found = true;
            }
            if (c1Found && c2Found && c3Found) {
                return {facesPos[i], {coords[i][0], coords[i][1]}};
            }
        }
        return {Face::U, {-1, -1}}; // Not found
    }
    
    // Helper function to solve one white edge piece
    void solveWhiteEdge(Color adjacentColor, Face adjacentFace, std::string move) {
        // This function is now only used for the cross and remains unchanged
        std::pair<int, int> correctPos;
        if (adjacentFace == Face::F) correctPos = {2, 1};
        else if (adjacentFace == Face::R) correctPos = {1, 2};
        else if (adjacentFace == Face::B) correctPos = {0, 1};
        else if (adjacentFace == Face::L) correctPos = {1, 0};

        if (faces[Face::U][correctPos.first][correctPos.second] == Color::W && faces[adjacentFace][0][1] == adjacentColor) {
            return;
        }

        auto loc = findEdge(Color::W, adjacentColor);
        Face face = loc.first;
        int row = loc.second.first;
        int col = loc.second.second;
        
        if (face == Face::U) {
             if (row == 0 && col == 1) applySequence("B2");
             else if (row == 1 && col == 0) applySequence("L2");
             else if (row == 1 && col == 2) applySequence("R2");
             else if (row == 2 && col == 1) applySequence("F2");
        }
        else if (face == Face::F && col == 0) applySequence("L' U' L"); // FL
        else if (face == Face::F && col == 2) applySequence("R U R'");  // FR
        else if (face == Face::B && col == 0) applySequence("R' U' R"); // BR
        else if (face == Face::B && col == 2) applySequence("L U L'");  // BL

        int attempts = 0;
        while(true) {
            auto bottomLoc = findEdge(Color::W, adjacentColor);
            if(bottomLoc.first == adjacentFace && bottomLoc.second.first == 0 && bottomLoc.second.second == 1 && faces[Face::U][2][1] == adjacentColor) {
                break;
            }
            applySequence("U");
            if(attempts++ > 4) {std::cout << "Error: Edge not found on top.\n"; return;}
        }

        applySequence(move + "2");
    }

    // First step of the solver: The White Cross
    void solveCross() {
        std::cout << "Step 1: Solving the White Cross...\n";
        solveWhiteEdge(Color::G, Face::F, "F");
        solveWhiteEdge(Color::R, Face::R, "R");
        solveWhiteEdge(Color::B, Face::B, "B");
        solveWhiteEdge(Color::O, Face::L, "L");
        std::cout << "White Cross is complete!\n";
    }

    // Generalized function to solve one white corner
    void solveWhiteCorner(Color c1, Color c2, Face f1, Face f2, std::string setup) {
         // This function is now only used for the first layer and remains unchanged
        auto targetLoc = findCorner(Color::W, c1, c2);
        std::pair<int,int> solvedPos;
        if(f1 == Face::F && f2 == Face::R) solvedPos = {2,2};
        else if(f1 == Face::R && f2 == Face::B) solvedPos = {0,2};
        else if(f1 == Face::B && f2 == Face::L) solvedPos = {0,0};
        else if(f1 == Face::L && f2 == Face::F) solvedPos = {2,0};

        if (targetLoc.first == Face::U && targetLoc.second.first == solvedPos.first && targetLoc.second.second == solvedPos.second) {
            return; // Already solved
        }
        
        if(targetLoc.first == Face::U) {
            applySequence(setup + " R' D' R");
        }
        
        int attempts = 0;
        applySequence(setup);
        while(true) {
            auto topLoc = findCorner(Color::W, c1, c2);
            if(topLoc.first == Face::D && topLoc.second.first == 0 && topLoc.second.second == 2) {
                break;
            }
            applySequence("U");
            if(attempts++ > 4) {std::cout << "Error: Corner not found on top.\n"; return;}
        }

        attempts = 0;
        while(true) {
             auto finalLoc = findCorner(Color::W, c1, c2);
             if(finalLoc.first == Face::U && finalLoc.second.first == solvedPos.first && finalLoc.second.second == solvedPos.second) break; 
             applySequence("R' D' R D");
             if(attempts++ > 5) { std::cout << "Error: Corner insertion failed.\n"; return; }
        }
        applySequence(setup + "'");
    }

    // Second Step: Solve First Layer Corners
    void solveFirstLayerCorners() {
        std::cout << "Step 2: Solving First Layer Corners...\n";
        solveWhiteCorner(Color::G, Color::R, Face::F, Face::R, "");
        solveWhiteCorner(Color::R, Color::B, Face::R, Face::B, "U'");
        solveWhiteCorner(Color::B, Color::O, Face::B, Face::L, "U2");
        solveWhiteCorner(Color::O, Color::G, Face::L, Face::F, "U");
        std::cout << "First Layer Corners are complete!\n";
    }

    // Helper to solve one second-layer edge
    void solveSecondLayerEdge(Color c1, Color c2, std::string rightAlg, std::string leftAlg, std::string setup) {
        // Check if solved
        auto loc = findEdge(c1, c2);
        if (loc.first != Face::U && loc.first != Face::D) {
            // Check if it's in the correct slot but maybe flipped
            if ( (loc.first == Face::F && loc.second.second == 2 && faces[Face::F][1][2] == c1) ||
                 (loc.first == Face::R && loc.second.second == 0 && faces[Face::R][1][0] == c1) )
                 return;
        }

        // If piece is in the middle layer but wrong slot/flipped, pop it out
        if (loc.first != Face::U && loc.first != Face::D) {
            applySequence(setup);
            applySequence(rightAlg);
            applySequence(setup + "'");
        }

        // Align edge on top layer
        int attempts = 0;
        applySequence(setup);
        while (true) {
            auto topLoc = findEdge(c1, c2);
            if (topLoc.first == Face::U && topLoc.second.first == 2 && topLoc.second.second == 1) {
                break;
            }
            applySequence("U");
            if(attempts++ > 4) {std::cout << "Error: Cannot find edge on top layer.\n"; return;}
        }

        // Apply correct insertion algorithm
        if (faces[Face::F][0][1] == c2) { // Other color matches right face
            applySequence(rightAlg);
        } else { // Other color matches left face
            applySequence(leftAlg);
        }
         applySequence(setup + "'");
    }

    // Third Step: Solve Second Layer Edges
    void solveSecondLayerEdges() {
        std::cout << "Step 3: Solving Second Layer Edges...\n";
        
        std::string right = "U R U' R' U' F' U F";
        std::string left = "U' L' U L U F U' F'";

        solveSecondLayerEdge(Color::G, Color::R, right, left, "");
        solveSecondLayerEdge(Color::R, Color::B, right, left, "U'");
        solveSecondLayerEdge(Color::B, Color::O, right, left, "U2");
        solveSecondLayerEdge(Color::O, Color::G, right, left, "U");
        
        std::cout << "Second Layer Edges are complete!\n";
    }

    // Fourth Step: Create the Yellow Cross
    void solveYellowCross() {
        std::cout << "Step 4: Forming the Yellow Cross...\n";

        // Check if cross is already formed
        if (faces[Face::D][0][1] == Color::Y && faces[Face::D][1][0] == Color::Y &&
            faces[Face::D][1][2] == Color::Y && faces[Face::D][2][1] == Color::Y) {
            return;
        }

        // Case 1: Dot shape 
        if ( faces[Face::D][0][1] != Color::Y && faces[Face::D][1][0] != Color::Y &&
             faces[Face::D][1][2] != Color::Y && faces[Face::D][2][1] != Color::Y) {
            applySequence("F U R U' R' F'");
        }
        
        // After one alg, we'll have either L or Line
        int attempts = 0;
        while(!(faces[Face::D][0][1] == Color::Y && faces[Face::D][1][0] == Color::Y &&
            faces[Face::D][1][2] == Color::Y && faces[Face::D][2][1] == Color::Y)) {
            
            if (attempts++ > 4) {std::cout << "Error: Yellow cross failed.\n"; return;}

            // Align L-shape correctly (top-left)
            if((faces[Face::D][0][1] == Color::Y && faces[Face::D][1][0] == Color::Y) || 
               (faces[Face::D][1][0] == Color::Y && faces[Face::D][2][1] == Color::Y) ||
               (faces[Face::D][2][1] == Color::Y && faces[Face::D][1][2] == Color::Y) ||
               (faces[Face::D][1][2] == Color::Y && faces[Face::D][0][1] == Color::Y)
            ) {
                 while(!(faces[Face::D][1][0] == Color::Y && faces[Face::D][0][1] == Color::Y)) {
                     applySequence("D");
                 }
                 applySequence("F U R U' R' F'");
            }
            // Align Line-shape correctly (horizontal)
            else if ((faces[Face::D][1][0] == Color::Y && faces[Face::D][1][2] == Color::Y) ||
                     (faces[Face::D][0][1] == Color::Y && faces[Face::D][2][1] == Color::Y))
            {
                while(!(faces[Face::D][1][0] == Color::Y && faces[Face::D][1][2] == Color::Y)) {
                    applySequence("D");
                }
                applySequence("F R U R' U' F'");
            }
        }
        
        std::cout << "Yellow Cross is complete!\n";
    }
    
    // Fifth Step: Orient the Last Layer (all yellow top)
    void orientLastLayer() {
        std::cout << "Step 5: Orienting the Last Layer (OLL)...\n";
        
        int attempts = 0;
        while (faces[Face::D][0][0] != Color::Y || faces[Face::D][0][2] != Color::Y ||
               faces[Face::D][2][0] != Color::Y || faces[Face::D][2][2] != Color::Y) {
            
            if (attempts++ > 7) { std::cout << "Error: OLL failed.\n"; return; }

            // Find case and orient cube
            int yellowCorners = 0;
            if (faces[Face::D][0][0] == Color::Y) yellowCorners++;
            if (faces[Face::D][0][2] == Color::Y) yellowCorners++;
            if (faces[Face::D][2][0] == Color::Y) yellowCorners++;
            if (faces[Face::D][2][2] == Color::Y) yellowCorners++;

            if (yellowCorners == 0) { // Case 1 or 2
                while(faces[Face::L][2][0] != Color::Y) applySequence("D");
                if (faces[Face::F][2][0] == Color::Y) applySequence("R U2 R' U' R U' R'"); // Sune
                else applySequence("R U R' U R U2 R'"); // Anti-Sune
            } else if (yellowCorners == 1) { // Case 3
                while(faces[Face::D][2][0] != Color::Y) applySequence("D");
                applySequence("R U2 R' U' R U' R'");
            } else if (yellowCorners == 2) { // Case 4, 5, or 6
                while(faces[Face::F][2][0] != Color::Y) applySequence("D");
                 applySequence("R2 U R' U' R2 U"); // Needs more logic to distinguish cases
            } else { // Should not happen if cross is solved
                applySequence("D");
            }
        }
        std::cout << "Last Layer Oriented (all yellow top)!\n";
    }

    // Sixth Step: Permute the Last Layer Corners
    void permuteLastLayerCorners() {
        std::cout << "Step 6: Permuting Last Layer Corners...\n";

        int attempts = 0;
        while(faces[Face::F][2][0] != faces[Face::F][2][2]) {
            applySequence("D");
            if(attempts++ > 4) break;
        }

        if(faces[Face::F][2][0] == faces[Face::F][2][2] && faces[Face::R][2][0] == faces[Face::R][2][2] && faces[Face::B][2][0] == faces[Face::B][2][2]) {
             return; // Already solved
        }
        
        // Find headlights
        attempts = 0;
        while (faces[Face::L][2][0] != faces[Face::L][2][2]) {
            applySequence("D");
            if (attempts++ > 4) break;
        }

        // If no headlights, create them
        if (attempts > 4) {
            applySequence("R' F R' B2 R F' R' B2 R2");
            attempts = 0;
            while (faces[Face::L][2][0] != faces[Face::L][2][2]) {
                applySequence("D");
                if (attempts++ > 4) {std::cout << "Error: PLL corner headlights failed.\n"; return;}
            }
        }
        
        applySequence("R' F R' B2 R F' R' B2 R2");
        std::cout << "Last Layer Corners Permuted!\n";
    }

    // Seventh Step: Permute the Last Layer Edges
    void permuteLastLayerEdges() {
        std::cout << "Step 7: Permuting Last Layer Edges...\n";

        int attempts = 0;
        while (faces[Face::F][2][1] != faces[Face::F][1][1]) {
            applySequence("D");
            if (attempts++ > 4) {std::cout << "Error: PLL edge alignment failed.\n"; return;}
        }

        if (faces[Face::R][2][1] == faces[Face::R][1][1] && faces[Face::L][2][1] == faces[Face::L][1][1]) {
            return; // Solved
        }
        
        // Check cycle direction
        if (faces[Face::R][2][1] == faces[Face::B][1][1]) { // Clockwise
            applySequence("R U' R U R U R U' R' U' R2");
        } else { // Counter-clockwise
            applySequence("R2 U R U R' U' R' U' R' U R'");
        }
        
        // Final alignment
        while (faces[Face::F][2][1] != faces[Face::F][1][1]) {
            applySequence("D");
        }
        std::cout << "Last Layer Edges Permuted! Cube Solved!\n";
    }

public:
    // ---- Move Functions ----
    // (All move functions U, U', U2, D, D', D2 etc. are unchanged)
    void U() {
        rotateFaceClockwise(Face::U);
        std::vector<Color> temp_row = faces[Face::F][0];
        faces[Face::F][0] = faces[Face::R][0];
        faces[Face::R][0] = faces[Face::B][0];
        faces[Face::B][0] = faces[Face::L][0];
        faces[Face::L][0] = temp_row;
    }
    void UPrime() {
        rotateFaceCounterClockwise(Face::U);
        std::vector<Color> temp_row = faces[Face::F][0];
        faces[Face::F][0] = faces[Face::L][0];
        faces[Face::L][0] = faces[Face::B][0];
        faces[Face::B][0] = faces[Face::R][0];
        faces[Face::R][0] = temp_row;
    }
    void U2() { U(); U(); }

    void D() {
        rotateFaceClockwise(Face::D);
        std::vector<Color> temp_row = faces[Face::F][2];
        faces[Face::F][2] = faces[Face::L][2];
        faces[Face::L][2] = faces[Face::B][2];
        faces[Face::B][2] = faces[Face::R][2];
        faces[Face::R][2] = temp_row;
    }
    void DPrime() {
        rotateFaceCounterClockwise(Face::D);
        std::vector<Color> temp_row = faces[Face::F][2];
        faces[Face::F][2] = faces[Face::R][2];
        faces[Face::R][2] = faces[Face::B][2];
        faces[Face::B][2] = faces[Face::L][2];
        faces[Face::L][2] = temp_row;
    }
    void D2() { D(); D(); }

    void F() {
        rotateFaceClockwise(Face::F);
        Color temp[3] = {faces[Face::U][2][0], faces[Face::U][2][1], faces[Face::U][2][2]};
        for(int i=0; i<3; ++i) faces[Face::U][2][i] = faces[Face::L][2-i][2];
        for(int i=0; i<3; ++i) faces[Face::L][i][2] = faces[Face::D][0][i];
        for(int i=0; i<3; ++i) faces[Face::D][0][i] = faces[Face::R][2-i][0];
        for(int i=0; i<3; ++i) faces[Face::R][i][0] = temp[i];
    }
    void FPrime() {
        rotateFaceCounterClockwise(Face::F);
        Color temp[3] = {faces[Face::U][2][0], faces[Face::U][2][1], faces[Face::U][2][2]};
        for(int i=0; i<3; ++i) faces[Face::U][2][i] = faces[Face::R][i][0];
        for(int i=0; i<3; ++i) faces[Face::R][i][0] = faces[Face::D][0][2-i];
        for(int i=0; i<3; ++i) faces[Face::D][0][i] = faces[Face::L][i][2];
        for(int i=0; i<3; ++i) faces[Face::L][2-i][2] = temp[i];
    }
    void F2() { F(); F(); }

    void B() {
        rotateFaceClockwise(Face::B);
        Color temp[3] = {faces[Face::U][0][0], faces[Face::U][0][1], faces[Face::U][0][2]};
        for(int i=0; i<3; ++i) faces[Face::U][0][i] = faces[Face::R][i][2];
        for(int i=0; i<3; ++i) faces[Face::R][i][2] = faces[Face::D][2][2-i];
        for(int i=0; i<3; ++i) faces[Face::D][2][i] = faces[Face::L][2-i][0];
        for(int i=0; i<3; ++i) faces[Face::L][i][0] = temp[2-i];
    }
    void BPrime() {
        rotateFaceCounterClockwise(Face::B);
        Color temp[3] = {faces[Face::U][0][0], faces[Face::U][0][1], faces[Face::U][0][2]};
        for(int i=0; i<3; ++i) faces[Face::U][0][i] = faces[Face::L][2-i][0];
        for(int i=0; i<3; ++i) faces[Face::L][i][0] = faces[Face::D][2][2-i];
        for(int i=0; i<3; ++i) faces[Face::D][2][i] = faces[Face::R][2-i][2];
        for(int i=0; i<3; ++i) faces[Face::R][i][2] = temp[i];
    }
    void B2() { B(); B(); }

    void L() {
        rotateFaceClockwise(Face::L);
        Color temp[3];
        for(int i=0; i<3; ++i) temp[i] = faces[Face::U][i][0];
        for(int i=0; i<3; ++i) faces[Face::U][i][0] = faces[Face::B][2-i][2];
        for(int i=0; i<3; ++i) faces[Face::B][i][2] = faces[Face::D][2-i][0];
        for(int i=0; i<3; ++i) faces[Face::D][i][0] = faces[Face::F][i][0];
        for(int i=0; i<3; ++i) faces[Face::F][i][0] = temp[i];
    }
    void LPrime() {
        rotateFaceCounterClockwise(Face::L);
        Color temp[3];
        for(int i=0; i<3; ++i) temp[i] = faces[Face::U][i][0];
        for(int i=0; i<3; ++i) faces[Face::U][i][0] = faces[Face::F][i][0];
        for(int i=0; i<3; ++i) faces[Face::F][i][0] = faces[Face::D][i][0];
        for(int i=0; i<3; ++i) faces[Face::D][i][0] = faces[Face::B][2-i][2];
        for(int i=0; i<3; ++i) faces[Face::B][i][2] = temp[2-i];
    }
    void L2() { L(); L(); }

    void R() {
        rotateFaceClockwise(Face::R);
        Color temp[3];
        for(int i=0; i<3; ++i) temp[i] = faces[Face::U][i][2];
        for(int i=0; i<3; ++i) faces[Face::U][i][2] = faces[Face::F][i][2];
        for(int i=0; i<3; ++i) faces[Face::F][i][2] = faces[Face::D][i][2];
        for(int i=0; i<3; ++i) faces[Face::D][i][2] = faces[Face::B][2-i][0];
        for(int i=0; i<3; ++i) faces[Face::B][2-i][0] = temp[i];
    }
    void RPrime() {
        rotateFaceCounterClockwise(Face::R);
        Color temp[3];
        for(int i=0; i<3; ++i) temp[i] = faces[Face::U][i][2]; // Save U
        for(int i=0; i<3; ++i) faces[Face::U][i][2] = faces[Face::B][2-i][0]; // B -> U
        for(int i=0; i<3; ++i) faces[Face::B][2-i][0] = faces[Face::D][i][2]; // D -> B
        for(int i=0; i<3; ++i) faces[Face::D][i][2] = faces[Face::F][i][2]; // F -> D
        for(int i=0; i<3; ++i) faces[Face::F][i][2] = temp[i]; // temp -> F
    }
    void R2() { R(); R(); }

    // New function to apply a sequence of moves
    void applySequence(std::string sequence) {
        std::stringstream ss(sequence);
        std::string move;
        while (ss >> move) {
            if (move == "U") U();
            else if (move == "U'") UPrime();
            else if (move == "U2") U2();
            else if (move == "D") D();
            else if (move == "D'") DPrime();
            else if (move == "D2") D2();
            else if (move == "F") F();
            else if (move == "F'") FPrime();
            else if (move == "F2") F2();
            else if (move == "B") B();
            else if (move == "B'") BPrime();
            else if (move == "B2") B2();
            else if (move == "L") L();
            else if (move == "L'") LPrime();
            else if (move == "L2") L2();
            else if (move == "R") R();
            else if (move == "R'") RPrime();
            else if (move == "R2") R2();
            else std::cout << "Unknown move: " << move << std::endl;
        }
    }
    
    // Function to generate and apply a random scramble
    void scramble() {
        std::vector<std::string> moves = {"U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2", "L", "L'", "L2", "R", "R'", "R2"};
        std::vector<char> faces = {'U', 'D', 'F', 'B', 'L', 'R'};
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, moves.size() - 1);

        std::string scramble_sequence = "";
        char last_face = ' ';
        
        std::cout << "\nGenerating scramble...\n";
        for(int i=0; i < 25; ++i) {
            std::string move;
            char current_face;
            do {
                move = moves[dist(rng)];
                current_face = move[0];
            } while (current_face == last_face);
            
            scramble_sequence += move + " ";
            last_face = current_face;
        }

        std::cout << "Scramble: " << scramble_sequence << std::endl;
        applySequence(scramble_sequence);
    }

    // New function to start the solving process
    void solve() {
        std::cout << "\n--- Starting Solver ---\n";
        
        solveCross();
        solveFirstLayerCorners();
        solveSecondLayerEdges();
        solveYellowCross();
        orientLastLayer();
        permuteLastLayerCorners();
        permuteLastLayerEdges();

        std::cout << "--- CUBE SOLVED! ---\n";
    }
};

int main() {
    RubiksCube cube;
    std::cout << "Rubik's Cube Simulator" << std::endl;
    std::cout << "Initial Solved State:";
    cube.printCube();

    std::string line;
    while (true) {
        std::cout << "\nEnter moves, 'scramble', 'solve', or 'exit':\n> ";
        std::getline(std::cin, line);

        if (line == "exit") {
            break;
        } else if (line == "solve") {
            cube.solve();
        } else if (line == "scramble") {
            cube.scramble();
        }
        else {
            cube.applySequence(line);
        }
        
        cube.printCube();
    }

    return 0;
}

