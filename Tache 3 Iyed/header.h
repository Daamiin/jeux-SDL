#ifndef SAUVGARDER_H
#define SAUVGARDER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>




typedef struct {
    SDL_Surface *im;
    SDL_Rect pos;
} background1, background2;

typedef struct {
    SDL_Surface *im, *im1, *im2, *im3;
    SDL_Rect posim, posim2;
} bouton1, bouton2;


typedef struct {
    Mix_Music *bgmusic;
    Mix_Chunk *bson;
} sound;



void initBackground1(background1 *bg);
void initBackground2(background2 *bg);
void initBouton1(bouton1 *b);
void initBouton2(bouton2 *bb);
void afficherbackground1(SDL_Surface *ecran, background1 *bg);
void afficherbackground2(SDL_Surface *ecran, background2 *bg);
void afficherBouton1(SDL_Surface *ecran, bouton1 *b, int ok);
void afficherBouton2(SDL_Surface *ecran, bouton2 *bb, int ok);
void mouseMotion1(SDL_Event event, bouton1 *b, int *ok, sound *s);
void mouseMotion2(SDL_Event event, bouton2 *bb, int *ok, sound *s);
void keysym(SDL_Event e, int *test, int *continuer);
void initSound(sound *s);

#endif
