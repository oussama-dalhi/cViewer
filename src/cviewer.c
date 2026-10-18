#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int main(void)
{
    int sdlinit = SDL_Init(SDL_INIT_VIDEO);
    if (sdlinit != 0)
    {
        printf("%s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("cViewer", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        printf("%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *windowrender = SDL_CreateRenderer(window, -1, 0);
    if(windowrender == NULL)
    {
        printf("%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

   bool app_running = true;
   while (app_running) {
       SDL_Event event;
           while (SDL_PollEvent(&event)) 
                {  
                    if(event.type == SDL_QUIT)
                    {
                        app_running = false;
                    }
                    // decide what to do with this event.
                }
                           // update game state, draw the current frame
            }
            
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(windowrender);
    SDL_Quit();
    return 0;
}
