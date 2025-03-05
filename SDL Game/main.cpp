#define SDL_MAIN_USE_CALLBACKS

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>



const Uint16			wWidth = 1440;
const Uint16			wHeight = 960;

Uint8       RenderColorR = 255;
Uint8       RenderColorG = 255;
Uint8       RenderColorB = 255;
Uint8       RenderOpaqueAlpha = 255;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface *ScreenSurface = nullptr;
SDL_Surface *IMG = nullptr;
SDL_Texture *texture = nullptr;
SDL_GPUGraphicsPipeline *GPUPipeline = nullptr;
SDL_FRect rect = 
    {
        0,
        0,
        wWidth,
        wHeight,
    };

//      Initializations:



void SDL_AppQuit(void* appstate, SDL_AppResult result) 
    {
        //SDL_DestroySurface(ScreenSurface);
        //ScreenSurface = NULL;
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        SDL_DestroyWindow(window);
        window = NULL;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) 
    {
        if (event->type == SDL_EVENT_QUIT) 
            {
                return SDL_APP_SUCCESS;
            }
        return SDL_APP_CONTINUE;
    }

bool LoadBackgroundImage()
    {
        bool success = true;
        IMG = SDL_LoadBMP("image.bmp");

        if (!IMG)
            {
                success = false;
            }
        else
            {
                //ScreenSurface = SDL_GetWindowSurface(window);
                texture = SDL_CreateTextureFromSurface(renderer, IMG);  
            }

        return success;
    }



void Render() 
    {
        //SDL_RenderClear(renderer);
        //SDL_SetRenderDrawColor(renderer, RenderColorR, RenderColorG, RenderColorB, RenderOpaqueAlpha);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        

        SDL_RenderPresent(renderer);
    }



void Update() // 
    {
        RenderColorR = rand() % 256;
        RenderColorG = rand() % 256;
        RenderColorB = rand() % 256;
    }

SDL_AppResult SDL_AppIterate(void* appstate) // Main game loop - Everything runs in realtime
    {   
        Render();
        return SDL_APP_CONTINUE;
    }

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv) 
    {

        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))    
            {
                SDL_Log("Error initializing SDL: %s", SDL_GetError());
                return SDL_APP_FAILURE;
            }

        window = SDL_CreateWindow("Game", wWidth, wHeight, NULL);
        
        if (!window) 
            {
                SDL_Log("Error creating window: %s", SDL_GetError());
                return SDL_APP_FAILURE;
            }
        
        renderer = SDL_CreateRenderer(window, NULL);

        
        if (!renderer) 
            {
                SDL_Log("Error creating renderer: %s", SDL_GetError());
                return SDL_APP_FAILURE;
            }
        
        if (!LoadBackgroundImage())
            {
                SDL_Log("Image load failed.");
                return SDL_APP_FAILURE;
            }        

        if (!SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "DEBUG", "Lorem ipsum Dolor sit amet", window))
            {
                SDL_Log("Error creating debug message: %s", SDL_GetError());
            }

        return SDL_APP_CONTINUE;
    }

