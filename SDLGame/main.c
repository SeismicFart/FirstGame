#include <stdio.h>
#include <SDL2/SDL.h>

int processEvents(SDL_Window* window) {

    int done = 0;
    SDL_Event event;


    // Check for event
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_WINDOWEVENT_CLOSE: {
                if(window) {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
            break;
            case SDL_KEYDOWN: {
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE: done = 1;
                    break;
                }
            }
            break;
            case SDL_QUIT: done = 1;
            break;
        }
    }
    return done;
}

void doRender(SDL_Renderer* renderer) {
    // Render display
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
     
    // clear screen to blue
    SDL_RenderClear(renderer);
     
    // set drawing colour to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
     
    SDL_Rect rect = {350, 250, 100, 100};
    SDL_RenderFillRect(renderer, &rect);
     
    // done drawing, now presenting
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {                                           // Initialize SDL2
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game Window",                           // window title
                                          SDL_WINDOWPOS_UNDEFINED,                 // window x position
                                          SDL_WINDOWPOS_UNDEFINED,                 // window y position
                                          800,                                     // width, in pixels
                                          600,                                     // height, in pixels
                                          SDL_WINDOW_SHOWN                         // flags
                                          );
    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Event loop
    int done = 0;

    while(!done) {
        // check for events
        done = processEvents(window);

        // render display
        doRender(renderer);

        // limit fps
        SDL_Delay(100); 
    }

    // close and destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
    
}
