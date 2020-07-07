#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


using std::cerr;
using std::endl;
using std::cout;

int main1(int argc, char const *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "fatal: SDL init video error!" << endl;
    }
    SDL_Window *win = SDL_CreateWindow("df-tanks", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Surface *suf = SDL_GetWindowSurface(win);

    SDL_FillRect(suf, NULL, SDL_MapRGB(suf->format, 0x00, 0xff, 0xff));
    
    SDL_UpdateWindowSurface(win);

    SDL_Delay(4000);

    SDL_DestroyWindow(win);
    win = nullptr;
    SDL_Quit();
    return 0;
}


int main(int argc, char const *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "fatal: SDL init video error!" << endl;
    }
    SDL_Window *win = SDL_CreateWindow("df-tanks", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    SDL_Surface *suf = SDL_GetWindowSurface(win);
    SDL_Surface *helloworld = nullptr;
    
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cerr << "SDL image could not initialize." << endl;
    }

    helloworld = IMG_Load("start.png");
    if (!helloworld) {
        cerr << "fatal: SDL load bmp file error!" << endl;
    }
    bool quitflag = false;
    SDL_Event e;
    
    SDL_FillRect(suf, NULL, SDL_MapRGB(suf->format, 0xff, 0xff, 0xff));
    while(!quitflag) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quitflag = true;
            }
        SDL_BlitSurface(helloworld, NULL, suf, NULL);
        SDL_UpdateWindowSurface(win);
        }
    }

    return 0;
}

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

int main3(int argc, char const *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "fatal: SDL init video error!" << endl;
    }
    SDL_Window *win = SDL_CreateWindow("df-tanks", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Surface *suf = SDL_GetWindowSurface(win);
    SDL_Surface *loadsuf = SDL_LoadBMP("start.bmp");
    SDL_Surface *optsuf = NULL;
    optsuf = SDL_ConvertSurface(loadsuf, suf->format, 0);

    SDL_Rect strechRect;
    strechRect.x = 0;
    strechRect.y = 0;
    strechRect.w = 640;
    strechRect.h = 480;
    SDL_BlitSurface(loadsuf, NULL, suf, &strechRect);

    SDL_UpdateWindowSurface(win);

    SDL_Delay(2000);

    SDL_FreeSurface(loadsuf);
    return 0;
}

