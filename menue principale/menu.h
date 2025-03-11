#ifndef MENUE_H_INCLUDED
#define MENUE_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct
{
	SDL_Surface *bg_principale;

	Mix_Music *musique_bg;
	Mix_Chunk *son;

	SDL_Surface *jouer_btn[2];
	SDL_Surface *option_btn[2];
	SDL_Surface *meilleur_btn[2];
	SDL_Surface *histoir_btn[2];
	SDL_Surface *quit_btn[2];

	SDL_Rect pos_btn_jouer;
	SDL_Rect pos_btn_option;
	SDL_Rect pos_btn_meilleur;
	SDL_Rect pos_btn_histoir;
	SDL_Rect pos_btn_quit;

	int btn_select;
	

}Menu;

void init_menu(Menu *m);
void afficher_menu(Menu m,SDL_Surface *ecran);
int collision_avec_souris(SDL_Rect pos_btn);
void miseajour_menu(Menu *m);

#endif
