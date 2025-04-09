#include "header.h"


int main(int argc, char *argv[]) {
    SDL_Surface *ecran = NULL;
    background1 bg;
    background2 bg2;
    bouton1 b;
    bouton2 bb;
    sound s;
    SDL_Event event;
    int continuer = 1, ok = 0, test = 0;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    ecran = SDL_SetVideoMode(1650, 937, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


    initBackground1(&bg);
    initBouton1(&b);
    initBackground2(&bg2);
    initBouton2(&bb);
    initSound(&s);

    while (continuer) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_MOUSEMOTION:
                    mouseMotion1(event, &b, &ok, &s);
                    mouseMotion2(event, &bb, &ok, &s);
                    break;
                case SDL_KEYDOWN:
                    keysym(event, &test, &continuer);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (event.button.x >= b.posim.x && event.button.x <= (b.posim.x + 254) &&
                            event.button.y >= b.posim.y && event.button.y <= (b.posim.y + 118)) {
                            test = 1;  
                        }
                        if (event.button.x >= bb.posim2.x && event.button.x <= (bb.posim2.x + 254) &&
                            event.button.y >= bb.posim2.y && event.button.y <= (bb.posim2.y + 118)) {
                            continuer = 0;
                        }
                    }
                    break;
            }
        }

        if (test) {
            afficherbackground2(ecran, &bg2);
            afficherBouton2(ecran, &bb, ok);
        } else {
            afficherbackground1(ecran, &bg);
            afficherBouton1(ecran, &b, ok);
        }

        SDL_Flip(ecran);
    }
    

    SDL_Quit();
    return 0;
}
