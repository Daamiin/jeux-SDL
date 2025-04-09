#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_ttf.h>


void initBackground1(background1 *bg) {
    bg->im = IMG_Load("background1.png");
       if (bg->im == NULL) {
    fprintf(stderr, "Erreur de chargement de background1.png : %s\n", IMG_GetError());
}
    bg->pos.x = 0;
    bg->pos.y = 0;
}
void initBackground2(background2 *bg2) {
    bg2->im = IMG_Load("background2.png");
      if (bg2->im == NULL) {
    fprintf(stderr, "Erreur de chargement de background1.png : %s\n", IMG_GetError());
}
    bg2->pos.x = 0;
    bg2->pos.y = 0;
}


void initBouton1(bouton1 *b) {
b->im = IMG_Load("ouinon.png");
if (b->im == NULL) fprintf(stderr, "Erreur chargement ouinon.png : %s\n", IMG_GetError());

b->im1 = IMG_Load("ouisec.png");
if (b->im1 == NULL) fprintf(stderr, "Erreur chargement ouisec.png : %s\n", IMG_GetError());

b->im2 = IMG_Load("nonnon.png");
if (b->im2 == NULL) fprintf(stderr, "Erreur chargement nonnon.png : %s\n", IMG_GetError());

b->im3 = IMG_Load("nonseec.png");
if (b->im3 == NULL) fprintf(stderr, "Erreur chargement nonseec.png : %s\n", IMG_GetError());
    b->posim.x = 280;  b->posim.y =360;
    b->posim2.x = 870; b->posim2.y = 360;
}

void initBouton2(bouton2 *bb) {
    bb->im = IMG_Load("chargernon.png");
    bb->im1 = IMG_Load("chargersec.png");
    bb->im2 = IMG_Load("nouvnon.png");
    bb->im3 = IMG_Load("nouvsec.png");
    bb->posim.x = 280;  bb->posim.y = 360;
    bb->posim2.x = 870; bb->posim2.y = 360;
}

void afficherbackground1(SDL_Surface *ecran, background1 *bg) {
    SDL_BlitSurface(bg->im, NULL, ecran, &bg->pos);
}
void afficherbackground2(SDL_Surface *ecran, background2 *bg) {
    SDL_BlitSurface(bg->im, NULL, ecran, &bg->pos);
}



void afficherBouton1(SDL_Surface *ecran, bouton1 *b, int ok) {
    SDL_BlitSurface(ok == 1 ? b->im1 : b->im, NULL, ecran, &b->posim);
    SDL_BlitSurface(ok == 2 ? b->im3 : b->im2, NULL, ecran, &b->posim2);
}

void afficherBouton2(SDL_Surface *ecran, bouton2 *bb, int ok) {
    SDL_BlitSurface(ok == 3 ? bb->im1 : bb->im, NULL, ecran, &bb->posim);
    SDL_BlitSurface(ok == 4 ? bb->im3 : bb->im2, NULL, ecran, &bb->posim2);
}

void mouseMotion1(SDL_Event event, bouton1 *b, int *ok, sound *s) {
    int prevOk = *ok;
    *ok = 0;
    if (event.motion.x >= b->posim.x && event.motion.x <= (b->posim.x + 254) &&
        event.motion.y >= b->posim.y && event.motion.y <= (b->posim.y + 118)) {
        *ok = 1;
    } else if (event.motion.x >= b->posim2.x && event.motion.x <= (b->posim2.x + 254) &&
               event.motion.y >= b->posim2.y && event.motion.y <= (b->posim2.y + 118)) {
        *ok = 2;
    }
    if (*ok != prevOk) Mix_PlayChannel(-1, s->bson, 0);
}

void mouseMotion2(SDL_Event event, bouton2 *bb, int *ok, sound *s) {
    int prevOk = *ok;
    *ok = 0;
    if (event.motion.x >= bb->posim.x && event.motion.x <= (bb->posim.x + 254) &&
        event.motion.y >= bb->posim.y && event.motion.y <= (bb->posim.y + 118)) {
        *ok = 3;
    } else if (event.motion.x >= bb->posim2.x && event.motion.x <= (bb->posim2.x + 261) &&
               event.motion.y >= bb->posim2.y && event.motion.y <= (bb->posim2.y + 90)) {
        *ok = 4;
    }
    if (*ok != prevOk) Mix_PlayChannel(-1, s->bson, 0);
}

void keysym(SDL_Event e, int *test, int *continuer) {
    if (e.key.keysym.sym == SDLK_ESCAPE) *continuer = 0;
}

void initSound(sound *s) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    s->bgmusic = Mix_LoadMUS("Musique du jeu.mp3");
    s->bson = Mix_LoadWAV("click.wav");
    Mix_PlayMusic(s->bgmusic, -1);
    
}


