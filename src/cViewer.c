#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main(int argc, char *argv[])
{
    int exit_status = EXIT_SUCCESS;
    unsigned char *pixels = NULL;
    SDL_Surface *surface = NULL;
    SDL_Window *window = NULL;
    SDL_Renderer *windowrenderer = NULL;
    SDL_Texture *texture = NULL;
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./cViewer <imagepath>\n");
        return EXIT_FAILURE;
    }
    int width, height;
    pixels = stbi_load(argv[1], &width, &height, NULL, 4);
    if(pixels == NULL)
    {
        fprintf(stderr, "%s\n", stbi_failure_reason());
        return EXIT_FAILURE;
    }
    int sdl_init_result = SDL_Init(SDL_INIT_VIDEO);
    if (sdl_init_result != 0)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit_status = EXIT_FAILURE;
        goto cleanup;
    }
    int depth = 32;
    int pitch = width * 4;
    surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, 
            width, height, depth, pitch, SDL_PIXELFORMAT_RGBA32);
    if(surface == NULL)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit_status = EXIT_FAILURE;
        goto cleanup;
    }

    window = SDL_CreateWindow("cViewer", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit_status = EXIT_FAILURE;
        goto cleanup;
    }

    windowrenderer = SDL_CreateRenderer(window, -1, 0);
    if(windowrenderer == NULL)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit_status = EXIT_FAILURE;
        goto cleanup;
    }

    texture =  SDL_CreateTextureFromSurface(windowrenderer, 
            surface);
    if(texture == NULL)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit_status = EXIT_FAILURE;
        goto cleanup;
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    stbi_image_free(pixels);
    pixels = NULL;

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
        if (!app_running)
        {
            break;
        }
        Uint8 red = 30;
        Uint8 green = 30;
        Uint8 blue = 30;
        Uint8 alpha = SDL_ALPHA_OPAQUE;
        int color_result = SDL_SetRenderDrawColor(windowrenderer, red, green, blue, alpha);
        if (color_result != 0)
        {
            fprintf(stderr, "%s\n", SDL_GetError());
            exit_status = EXIT_FAILURE;
            break;
        }
        int clear_result = SDL_RenderClear(windowrenderer);
        if (clear_result != 0)
        {
            fprintf(stderr, "%s\n", SDL_GetError());
            exit_status = EXIT_FAILURE;
            break;
        }
        int w;
        int h;

        int size_result = SDL_GetRendererOutputSize(windowrenderer, &w, &h);
        if (size_result != 0)
        {
            fprintf(stderr, "%s\n", SDL_GetError());
            exit_status = EXIT_FAILURE;
            break;
        } 

        double scale_factor = fmin((double)w / width, (double)h / height);
        SDL_Rect dest;
        dest.w = (int)(scale_factor * width);
        dest.h = (int)(scale_factor * height);
        dest.x = (w - dest.w) / 2;
        dest.y = (h - dest.h) / 2;


        int render_cp = SDL_RenderCopy(windowrenderer, texture, NULL, &dest);
        if(render_cp != 0)
        {
            fprintf(stderr, "%s\n", SDL_GetError());
            exit_status = EXIT_FAILURE;
            break;
        }

        SDL_RenderPresent(windowrenderer);
    }
    
cleanup:
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
    }
    if(windowrenderer != NULL)
    {
        SDL_DestroyRenderer(windowrenderer);
    }
    if(window != NULL)
    {
        SDL_DestroyWindow(window);
    }
    if(surface != NULL)
    {
        SDL_FreeSurface(surface);
    }
    if(pixels != NULL)
    {
        stbi_image_free(pixels);
    }
    SDL_Quit();
    return exit_status;
}
