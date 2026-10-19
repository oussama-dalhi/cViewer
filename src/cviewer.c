#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTAION
#include <stb_image.h>

int main(void)
{
    int sdl_init_result = SDL_Init(SDL_INIT_VIDEO);
    if (sdl_init_result != 0)
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

    SDL_Renderer *windowrenderer = SDL_CreateRenderer(window, -1, 0);
    if(windowrenderer == NULL)
    {
        printf("%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

   bool app_running = true;
   while (app_running) 
   {
       SDL_Event event;
       while (SDL_PollEvent(&event)) 
       {  
           if(event.type == SDL_QUIT)
           {
               app_running = false;
           }
       }
       Uint8 red = 30;
       Uint8 green = 30;
       Uint8 blue = 30;
       Uint8 alpha = SDL_ALPHA_OPAQUE;
       int color_result = SDL_SetRenderDrawColor(windowrenderer, red, green, blue, alpha);
       if (color_result != 0)
       {
            printf("%s\n", SDL_GetError());
            SDL_DestroyRenderer(windowrenderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return -1;
       }
       int clear_result = SDL_RenderClear(windowrenderer);
       if (clear_result != 0)
       {
            printf("%s\n", SDL_GetError());
            SDL_DestroyRenderer(windowrenderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return -1;
       }
       SDL_RenderPresent(windowrenderer);
   }
            
    SDL_DestroyRenderer(windowrenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
