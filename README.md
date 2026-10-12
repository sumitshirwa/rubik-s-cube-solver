# Rubik's Cube Solver

A C++ implementation of a 3x3 Rubik's Cube solver using multiple AI search algorithms with an interactive menu-driven interface.

## Features

### Interactive Menu Interface
- **View Cube State** - Display the current cube configuration with all 6 faces
- **Shuffle** - Randomize the cube with selectable depth (1-20 moves)
- **Check Status** - Verify if the cube is solved
- **Reset** - Return to solved state instantly
- **Real-time Feedback** - See Corner Pattern Database depth (estimated moves to solve)

### Cube Representations
- **3D Array** — intuitive face[row][col] model
- **1D Array** — flattened for cache efficiency  
- **Bitboard** — compact bit-packed for fastest hashing and searching

### Search Algorithms
| Algorithm | Type       | Optimal? | Notes                                |
|-----------|------------|----------|--------------------------------------|
| DFS       | Uninformed | No       | Depth-limited search                 |
| BFS       | Uninformed | Yes      | Memory-heavy but guarantees optimality|
| IDDFS     | Uninformed | Yes      | DFS + BFS tradeoff, best efficiency  |
| IDA*      | Informed   | Yes      | Uses Corner Pattern DB heuristic     |

### Corner Pattern Database
- Pre-computes minimum moves for all 88,179,840 corner permutations
- Stored as nibble array (4 bits/entry) → ~42MB on disk
- Used as admissible heuristic for IDA* search
- Provides immediate feedback on solution depth from any cube state

## Build Instructions

### Prerequisites
- C++ compiler (g++ recommended)
- C++14 or higher

### Compilation
```bash
cd rubiks-cube-solver-main
g++ -std=c++14 -I. -o rubiks_cube_solver main.cpp Model/RubiksCube.cpp \
  PatternDatabases/NibbleArray.cpp PatternDatabases/PatternDatabase.cpp \
  PatternDatabases/CornerPatternDatabase.cpp PatternDatabases/CornerDBMaker.cpp \
  PatternDatabases/math.cpp
```

## Usage

### Running the Program
```bash
./rubiks_cube_solver.exe
```

Or on Windows:
```powershell
.\rubiks_cube_solver.exe
```

### Interactive Menu Options

Upon starting, the program displays the initial cube state and presents 6 menu options:

**1. Show Current Cube State**
- Displays all 6 faces of the cube
- Shows whether cube is SOLVED (✓) or NOT SOLVED (✗)
- Displays Corner DB depth (minimum estimated moves to solution)

**2. Shuffle Cube**
- Enter depth (1-20) for number of random moves
- View the scrambled cube configuration
- See updated Corner DB depth based on current state

**3. Apply Single Move** *(extensible feature)*
- Test individual moves on the cube
- View cube after move application
- Check updated solution depth

**4. Check if Solved**
- Quick verification of current cube state

**5. Reset to Solved State**
- Instantly return to initial solved configuration

**6. Exit**
- Quit the program gracefully

### Example Session
```
╔════════════════════════════════════════╗
║   RUBIK'S CUBE SOLVER - INTERACTIVE   ║
║          (Using Bitboard Model)       ║
╚════════════════════════════════════════╝

--- Initial Cube State ---

       W W W 
       W W W 
       W W W 

G G G  R R R  B B B  O O O 
G G G  R R R  B B B  O O O 
G G G  R R R  B B B  O O O 

       Y Y Y 
       Y Y Y 
       Y Y Y 

Status: ✓ SOLVED
Moves to solve (Corner DB): 0
```

## Project Structure
```
rubiks-cube-solver-main/
├── main.cpp                              # Interactive menu interface
├── Model/
│   ├── RubiksCube.h                     # Base class definition
│   ├── RubiksCube.cpp                   # Core implementation
│   ├── RubiksCube3dArray.h/cpp          # 3D array representation
│   ├── RubiksCube1dArray.h/cpp          # 1D array representation
│   └── RubiksCubeBitboard.h/cpp         # Bitboard representation
├── Solver/
│   ├── DFSSolver.h                      # Depth-first search solver
│   ├── BFSSolver.h                      # Breadth-first search solver
│   ├── IDDFSSolver.h                    # Iterative deepening DFS
│   └── IDAstarSolver.h                  # IDA* with heuristic
├── PatternDatabases/
│   ├── CornerPatternDatabase.h/cpp      # Corner DB interface & impl
│   ├── CornerDBMaker.h/cpp              # Database builder tool
│   ├── NibbleArray.h/cpp                # 4-bit per entry storage
│   ├── PatternDatabase.h/cpp            # Generic pattern database
│   ├── PermutationIndexer.h             # Permutation encoding
│   └── math.h/cpp                       # Mathematical utilities
├── Databases/
│   └── cornerDepth5V1.txt               # Pre-built corner database
├── README.md                             # This file
└── CMakeLists.txt                       # CMake build configuration
```

## How It Works

### Cube State Representation
- Each cube state is encoded efficiently using a **bitboard** (6 × 64-bit integers)
- Colors and piece positions are bit-packed for minimal memory footprint
- Enables fast state hashing and comparison during search

### Corner Pattern Database
The Corner Pattern Database computes the minimum number of moves needed from any corner permutation to the solved state:

- **Admissible Heuristic** - Never overestimates the actual cost to solution
- **Fast Lookup** - O(1) constant-time retrieval of heuristic values
- **Memory Efficient** - Uses only 4 bits per cube state (nibble array)
- **Database Size** - ~42MB for complete corner permutations (88,179,840 states)

### IDA* Search Algorithm
The IDA* (Iterative Deepening A*) algorithm uses the Corner Pattern Database heuristic for optimal solving.

## Color Legend
- **W** - White
- **Y** - Yellow
- **R** - Red
- **O** - Orange
- **G** - Green
- **B** - Blue

## Performance
- **Memory Usage**: ~42MB for Corner Pattern Database
- **State Space**: 43,252,003,274,489,856,000 possible configurations
- **Search Optimality**: Guaranteed with IDA* algorithm

## Future Enhancements
- [ ] Move parser for manual input (U, R', D2, etc.)
- [ ] Automated solver using IDA*
- [ ] 3D visualization interface
- [ ] Web-based GUI
- [ ] Performance benchmarking tools

## License
Open source - use freely for educational purposes

## References
- Rubik's Cube theory and group theory
- Pattern database heuristics for admissible search
- Bitboard representations for game state compression