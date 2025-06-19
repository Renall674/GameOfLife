#include <SDL.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int GRID_SIZE = 20;
int DELAY_MS = 100;
bool isRunning = true;
bool isPaused = true;

std::vector<std::vector<bool>> grid;
std::vector<std::vector<bool>> nextGrid;
int GRID_COLS;
int GRID_ROWS;

void parseArguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--width" && i + 1 < argc) {
            SCREEN_WIDTH = std::max(100, std::atoi(argv[++i]));
        }
        else if (arg == "--height" && i + 1 < argc) {
            SCREEN_HEIGHT = std::max(100, std::atoi(argv[++i]));
        }
        else if (arg == "--grid" && i + 1 < argc) {
            GRID_SIZE = std::max(5, std::atoi(argv[++i]));
        }
        else if (arg == "--speed" && i + 1 < argc) {
            DELAY_MS = std::max(10, std::atoi(argv[++i]));
        }
        else if (arg == "--help") {
            std::cout << "Usage:\n"
                << "  --width  [pixels]  Window width\n"
                << "  --height [pixels]  Window height\n"
                << "  --grid   [size]    Cell size\n"
                << "  --speed  [ms]      Simulation speed\n";
            exit(0);
        }
    }
}

void initGrid() {
    GRID_COLS = SCREEN_WIDTH / GRID_SIZE;
    GRID_ROWS = SCREEN_HEIGHT / GRID_SIZE;
    grid.resize(GRID_ROWS, std::vector<bool>(GRID_COLS, false));
    nextGrid = grid;
}

void clearGrid() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), false);
    }
}

void randomizeGrid() {
    for (auto& row : grid) {
        for (auto& cell : row) {
            cell = rand() % 2;
        }
    }
}

int countNeighbors(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < GRID_COLS && ny >= 0 && ny < GRID_ROWS && grid[ny][nx]) {
                count++;
            }
        }
    }
    return count;
}

void updateGrid() {
    for (int y = 0; y < GRID_ROWS; ++y) {
        for (int x = 0; x < GRID_COLS; ++x) {
            int neighbors = countNeighbors(x, y);
            if (grid[y][x]) {
                nextGrid[y][x] = (neighbors == 2 || neighbors == 3);
            }
            else {
                nextGrid[y][x] = (neighbors == 3);
            }
        }
    }
    grid = nextGrid;
}

void handleMouseClick(int mouseX, int mouseY) {
    int gridX = mouseX / GRID_SIZE;
    int gridY = mouseY / GRID_SIZE;
    if (gridX >= 0 && gridX < GRID_COLS && gridY >= 0 && gridY < GRID_ROWS) {
        grid[gridY][gridX] = !grid[gridY][gridX];
    }
}

int main(int argc, char* argv[]) {
    parseArguments(argc, argv);
    initGrid();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    handleMouseClick(event.button.x, event.button.y);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_SPACE: isPaused = !isPaused; break;
                case SDLK_c: clearGrid(); break;
                case SDLK_r: randomizeGrid(); break;
                case SDLK_s: if (isPaused) updateGrid(); break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        for (int x = 0; x <= SCREEN_WIDTH; x += GRID_SIZE) {
            SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
        }
        for (int y = 0; y <= SCREEN_HEIGHT; y += GRID_SIZE) {
            SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int y = 0; y < GRID_ROWS; ++y) {
            for (int x = 0; x < GRID_COLS; ++x) {
                if (grid[y][x]) {
                    SDL_Rect rect = { x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }

        SDL_RenderPresent(renderer);

        if (!isPaused) {
            updateGrid();
            SDL_Delay(DELAY_MS);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}