#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>

// =============================
// Tile Definition
// =============================
struct Tile {
    Uint8 r, g, b;
    SDL_Texture* texture = nullptr; // for later
};

// =============================
// TileMap
// =============================
class TileMap {
public:
    TileMap(int w, int h)
        : width(w), height(h),
          grid(w, std::vector<int>(h, 0)) {}

    int width;
    int height;
    std::vector<std::vector<int>> grid;
};

// =============================
// Main
// =============================
int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    const int gridWidth = 25;
    const int gridHeight = 25;
    const int tileSize = 32;

    const int windowWidth = gridWidth * tileSize;
    const int windowHeight = gridHeight * tileSize;

    SDL_Window* window = SDL_CreateWindow(
        "Tile Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    // =============================
    // Create Tiles (Tile Definitions)
    // =============================
    std::vector<Tile> tiles = {
        { 50, 200, 50 },   // 0 - grass
        { 50, 50, 200 },   // 1 - water
        { 150, 100, 50 },  // 2 - dirt
        { 120, 120, 120 }  // 3 - stone
    };
    tiles[0].texture = IMG_LoadTexture(renderer, "./display/grass.png");
                

    // =============================
    // Create TileMap
    // =============================
    TileMap map(gridWidth, gridHeight);

    bool quit = false;
    SDL_Event event;

    int selectedTile = 1; // change this to paint different tiles

    while (!quit) {

        // =============================
        // INPUT
        // =============================
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = true;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                int cellX = mouseX / tileSize;
                int cellY = mouseY / tileSize;

                if (cellX >= 0 && cellX < map.width &&
                    cellY >= 0 && cellY < map.height) {

                    map.grid[cellX][cellY] = selectedTile;
                }
            }

            // Number keys to switch tile
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_1) selectedTile = 0;
                if (event.key.keysym.sym == SDLK_2) selectedTile = 1;
                if (event.key.keysym.sym == SDLK_3) selectedTile = 2;
                if (event.key.keysym.sym == SDLK_4) selectedTile = 3;
            }
        }

        // =============================
        // RENDER
        // =============================
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int x = 0; x < map.width; x++) {
            for (int y = 0; y < map.height; y++) {

                int tileID = map.grid[x][y];
                Tile& tile = tiles[tileID];

                SDL_Rect dst = {
                    x * tileSize,
                    y * tileSize,
                    tileSize,
                    tileSize
                };

                if (tile.texture) {
                    // Future textured rendering
                    SDL_RenderCopy(renderer, tile.texture, nullptr, &dst);
                } else {
                    // Solid color rendering
                    SDL_SetRenderDrawColor(renderer, tile.r, tile.g, tile.b, 255);
                    SDL_RenderFillRect(renderer, &dst);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}