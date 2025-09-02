#include "Cube.h"
#include <iostream>
#include <sstream>
#include <cstdio>
#include <memory>

// Color Maps and other helpers from before...
static const std::map<Color, char> COLOR_TO_CHAR = { {Color::W, 'W'}, {Color::Y, 'Y'}, {Color::G, 'G'}, {Color::B, 'B'}, {Color::R, 'R'}, {Color::O, 'O'} };
static const std::map<Color, std::string> COLOR_TO_ANSI = { {Color::W, "\033[97m"}, {Color::Y, "\033[93m"}, {Color::G, "\033[92m"}, {Color::B, "\033[94m"}, {Color::R, "\033[91m"}, {Color::O, "\033[38;5;208m"} };
static const std::string ANSI_RESET = "\033[0m";
static char colorToFacelet(Color c) {
    switch (c) {
        case Color::W: return 'U'; case Color::Y: return 'D'; case Color::G: return 'F';
        case Color::B: return 'B'; case Color::R: return 'R'; case Color::O: return 'L';
        default: return ' ';
    }
}

Cube::Cube() { fillFace(U, Color::W); fillFace(D, Color::Y); fillFace(F, Color::G); fillFace(B, Color::B); fillFace(L, Color::O); fillFace(R, Color::R); }
void Cube::fillFace(Face &f, Color c) { for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) f.g[i][j] = c; }
void Cube::printCube() const {
    auto print_face_line = [](const Face& face, int row) {
        for (int j = 0; j < 3; j++) {
            Color c = face.g[row][j];
            std::cout << COLOR_TO_ANSI.at(c) << COLOR_TO_CHAR.at(c) << ANSI_RESET << " ";
        }
    };
    std::cout << "\n           Up Face (W):\n";
    for (int i = 0; i < 3; i++) { std::cout << "           "; print_face_line(U, i); std::cout << "\n"; }
    std::cout << "\nLeft(O)    Front(G)   Right(R)   Back(B)\n";
    for (int i = 0; i < 3; i++) { print_face_line(L, i); std::cout << "  "; print_face_line(F, i); std::cout << "  "; print_face_line(R, i); std::cout << "  "; print_face_line(B, i); std::cout << "\n"; }
    std::cout << "\n           Down Face (Y):\n";
    for (int i = 0; i < 3; i++) { std::cout << "           "; print_face_line(D, i); std::cout << "\n"; }
    std::cout << "-------------------------------------------\n";
}
void Cube::rotCW(Face &f) { Face tmp = f; for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) f.g[j][2 - i] = tmp.g[i][j]; }
void Cube::move_U() { rotCW(U); std::array<Color,3> t=F.g[0]; F.g[0]=R.g[0]; R.g[0]=B.g[0]; B.g[0]=L.g[0]; L.g[0]=t; }
void Cube::move_D() { rotCW(D); std::array<Color,3> t=F.g[2]; F.g[2]=L.g[2]; L.g[2]=B.g[2]; B.g[2]=R.g[2]; R.g[2]=t; }
void Cube::move_F() { rotCW(F); std::array<Color,3> t=U.g[2]; for(int i=0;i<3;i++) U.g[2][i]=L.g[2-i][2]; for(int i=0;i<3;i++) L.g[i][2]=D.g[0][i]; for(int i=0;i<3;i++) D.g[0][i]=R.g[2-i][0]; for(int i=0;i<3;i++) R.g[i][0]=t[i]; }
void Cube::move_B() { rotCW(B); std::array<Color,3> t=U.g[0]; for(int i=0;i<3;i++) U.g[0][i]=R.g[i][2]; for(int i=0;i<3;i++) R.g[i][2]=D.g[2][2-i]; for(int i=0;i<3;i++) D.g[2][i]=L.g[i][0]; for(int i=0;i<3;i++) L.g[i][0]=t[2-i]; }
void Cube::move_L() { rotCW(L); std::array<Color,3> t; for(int i=0;i<3;i++) t[i]=U.g[i][0]; for(int i=0;i<3;i++) U.g[i][0]=B.g[2-i][2]; for(int i=0;i<3;i++) B.g[i][2]=D.g[2-i][0]; for(int i=0;i<3;i++) D.g[i][0]=F.g[i][0]; for(int i=0;i<3;i++) F.g[i][0]=t[i]; }
void Cube::move_R() { rotCW(R); std::array<Color,3> t; for(int i=0;i<3;i++) t[i]=U.g[i][2]; for(int i=0;i<3;i++) U.g[i][2]=F.g[i][2]; for(int i=0;i<3;i++) F.g[i][2]=D.g[i][2]; for(int i=0;i<3;i++) D.g[i][2]=B.g[2-i][0]; for(int i=0;i<3;i++) B.g[i][0]=t[2-i]; }
void Cube::applyMoveToken(const std::string &tok) {
    if (tok == "U") move_U(); else if (tok == "U'") { move_U(); move_U(); move_U(); } else if (tok == "U2") { move_U(); move_U(); }
    else if (tok == "D") move_D(); else if (tok == "D'") { move_D(); move_D(); move_D(); } else if (tok == "D2") { move_D(); move_D(); }
    else if (tok == "F") move_F(); else if (tok == "F'") { move_F(); move_F(); move_F(); } else if (tok == "F2") { move_F(); move_F(); }
    else if (tok == "B") move_B(); else if (tok == "B'") { move_B(); move_B(); move_B(); } else if (tok == "B2") { move_B(); move_B(); }
    else if (tok == "L") move_L(); else if (tok == "L'") { move_L(); move_L(); move_L(); } else if (tok == "L2") { move_L(); move_L(); }
    else if (tok == "R") move_R(); else if (tok == "R'") { move_R(); move_R(); move_R(); } else if (tok == "R2") { move_R(); move_R(); }
}
void Cube::applySequence(const std::string &seq) { std::stringstream ss(seq); std::string tok; while(ss >> tok) applyMoveToken(tok); }
std::string Cube::toKociembaFaceletString() const { std::string s; auto aF=[&](const Face&f){for(int i=0;i<3;i++)for(int j=0;j<3;j++)s.push_back(colorToFacelet(f.g[i][j]));}; aF(U);aF(R);aF(F);aF(D);aF(L);aF(B); return s;}
bool Cube::isSolved() const { auto sF = [](const Face &f){Color c=f.g[0][0];for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(f.g[i][j]!=c)return false;return true;}; return sF(U)&&sF(D)&&sF(F)&&sF(B)&&sF(L)&&sF(R); }

// The restored, working Python solver call
std::string Cube::callKociembaSolver() const {
    std::string python_path = "E:\\Rubik_cube\\.venv\\Scripts\\python.exe"; 
    std::string script_path = "kociemba_helper.py";
    std::string command = python_path + " \"" + script_path + "\" " + toKociembaFaceletString();
    std::string result = "";
    std::array<char, 256> buffer;
    #ifdef _WIN32
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
    #else
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    #endif
    if (!pipe) { std::cerr << "Could not open pipe.\n"; return ""; }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { result += buffer.data(); }
    return result;
}