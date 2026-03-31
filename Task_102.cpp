#include <SDL3/SDL.h>
#include <cmath>

// Function to draw FILLED circle
void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int r) {
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            if (x * x + y * y <= r * r) {
                SDL_RenderPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

int main(int argc, char* argv[]) {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL Init Failed: %s", SDL_GetError());
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Task 102 - Growing Red Circle",
        800,
        600,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        SDL_Log("Window Failed: %s", SDL_GetError());
        return -1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer) {
        SDL_Log("Renderer Failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return -1;
    }

    bool running = true;
    SDL_Event event;

    int centerX = 800 / 2;
    int centerY = 600 / 2;

    int radius = 10; // starting radius

    // Main loop
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        // Clear screen (black)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set RED color
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Draw filled circle
        drawFilledCircle(renderer, centerX, centerY, radius);

        // Increase radius
        radius++;

        // Reset when hitting window boundary
        if (centerX + radius >= 800 || centerY + radius >= 600) {
            radius = 10;
        }

        // Show on screen
        SDL_RenderPresent(renderer);

        // Delay for smooth animation
        SDL_Delay(20);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}