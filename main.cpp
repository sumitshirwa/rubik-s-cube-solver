#include <bits/stdc++.h>
#include "Model/RubiksCube.h"
#include "Model/RubiksCube3dArray.h"
#include "Model/RubiksCube1dArray.h"
#include "Model/RubiksCubeBitboard.h"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"
#include "Solver/IDAstarSolver.h"
#include "PatternDatabases/CornerPatternDatabase.h"
#include "PatternDatabases/CornerDBMaker.h"

using namespace std;

void printMenu() {
    cout << "\n========================================\n";
    cout << "       RUBIK'S CUBE SOLVER\n";
    cout << "========================================\n";
    cout << "1. Show Current Cube State\n";
    cout << "2. Shuffle Cube\n";
    cout << "3. Apply Single Move\n";
    cout << "4. Check if Solved\n";
    cout << "5. Reset to Solved State\n";
    cout << "6. Exit\n";
    cout << "========================================\n";
    cout << "Select option (1-6): ";
}

void printMoveMenu() {
    cout << "\nAvailable Moves:\n";
    cout << "U/u - Up   D/d - Down   L/l - Left\n";
    cout << "R/r - Right   F/f - Front   B/b - Back\n";
    cout << "Add ' for inverse (e.g., u')  Add 2 for double (e.g., u2)\n";
    cout << "Examples: u, d', r2, f, b'\n";
}

bool applyMove(RubiksCubeBitboard& cube, string move) {
    if (move.empty()) return false;
    
    // Convert to lowercase
    move[0] = tolower(move[0]);
    
    // Check for prime (') or 2
    bool isPrime = move.find('\'') != string::npos;
    bool isDouble = move.find('2') != string::npos;
    
    // Apply moves
    switch(move[0]) {
        case 'u': cube.u(); if (isPrime) { cube.u(); cube.u(); } else if (isDouble) { cube.u(); } return true;
        case 'd': cube.d(); if (isPrime) { cube.d(); cube.d(); } else if (isDouble) { cube.d(); } return true;
        case 'l': cube.l(); if (isPrime) { cube.l(); cube.l(); } else if (isDouble) { cube.l(); } return true;
        case 'r': cube.r(); if (isPrime) { cube.r(); cube.r(); } else if (isDouble) { cube.r(); } return true;
        case 'f': cube.f(); if (isPrime) { cube.f(); cube.f(); } else if (isDouble) { cube.f(); } return true;
        case 'b': cube.b(); if (isPrime) { cube.b(); cube.b(); } else if (isDouble) { cube.b(); } return true;
        default: return false;
    }
}

int main() {
    RubiksCubeBitboard cube;
    int choice;
    string move_input;
    int shuffle_depth;
    
    cout << "\n========================================\n";
    cout << "   RUBIK'S CUBE SOLVER - INTERACTIVE   \n";
    cout << "        (Using Bitboard Model)       \n";
    cout << "========================================\n";

    // Display initial cube state
    cout << "\n--- Initial Cube State ---\n";
    cube.print();
    if (cube.isSolved()) {
        cout << "Status: SOLVED\n";
    } else {
        cout << "Status: NOT SOLVED\n";
    }

    while (true) {
        printMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: {
                cout << "\n--- Current Cube State ---\n";
                cube.print();
                if (cube.isSolved()) {
                    cout << "Status: SOLVED\n";
                } else {
                    cout << "Status: NOT SOLVED\n";
                }
                break;
            }
            
            case 2: {
                cout << "Enter shuffle depth (1-20): ";
                cin >> shuffle_depth;
                cin.ignore();
                
                if (shuffle_depth < 1 || shuffle_depth > 20) {
                    cout << "Invalid depth! Using 5.\n";
                    shuffle_depth = 5;
                }
                
                vector<RubiksCube::MOVE> moves = cube.randomShuffleCube(shuffle_depth);
                cout << "\nShuffle applied with moves: ";
                for (auto move : moves) {
                    cout << cube.getMove(move) << " ";
                }
                cout << "\n\n";
                cube.print();
                cout << "Status: NOT SOLVED\n";
                break;
            }
            
            case 3: {
                printMoveMenu();
                cout << "Enter move: ";
                getline(cin, move_input);
                
                if (applyMove(cube, move_input)) {
                    cout << "\nMove '" << move_input << "' applied!\n\n";
                    cube.print();
                    cout << "Status: " << (cube.isSolved() ? "SOLVED" : "NOT SOLVED") << "\n";
                } else if (!move_input.empty()) {
                    cout << "Invalid move: " << move_input << "\n";
                    cout << "Valid moves: u, d, l, r, f, b (with ' for prime, 2 for double)\n";
                } else {
                    cout << "No move entered.\n";
                }
                break;
            }
            
            case 4: {
                cout << "\nChecking cube state...\n";
                if (cube.isSolved()) {
                    cout << "*** CUBE IS SOLVED! ***\n";
                } else {
                    cout << "Cube is NOT solved. Keep trying!\n";
                }
                break;
            }
            
            case 5: {
                cube = RubiksCubeBitboard(); // Create fresh solved cube
                cout << "\nCube reset to solved state.\n";
                cube.print();
                cout << "Status: SOLVED\n";
                break;
            }
            
            case 6: {
                cout << "\nThanks for using Rubik's Cube Solver!\n";
                cout << "Goodbye!\n";
                return 0;
            }
            
            default: {
                cout << "Invalid choice! Please enter 1-6.\n";
            }
        }
    }
}