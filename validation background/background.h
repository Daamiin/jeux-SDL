#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct {

int temps_debut;
int temps_actuelle;

SDL_Surface *image_text;
char texte[20];

SDL_Rect pos_temps;
TTF_Font *font;
SDL_Color color_temps;
int min,sec;

} Temps;

typedef struct {
    SDL_Surface *image; 
    SDL_Rect pos_ecran[2];
    SDL_Rect pos_affichage[2];  
    int partage; //0 mono , 1 multi

    Temps temp;
} Background;

void initialiser_background(Background *b);
void afficher_background(Background b,SDL_Surface *ecran);
void scrolling(Background *b,int direction_x,int direction_y,int dx , int dy,int num_ecran);


void initialiser_temps(Temps *t);
void afficher_temps(Temps t,SDL_Surface *ecran);
void gestion_temps(Temps *t);

/* Fonctions pour le menu des contrôles */
void afficher_menu_controles(SDL_Surface *ecran);
void dessiner_bouton_controle(SDL_Surface *ecran, int x, int y, int w, int h, const char *texte, SDL_Color couleur);

#endif // BACKGROUND_H_INCLUDED
