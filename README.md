## Reaction-Diffusion visualization implemented in Cpp + Raylib

# Examples:
Mitosis:

<img width="200" height="200" alt="capture_1769625192" src="https://github.com/user-attachments/assets/9b435d41-42a6-4579-9321-81f0b9c32a77" />

Moving spots:

<img width="200" height="200" alt="capture_1769625662" src="https://github.com/user-attachments/assets/7a5ed098-2f06-4971-863f-1a99a0ce5f53" />


# How to use:
Use LMB to spawn a new chemical B to the grid.
Press the space bar to pause/unpause the reaction.
Use the keys 1-6 on your keyboard to select predefined constants for cool reactions:

KEY_1 -> Mitosis

KEY_2 -> Coral/Maze

KEY_3 -> Fingerprints

KEY_4 -> Moving Spots

KEY_5 -> Worms

KEY_6 -> Pulsating

# How to build
Compilation command:
``` bash
g++ .\react-diff.cpp -I..\LIBS\raylib-5.5\include\ -L..\LIBS\raylib-5.5\lib\ -lraylib -lwinmm -lgdi32 -Wall -Wextra -O3 -o react-diff
```

# Credits / Dependencies
@raysan5 - for the awesome "raylib"

# Sources
[karlsims.com/rd.html](https://www.karlsims.com/rd.html)

[wiki/Reaction-diffusion_system](https://en.wikipedia.org/wiki/Reaction%E2%80%93diffusion_system)
