# 3dcube Simulator

A simple implementation of rotation matricies and projections algorithms for cube in C using SDL2 for graphics rendering.

**Check [releases](https://github.com/47seconds/3DcubeSimulator/releases) page to download pre-compiled binaries and run the program.**

## Table of Contents
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [License](#license)

---

## Requirements

Before you can run the program, make sure you have the following installed:

1. **C Compiler**: Any C99-compatible compiler (e.g., GCC or Clang).
2. **SDL2 Library**: Install the SDL2 library to enable graphical rendering.

### Installing SDL2

#### On Linux
```bash
sudo apt-get install libsdl2-dev
```

#### On macOS
```bash
brew install sdl2
```

#### On Windows
Download and install SDL2 (version 2) from the [official website](https://github.com/libsdl-org/SDL/releases/).

---

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/47seconds/3DcubeSimulator.git
   cd 3DcubeSimulator
   ```

2. Compile the program:
   ```bash
   gcc -o main main.c -lm `sdl2-config --cflags --libs`
   ```
   Replace `main.c` with the actual name of the source file if it differs.

---

## Usage

Run the program with the following command:

1. If compiled:
```bash
./main
```

2. If downloaded binaries:
```bash
./3Dcube.bin (Linux)
./3Dcube.exe (Windows)
```
---

## How It Works

3Dcube Simulator works on principle of rotation matrix and 3D projection principles:

1. **Matrix**: Holds the coordinates of all 12 sides of cube.
2. **Rotation Matrix**: Rotate the cube by alpha, beta and gamma angles around different axes.
3. **3D projection**: Project the 3D cube into 2D.

The program displays the cube and updates it in real-time according to this algorithm.

---

## License

This project is licensed under the [MIT License](LICENSE).

Feel free to use, modify, and distribute the code as you see fit.