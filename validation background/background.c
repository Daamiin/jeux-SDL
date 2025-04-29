#include "background.h"

void initialiser_background(Background *b)
{
//verifier si taswira loaded ou non
	b->image = IMG_Load("image/background/background1.png");
	if(b->image == NULL)
	{
		printf("erreur load background\n");
		exit(1);
	}	
	else
	{
		printf("img loaded\n");
	}

	b->pos_ecran[0].x = 0;
	b->pos_ecran[0].y = 0;

	//position intitial d'affichage
	b->pos_affichage[0].x = 0;
	b->pos_affichage[0].y = 0;

	if(b->partage == 0) // mono
	{
		
	b->pos_ecran[0].w = 1920 /2;
	b->pos_ecran[0].h = 1080 /2;

	b->pos_affichage[0].w = 1920 ;
	b->pos_affichage[0].h = 1080 ;
	}
	else //multi
	{

    b->pos_affichage[0].x = 0;
    b->pos_affichage[0].y = 0;
    b->pos_affichage[0].w = b->image->w / 2;
    b->pos_affichage[0].h = b->image->h;

    b->pos_affichage[1].x = b->image->w / 2 ; 
    b->pos_affichage[1].y = 0;
    b->pos_affichage[1].w = b->image->w / 2;
    b->pos_affichage[1].h = b->image->h;

    b->pos_ecran[0].x = 0;
    b->pos_ecran[0].y = 0;
    b->pos_ecran[0].w = 1920 / 2;
    b->pos_ecran[0].h = 1080;

    b->pos_ecran[1].x = 1920 / 2 ;
    b->pos_ecran[1].y = 0;
    b->pos_ecran[1].w = 1920 / 2;
    b->pos_ecran[1].h = 1080;	
	}
	initialiser_temps(&b->temp);

}

void afficher_background(Background b,SDL_Surface *ecran){

	SDL_BlitSurface(b.image,&b.pos_affichage[0],ecran,&b.pos_ecran[0]);
	if(b.partage == 1)
	{	
		SDL_BlitSurface(b.image,&b.pos_affichage[1],ecran,&b.pos_ecran[1]); //afficher ecran partagee seulement si selectionnéé
	}
	afficher_temps(b.temp,ecran);
}

void scrolling(Background *b,int direction_x,int direction_y,int dx , int dy,int num_ecran){

	if(b->partage == 0)
	{
		

		if(direction_x == 1) //movement du background
		{
		   if(b->pos_affichage[0].x + dx < (b->image->w - 1920)) // limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[0].x += dx;
		}
		else if(direction_x == -1)
		{
	 	  if(b->pos_affichage[0].x - dx > 0)		// limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[0].x -= dx;
		}
	

		if(direction_y == 1)
		{
		   if(b->pos_affichage[0].y - dy > 0)		// limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[0].y -= dy;
		}
		else if(direction_y == -1)
		{
		   if(b->pos_affichage[0].y + dy < (b->image->h - 1080)) // limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[0].y += dy;
		}

	}
	else
	{


		//ecran 1-------------------------------------------------------------------------------------------------
	if(num_ecran == 0)
	   {
		if(direction_x == 1) //movement du background
		{
		   if(b->pos_affichage[0].x + dx < (b->image->w - 1920 /2)) // limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[0].x += dx;
		}
		else if(direction_x == -1)
		{
	 	  if(b->pos_affichage[0].x - dx > 0)		// limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[0].x -= dx;
		}
	

		if(direction_y == 1)
		{
		   if(b->pos_affichage[0].y - dy > 0)		// limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[0].y -= dy;
		}
		else if(direction_y == -1)
		{
		   if(b->pos_affichage[0].y + dy < (b->image->h - 1080)) // limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[0].y += dy;
		}

	   }
		//ecran 2-------------------------------------------------------------------------------------------------
	if(num_ecran == 1)
	   {
		if(direction_x == 1) //movement du background
		{
		   if(b->pos_affichage[1].x + dx < (b->image->w - 1920 /2)) // limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[1].x += dx;
		}
		else if(direction_x == -1)
		{
	 	  if(b->pos_affichage[1].x - dx > 0)		// limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[1].x -= dx;
		}
	

		if(direction_y == 1)
		{
		   if(b->pos_affichage[1].y - dy > 0)		// limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[1].y -= dy;
		}
		else if(direction_y == -1)
		{
		   if(b->pos_affichage[1].y + dy < (b->image->h - 1080)) // limiter le mvt du bg bech mato5rejch barra ml ecran
			b->pos_affichage[1].y += dy;
		}
	    }

	}


}



