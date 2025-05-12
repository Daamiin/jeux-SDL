#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_events.h>

#define MAX_SCORES 3

typedef struct {
	int score;
	char name[50];
} HighScore;

typedef struct
{
	// Main menu elements
	SDL_Surface *bg_principale;
	SDL_Surface *options_bg;
	SDL_Surface *highscores_bg;  // Background for high scores
	SDL_Surface *ecran;

	Mix_Music *musique_bg;
	Mix_Chunk *son;

	SDL_Surface *jouer_btn[2];
	SDL_Surface *option_btn[2];
	SDL_Surface *meilleur_btn[2];
	SDL_Surface *histoir_btn[2];
	SDL_Surface *quit_btn[2];
	SDL_Surface *retour_btn[2];  // Return button for high scores

	SDL_Rect pos_btn_jouer;
	SDL_Rect pos_btn_option;
	SDL_Rect pos_btn_meilleur;
	SDL_Rect pos_btn_histoir;
	SDL_Rect pos_btn_quit;
	SDL_Rect pos_btn_retour;  // Position for return button
	SDL_Rect pos_options_bg;
	SDL_Rect pos_highscores_bg;

	// High scores elements
	HighScore top_scores[MAX_SCORES];
	TTF_Font *score_font;
	SDL_Surface *score_surfaces[MAX_SCORES];
	SDL_Rect score_positions[MAX_SCORES];

	// Options menu elements
	SDL_Surface *BACKGROUND;
	SDL_Surface *ECRANMENU;
	SDL_Surface *DIM1;
	SDL_Surface *DIM2;
	SDL_Surface *AUG1;
	SDL_Surface *AUG2;
	SDL_Surface *FEN1;
	SDL_Surface *FEN2;
	SDL_Surface *PLEIN1;
	SDL_Surface *PLEIN2;
	SDL_Surface *RET1;
	SDL_Surface *RET2;
	
	SDL_Rect positionBACKGROUND;
	SDL_Rect positionDIM;
	SDL_Rect positionAUG;
	SDL_Rect positionFEN;
	SDL_Rect positionPLEIN;
	SDL_Rect positionRET;
	SDL_Rect positionTXT;
	SDL_Rect positionTEXT;
	
	Mix_Chunk *sonbutton;
	int buttonon;
	int GAMEPAGE;  // 0: main menu, 1: options, 2: high scores
	int changemenu;
	int SELECTEDBUT;
	int sonbref;
	int window;
	int volume;
	TTF_Font *police;
	SDL_Surface *text;
	SDL_Color white;
	Mix_Music *music;

} Menu;

// Main menu functions
void init_menu(Menu *m, SDL_Surface *ecran);
void afficher_menu(Menu m, SDL_Surface *ecran);
int collision_avec_souris(SDL_Rect pos_btn);
void miseajour_menu(Menu *m);
void cleanup_menu(Menu *m);
void sonbref(Menu *menu);
void handle_options_input(Menu *menu, SDL_Event event);

// High scores functions
void init_highscores(Menu *m);
void load_highscores(Menu *m);
void save_highscores(Menu *m);
void add_highscore(Menu *m, int score, const char *name);
void afficher_highscores(Menu *m, SDL_Surface *ecran);
void cleanup_highscores(Menu *m);

// Options menu functions
void initMENU(Menu *menu);
void MenuINPUTS(Menu *menu, SDL_Event event);
void afficherMENU(Menu *menu, SDL_Surface *fenetre);

#endif 