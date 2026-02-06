## Reaction-Diffusion visualization implemented in Cpp + Raylib

# Examples:
Coral:

![Animation1](https://github.com/user-attachments/assets/16c8aa17-280c-4eab-8d94-109bcfb19ef0)

Mitosis

![Animation2](https://github.com/user-attachments/assets/1d41f990-a77d-42f5-ae3b-89904cb61423)

Moving spots:

![Animation3](https://github.com/user-attachments/assets/54a4bb10-755e-4c2f-b7c5-992ec55dce75)

Custom drawing:

![Animation4](https://github.com/user-attachments/assets/a6fd26a1-888e-4340-adb8-25772fa957f4)

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
