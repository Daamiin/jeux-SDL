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



