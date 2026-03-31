#include <SDL3/SDL.h>
#include <cmath>

// Draw filled circle
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
        "Task 103 - Collision",
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

    // Circle 1 (auto moving)
    int x1 = 0;
    int y1 = 300;
    int r1 = 40;

    // Circle 2 (user controlled)
    int x2 = 400;
    int y2 = 100;
    int r2 = 40;

    while (running) {

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        // ✅ SDL3 keyboard input (FIXED)
        const bool* keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_UP]) y2 -= 5;
        if (keys[SDL_SCANCODE_DOWN]) y2 += 5;
        if (keys[SDL_SCANCODE_LEFT]) x2 -= 5;
        if (keys[SDL_SCANCODE_RIGHT]) x2 += 5;

        // Move first circle automatically
        x1 += 3;
        if (x1 > 800) x1 = 0;

        // Collision detection
        float dist = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
        bool collision = (dist <= r1 + r2);

        // Clear screen (black)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Change color on collision
        if (collision) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // RED
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // GREEN
        }

        // Draw circles
        drawFilledCircle(renderer, x1, y1, r1);
        drawFilledCircle(renderer, x2, y2, r2);

        // Show on screen
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // smooth animation
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}