void initialiser_temps(Temps *t)
{

t -> temps_debut = SDL_GetTicks(); //te5ou bl 1000
strcpy(t->texte ,"Time : 00:00");
t->pos_temps.x = 50;
t->pos_temps.y = 50;

t->font = TTF_OpenFont("font/arial.ttf",30);
 	//couleur text
t->color_temps.r = 255;
t->color_temps.g = 255;
t->color_temps.b = 255;

t->min = 0;
t-> sec = 0;

t-> image_text = TTF_RenderText_Blended(t->font,t->texte,t->color_temps); //prepare le texte pour afficher

}



void afficher_temps(Temps t,SDL_Surface *ecran)
{
	SDL_BlitSurface(t.image_text,NULL,ecran,&t.pos_temps);
}




void gestion_temps(Temps *t)
{

t-> temps_actuelle = SDL_GetTicks();

int temps_total_ms = t->temps_actuelle - t->temps_debut; //differnce entre 
int temps_total_sec = temps_total_ms / 1000;

t-> min = (temps_total_sec / 60)%60; // pour pas depasser les heur il affiche seulement min
t->sec = (temps_total_sec %60); //% bech ne5ou just be9i l9Esma
sprintf(t->texte, "Time : %02d:%02d", t->min, t->sec); //%2 bech yabda b 00
t->image_text = TTF_RenderText_Blended(t->font,t->texte,t->color_temps);


}


/* Dessine un bouton pour les contrôles */
void dessiner_bouton_controle(SDL_Surface *ecran, int x, int y, int w, int h, const char *texte, SDL_Color couleur) {
    // Fond du bouton
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));

    // Bordure noire
    SDL_Rect bordure = {x-2, y-2, w+4, h+4};
    SDL_FillRect(ecran, &bordure, SDL_MapRGB(ecran->format, 0, 0, 0));

    // Texte centré
    TTF_Font *police = TTF_OpenFont("font/arial.ttf", 24);
    if (!police) return;
    
    SDL_Surface *texte_surface = TTF_RenderText_Blended(police, texte, (SDL_Color){255, 255, 255});
    SDL_Rect pos_texte = {
        x + (w - texte_surface->w)/2,
        y + (h - texte_surface->h)/2
    };
    SDL_BlitSurface(texte_surface, NULL, ecran, &pos_texte);
    
    SDL_FreeSurface(texte_surface);
    TTF_CloseFont(police);
}

/* Affiche le menu des contrôles */
void afficher_menu_controles(SDL_Surface *ecran) {
   
    SDL_Rect fond = {0, 0, 1920, 1080};
    SDL_FillRect(ecran, &fond, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_SetAlpha(ecran, SDL_SRCALPHA, 128);

    
    SDL_Rect fenetre = {460, 190, 1000, 700};
    SDL_FillRect(ecran, &fenetre, SDL_MapRGB(ecran->format, 30, 30, 50));

    
    TTF_Font *titre_police = TTF_OpenFont("font/arial.ttf", 48);
    if (titre_police) {
        SDL_Surface *titre = TTF_RenderText_Blended(titre_police, "CONTROLES DU JEU", (SDL_Color){255, 200, 0});
        SDL_Rect pos_titre = {960 - titre->w/2, 220};
        SDL_BlitSurface(titre, NULL, ecran, &pos_titre);
        SDL_FreeSurface(titre);
        TTF_CloseFont(titre_police);
    }

    // Contrôles Joueur 1 
    dessiner_bouton_controle(ecran, 560, 320, 300, 60, "JOUEUR 1", (SDL_Color){70, 70, 120});
    dessiner_bouton_controle(ecran, 560, 400, 120, 50, "HAUT: !", (SDL_Color){100, 100, 150});
    dessiner_bouton_controle(ecran, 560, 460, 120, 50, "BAS:!", (SDL_Color){100, 100, 150});
    dessiner_bouton_controle(ecran, 440, 460, 120, 50, "GAUCHE:<=", (SDL_Color){100, 100, 150});
    dessiner_bouton_controle(ecran, 680, 460, 120, 50, "DROITE:=>", (SDL_Color){100, 100, 150});

    // Contrôles Joueur 2 
    dessiner_bouton_controle(ecran, 1060, 320, 300, 60, "JOUEUR 2", (SDL_Color){120, 70, 70});
    dessiner_bouton_controle(ecran, 1060, 400, 120, 50, "HAUT: Z", (SDL_Color){150, 100, 100});
    dessiner_bouton_controle(ecran, 1060, 460, 120, 50, "BAS: S", (SDL_Color){150, 100, 100});
    dessiner_bouton_controle(ecran, 940, 460, 120, 50, "GAUCHE: Q", (SDL_Color){150, 100, 100});
    dessiner_bouton_controle(ecran, 1180, 460, 120, 50, "DROITE: D", (SDL_Color){150, 100, 100});

    // Bouton de fermeture
    dessiner_bouton_controle(ecran, 810, 600, 300, 80, "APPUYER SUR ECHAP", (SDL_Color){180, 50, 50});
}



