#include <SFML/Graphics.hpp>
#include "Cube.h"
#include <map>
#include <vector>
#include <random>
#include <iostream>

// Color mapping
std::map<Color, sf::Color> colorMap = {
    {Color::W, sf::Color::White}, {Color::Y, sf::Color::Yellow},
    {Color::G, sf::Color::Green}, {Color::B, sf::Color::Blue},
    {Color::R, sf::Color::Red},   {Color::O, sf::Color(255, 165, 0)}
};

// Helper function to draw one 3x3 face
void drawFace(sf::RenderWindow& window, const Face& face, sf::Vector2f startPosition) {
    const float TILE_SIZE = 40.f, GAP = 5.f;
    for (int i=0; i<3; ++i) for (int j=0; j<3; ++j) {
        sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        tile.setFillColor(colorMap[face.g[i][j]]);
        tile.setPosition(startPosition.x + j*(TILE_SIZE+GAP), startPosition.y + i*(TILE_SIZE+GAP));
        window.draw(tile);
    }
}

// Scramble function
std::string randomScramble(int m = 20) {
    std::vector<std::string> ml = {"U","U'","U2","D","D'","D2","F","F'","F2","B","B'","B2","L","L'","L2","R","R'","R2"};
    std::random_device rd; std::mt19937 g(rd());
    std::uniform_int_distribution<int> d(0, ml.size() - 1);
    std::string s; char l=0;
    for(int i=0; i<m; i++){ std::string move; do{move=ml[d(g)];}while(move[0]==l); s+=move+(i==m-1?"":" "); l=move[0]; }
    return s;
}

int main() {
    Cube cube;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rubik's Cube Solver");

    // Load font for instructions
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Could not load font file 'arial.ttf'.\n";
        return -1;
    }
    sf::Text instructions("Press 'S' to Scramble  |  'Enter' to Solve  |  'Esc' to Reset", font, 20);
    instructions.setPosition(20, 560);
    instructions.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) { // Scramble
                    std::string scrambleMoves = randomScramble();
                    cube.applySequence(scrambleMoves);
                }
                if (event.key.code == sf::Keyboard::Enter) { // Solve
                    // --- THIS IS THE CORRECT SOLVER CALL ---
                    std::string solution = cube.callKociembaSolver();
                    cube.applySequence(solution);
                }
                if (event.key.code == sf::Keyboard::Escape) { // Reset
                    cube = Cube(); // Create a new, solved cube
                }
            }
        }

        window.clear(sf::Color(40, 40, 40));

        const float TILE_SIZE = 40.f, GAP = 5.f, FACE_WIDTH = 3*TILE_SIZE+2*GAP;
        drawFace(window, cube.U, {FACE_WIDTH + GAP, 0.f + GAP});
        drawFace(window, cube.L, {0.f + GAP, FACE_WIDTH + GAP});
        drawFace(window, cube.F, {FACE_WIDTH + GAP, FACE_WIDTH + GAP});
        drawFace(window, cube.R, {2 * (FACE_WIDTH + GAP), FACE_WIDTH + GAP});
        drawFace(window, cube.B, {3 * (FACE_WIDTH + GAP), FACE_WIDTH + GAP});
        drawFace(window, cube.D, {FACE_WIDTH + GAP, 2 * (FACE_WIDTH + GAP)});
        
        window.draw(instructions);
        window.display();
    }
    return 0;
}