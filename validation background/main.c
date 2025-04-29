#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "background.h"

int main(){
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        
    // Initialize SDL_mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    // Initialize SDL_ttf
    TTF_Init();

    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    int quitter = 0;
    SDL_Event event;

    Background bg;
    bg.partage = 1;
    int afficher_guide = 1;  // 1 = show guide 
    initialiser_background(&bg);

    // Player 1
    SDL_Surface *player;
    player = IMG_Load("image/perso.png");
    SDL_Rect pos_perso;
    pos_perso.x = 600;
    pos_perso.y = 300;
    pos_perso.h = player->h;
    pos_perso.w = player->w;

    int direction_x = 0;
    int direction_y = 0;
    int pas_x = 10;
    int pas_y = 7;

    // Player 2
    SDL_Surface *player2;
    player2 = IMG_Load("image/perso.png");
    SDL_Rect pos_perso2;
    pos_perso2.x = 200 + 1920/2;
    pos_perso2.y = 300;
    pos_perso2.h = player2->h;
    pos_perso2.w = player2->w;

    int direction_x2 = 0;
    int direction_y2 = 0;
    int pas_x2 = 10;
    int pas_y2 = 7;

    while (quitter == 0) {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        
        if (afficher_guide) {
            afficher_menu_controles(screen);
        } else {
            
            afficher_background(bg, screen);
            SDL_BlitSurface(player, NULL, screen, &pos_perso);
            if (bg.partage == 1) {
                SDL_BlitSurface(player2, NULL, screen, &pos_perso2);
            }
        }

        SDL_Flip(screen);

        // Evennements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quitter = 1;
                    break;
                case SDL_KEYDOWN:
                    // Player 1 
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        pos_perso.x += pas_x;
                        direction_x = 1;    
                    }
                    else if (event.key.keysym.sym == SDLK_LEFT) {
                        pos_perso.x -= pas_x;    
                        direction_x = -1;    
                    }
                    else if (event.key.keysym.sym == SDLK_UP) {
                        pos_perso.y -= pas_y;    
                        direction_y = 1;    
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN) {
                        pos_perso.y += pas_y;
                        direction_y = -1;        
                    }
                    // Player 2 
                    else if (event.key.keysym.sym == SDLK_d) {
                        pos_perso2.x += pas_x2;
                        direction_x2 = 1;    
                    }
                    else if (event.key.keysym.sym == SDLK_q) {
                        pos_perso2.x -= pas_x2;    
                        direction_x2 = -1;    
                    }
                    else if (event.key.keysym.sym == SDLK_z) {
                        pos_perso2.y -= pas_y2;    
                        direction_y2 = 1;    
                    }
                    else if (event.key.keysym.sym == SDLK_s) {
                        pos_perso2.y += pas_y2;
                        direction_y2 = -1;        
                    }
                    // guide with ESC
                    else if (event.key.keysym.sym == SDLK_ESCAPE) {
                        afficher_guide = !afficher_guide;
                    }
                    break;
                    
                case SDL_KEYUP:
                    // Player 1                
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        direction_x = 0;    
                    }
                    else if (event.key.keysym.sym == SDLK_LEFT) {
                        direction_x = 0;    
                    }
                    else if (event.key.keysym.sym == SDLK_UP) {
                        direction_y = 0;    
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN) {
                        direction_y = 0;        
                    }
                    // Player 2
                    else if (event.key.keysym.sym == SDLK_d) {
                        direction_x2 = 0;    
                    }
                    else if (event.key.keysym.sym == SDLK_q) {
                        direction_x2 = 0;    
                    }
                    else if (event.key.keysym.sym == SDLK_z) {
                        direction_y2 = 0;    
                    }
                    else if (event.key.keysym.sym == SDLK_s) {
                        direction_y2 = 0;        
                    }
                    break;
                    
                default:
                    break;
            }
        }

        // mise a jour
        scrolling(&bg, direction_x, direction_y, pas_x, pas_y, 0);
        if (bg.partage == 1) {
            scrolling(&bg, direction_x2, direction_y2, pas_x2, pas_y2, 1);
        }
        gestion_temps(&bg.temp);
    }
   
    // Clean up
    SDL_FreeSurface(player);
    SDL_FreeSurface(player2);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
