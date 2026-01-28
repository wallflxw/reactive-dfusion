// g++ .\main.cpp -I..\LIBS\raylib-5.5\include\ -L..\LIBS\raylib-5.5\lib\ -I..\LIBS\ -lraylib -lwinmm -lgdi32 -Wall -Wextra -O3 -o main
// Source: https://www.karlsims.com/rd.html | https://en.wikipedia.org/wiki/Reaction–diffusion_system
#include <raylib.h>
#include <array>
#include <xmmintrin.h>
using std::array;

#define WIDTH 1000
#define HEIGTH 1000
#define N 200
#define PIXEL_SIZE WIDTH / N

#define ADJACENT_WEIGHT 0.2f  // left, rigth, up, down nbors weight
#define DIAGONAL_WEIGHT 0.05f // diagonal nbors weight
#define DIFFUSION_A 1.0f
#define DIFFUSION_B 0.5f


struct Cell {
    float A = {};
    float B = {};
};
using Grid = array<array<Cell, N>, N>;

void draw_grid_to_image(const Grid& grid, const Image& image, Texture2D texture);
void update_grid(Grid* curr_grid_p, Grid* next_grid_p, float feed, float kill);
void init_grid(Grid* curr_grid_p);
void add_B_to_grid(Grid* curr_grid_p) ;

int main() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    InitWindow(WIDTH, HEIGTH, "Hello, you");
    SetTargetFPS(60);
    bool pause = true;
    float feed = 0.0545f;
    float kill = 0.062f;
    Grid* curr_grid_p = new Grid();
    Grid* next_grid_p = new Grid();
    init_grid(curr_grid_p);

    Image image = GenImageColor(N, N, BLACK);
    Texture2D texture = LoadTextureFromImage(image);
    SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);

    draw_grid_to_image((*curr_grid_p), image, texture);
    while(!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { add_B_to_grid(curr_grid_p); draw_grid_to_image((*curr_grid_p), image, texture); }
        if (IsKeyPressed(KEY_SPACE)) { pause = !pause; }
        if (IsKeyPressed(KEY_ONE))   { feed = 0.0367; kill = 0.0649; } // Mitosis
        if (IsKeyPressed(KEY_TWO))   { feed = 0.0545; kill = 0.0620; } // Coral/Maze
        if (IsKeyPressed(KEY_THREE)) { feed = 0.0370; kill = 0.0600; } // Fingerprints
        if (IsKeyPressed(KEY_FOUR))  { feed = 0.0140; kill = 0.0540; } // Moving Spots
        if (IsKeyPressed(KEY_FIVE))  { feed = 0.0580; kill = 0.0650; } // Worms
        if (IsKeyPressed(KEY_SIX))   { feed = 0.0250; kill = 0.0560; } // Pulsating

        if (!pause) {
            for (int i = 0; i < 10; i++) {
                update_grid(curr_grid_p, next_grid_p, feed, kill);
                std::swap(curr_grid_p, next_grid_p);
            }
            draw_grid_to_image((*curr_grid_p), image, texture);
        }


        BeginDrawing();
            ClearBackground({0x26, 0x26, 0x26, 0xFF});
            DrawTexturePro(
                texture,
                (Rectangle){0, 0, N, N},
                (Rectangle){0, 0, WIDTH, HEIGTH},
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
            // DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}


void draw_grid_to_image(const Grid& grid, const Image& image, Texture2D texture) {
    Color* pixels = (Color*)image.data;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            // auto A = grid[i][j].A;
            auto B = grid[i][j].B;

            float hue = 60.0f + (B * 80.0f);
            float saturation = 1.0f;
            float value = B * 2.0f;

            pixels[j * N + i] = ColorFromHSV(hue, saturation, value);    

        }
    }
    UpdateTexture(texture, image.data);
}

void update_grid(Grid* curr_grid_p, Grid* next_grid_p, float feed, float kill) {
    float dt = 1.0f;
    Grid& curr_grid = *curr_grid_p;
    Grid& next_grid = *next_grid_p;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            size_t left  = (i - 1 + N) % N;
            size_t right = (i + 1) % N;
            size_t up    = (j - 1 + N) % N;
            size_t down  = (j + 1) % N;
            float lapA = (curr_grid[i][j].A * -1.0f) +
                (curr_grid[left][j].A * ADJACENT_WEIGHT) + (curr_grid[right][j].A * ADJACENT_WEIGHT) +
                (curr_grid[i][up].A * ADJACENT_WEIGHT) + (curr_grid[i][down].A * ADJACENT_WEIGHT) +
                (curr_grid[left][up].A * DIAGONAL_WEIGHT) + (curr_grid[right][up].A * DIAGONAL_WEIGHT) +
                (curr_grid[left][down].A * DIAGONAL_WEIGHT) + (curr_grid[right][down].A * DIAGONAL_WEIGHT);
            float lapB = (curr_grid[i][j].B * -1.0f) +
                (curr_grid[left][j].B * ADJACENT_WEIGHT) + (curr_grid[right][j].B * ADJACENT_WEIGHT) +
                (curr_grid[i][up].B * ADJACENT_WEIGHT) + (curr_grid[i][down].B * ADJACENT_WEIGHT) +
                (curr_grid[left][up].B * DIAGONAL_WEIGHT) + (curr_grid[right][up].B * DIAGONAL_WEIGHT) +
                (curr_grid[left][down].B * DIAGONAL_WEIGHT) + (curr_grid[right][down].B * DIAGONAL_WEIGHT);
            
            float a_old = curr_grid[i][j].A;
            float b_old = curr_grid[i][j].B;
            next_grid[i][j].A = a_old + (DIFFUSION_A * lapA - a_old * b_old * b_old + feed * (1.0f - a_old)) * dt;
            next_grid[i][j].B = b_old + (DIFFUSION_B * lapB + a_old * b_old * b_old - (kill + feed) * b_old) * dt;
            if (next_grid[i][j].A < 0) next_grid[i][j].A = 0;
            if (next_grid[i][j].A > 1) next_grid[i][j].A = 1;
            if (next_grid[i][j].B < 0) next_grid[i][j].B = 0;
            if (next_grid[i][j].B > 1) next_grid[i][j].B = 1;
        }
    }
}

void init_grid(Grid* curr_grid_p) {
    for (auto& row: (*curr_grid_p)) {
        row.fill({.A = 1.0f});
    }
    for (int i = 90; i < 100; i++) {
        for (int j = 90; j < 100; j++) {
            (*curr_grid_p)[i][j].B = 1.0f;
        }
    }
}

void add_B_to_grid(Grid* curr_grid_p) {
    Vector2 mouse = GetMousePosition();
    size_t mouse_x = (int)mouse.x / (PIXEL_SIZE);
    size_t mouse_y = (int)mouse.y / (PIXEL_SIZE);
    (*curr_grid_p)[mouse_x][mouse_y].B = 1.0f;
}