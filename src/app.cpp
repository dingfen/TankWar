#include "app.h"
#include "spriteconfig.h"

void App::run() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "fatal: SDL init video error!" << endl;
    }
    SDL_Window *win = SDL_CreateWindow("df-tankwar", 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            AppConfig::window_rect.w, AppConfig::window_rect.h, SDL_WINDOW_SHOWN);
    int imgflags = IMG_INIT_PNG;
    SDL_Surface *loadsuf = IMG_Load("resources/png/texture.png");
    if (!(IMG_Init(imgflags) & imgflags)) {
        cerr << "fatal: SDL init IMG error" << endl;
    }

    SDL_Renderer *render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect rect[4];
    SpriteConfig sc;
    rect[0] = sc.get(SpriteType::TANK_A).rect;
    rect[1].x = 150;
    rect[1].y = 100;
    rect[1].h = 32;
    rect[1].w = 32;
    SDL_Texture *text = SDL_CreateTextureFromSurface(render, loadsuf);
    
    SDL_RenderCopy(render, text, &rect[0], &rect[1]);

    SDL_RenderPresent(render);
    SDL_UpdateWindowSurface(win);

    SDL_Delay(2000);
    SDL_FreeSurface(loadsuf);
    SDL_DestroyWindow(win);
    win = nullptr;
    SDL_Quit();
}