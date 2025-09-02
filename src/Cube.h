#pragma once
#include <string>
#include <vector>
#include <map>
#include <array>

enum class Color { W, Y, G, B, R, O };
struct Face { std::array<std::array<Color, 3>, 3> g; };

class Cube {
public:
    Face U, D, F, B, L, R;
    Cube();
    void printCube() const;
    void applySequence(const std::string &seq);
    bool isSolved() const;
    std::string toKociembaFaceletString() const;
    std::string callKociembaSolver() const; // Restore this function

private:
    void fillFace(Face &f, Color c);
    static void rotCW(Face &f);
    void move_U(); void move_D(); void move_F();
    void move_B(); void move_L(); void move_R();
    void applyMoveToken(const std::string &tok);
};