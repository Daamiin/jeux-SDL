#include <SDL/SDL_mixer.h>
#include "menu.h"

void init_menu(Menu *m)
{
 m->bg_principale = IMG_Load ("/home/amin/Desktop/menue principale/photo/menue principale.png");

 m -> musique_bg = Mix_LoadMUS("/home/amin/Desktop/menue principale/son/sonmenue.mp3");
 Mix_PlayMusic (m ->musique_bg,-1);

 m ->son = Mix_LoadWAV("/home/amin/Desktop/menue principale/son/hover.wav");
if (!m->son) {
    printf("Error loading hover sound: %s\n", Mix_GetError());
    exit(1);  
}
 
 if(m->bg_principale == NULL)
	{
	 printf("error load bg principale\n");	
	}

	m -> jouer_btn[0] = IMG_Load("/home/amin/Desktop/menue principale/photo/jouer0.jpg");
	m -> jouer_btn[1] = IMG_Load("/home/amin/Desktop/menue principale/photo/jouer1.png");

	m -> option_btn[0] = IMG_Load("/home/amin/Desktop/menue principale/photo/option0.png");
	m -> option_btn[1] = IMG_Load("/home/amin/Desktop/menue principale/photo/option1.png");

	m -> meilleur_btn[0] = IMG_Load("/home/amin/Desktop/menue principale/photo/mei0.png");
	m -> meilleur_btn[1] = IMG_Load("/home/amin/Desktop/menue principale/photo/mei1.png");

	m -> histoir_btn[0] = IMG_Load("/home/amin/Desktop/menue principale/photo/hist0.png");
	m -> histoir_btn[1] = IMG_Load("/home/amin/Desktop/menue principale/photo/hist1.png");

	m -> quit_btn[0] = IMG_Load("/home/amin/Desktop/menue principale/photo/quit0.png");
	m -> quit_btn[1] = IMG_Load("/home/amin/Desktop/menue principale/photo/quit1.png");

	m -> pos_btn_jouer.x = 50 ;
	m -> pos_btn_jouer.y = 250 ;
	m -> pos_btn_jouer.w = m -> jouer_btn[0] -> w;
	m -> pos_btn_jouer.h = m -> jouer_btn[0] -> h;

	m -> pos_btn_option.x = 50 ;
	m -> pos_btn_option.y = 350 ;
	m -> pos_btn_option.w = m -> option_btn[0] -> w;
	m -> pos_btn_option.h = m -> option_btn[0] -> h;

	m -> pos_btn_meilleur.x = 50 ;
	m -> pos_btn_meilleur.y = 450 ;
	m -> pos_btn_meilleur.w = m -> meilleur_btn[0] -> w;
	m -> pos_btn_meilleur.h = m -> meilleur_btn[0] -> h;

	m -> pos_btn_histoir.x = 50 ;
	m -> pos_btn_histoir.y = 550 ;
	m -> pos_btn_histoir.w = m -> histoir_btn[0] -> w;
	m -> pos_btn_histoir.h = m -> histoir_btn[0] -> h;

	m -> pos_btn_quit.x = 1150 ;
	m -> pos_btn_quit.y = 600 ;
	m -> pos_btn_quit.w = m -> quit_btn[0] -> w;
	m -> pos_btn_quit.h = m -> quit_btn[0] -> h;


}

void afficher_menu(Menu m,SDL_Surface *ecran)
{

SDL_BlitSurface(m.bg_principale,NULL,ecran,NULL);
if (collision_avec_souris(m.pos_btn_jouer) == 0 && m.btn_select != 1)
{
SDL_BlitSurface(m.jouer_btn[0],NULL,ecran,&m.pos_btn_jouer);
}
else
{
SDL_BlitSurface(m.jouer_btn[1],NULL,ecran,&m.pos_btn_jouer);
}
if (collision_avec_souris(m.pos_btn_option) == 0 && m.btn_select != 2)
{
SDL_BlitSurface(m.option_btn[0],NULL,ecran,&m.pos_btn_option);
}
else
{
SDL_BlitSurface(m.option_btn[1],NULL,ecran,&m.pos_btn_option);
}
if (collision_avec_souris(m.pos_btn_meilleur) == 0 && m.btn_select != 3)
{
SDL_BlitSurface(m.meilleur_btn[0],NULL,ecran,&m.pos_btn_meilleur);
}
else
{
SDL_BlitSurface(m.meilleur_btn[1],NULL,ecran,&m.pos_btn_meilleur);
}
if (collision_avec_souris(m.pos_btn_histoir) == 0 && m.btn_select != 4)
{
SDL_BlitSurface(m.histoir_btn[0],NULL,ecran,&m.pos_btn_histoir);
}
else
{
SDL_BlitSurface(m.histoir_btn[1],NULL,ecran,&m.pos_btn_histoir);
}
if (collision_avec_souris(m.pos_btn_quit) == 0 && m.btn_select != 5)
{
SDL_BlitSurface(m.quit_btn[0],NULL,ecran,&m.pos_btn_quit);
}
else
{

SDL_BlitSurface(m.quit_btn[1],NULL,ecran,&m.pos_btn_quit);
}}





int collision_avec_souris(SDL_Rect pos_btn)
{
int x_souris,y_souris;
SDL_GetMouseState(&x_souris,&y_souris);
if(x_souris > pos_btn.x && x_souris < (pos_btn.x + pos_btn.w) && y_souris > pos_btn.y && y_souris < (pos_btn.y + pos_btn.h))
{

return 1;
}
else 

return 0;

}

void miseajour_menu(Menu *m)
{

if(collision_avec_souris(m->pos_btn_jouer) == 1)
	{	
		if(m->btn_select != 1){
			Mix_PlayChannel(-1, m->son,0);}
			m -> btn_select = 1;
		
	}
else if(collision_avec_souris(m->pos_btn_option) == 1)
{
		if(m->btn_select != 2){
			Mix_PlayChannel(-1, m->son,0);}
		m -> btn_select = 2;
}
else if(collision_avec_souris(m->pos_btn_meilleur) == 1)
{
		if(m->btn_select != 3){
			Mix_PlayChannel(-1, m->son,0);}
		m -> btn_select = 3;
}
else if(collision_avec_souris(m->pos_btn_histoir) == 1)
{
		if(m->btn_select != 4){
			Mix_PlayChannel(-1, m->son,0);}
		m -> btn_select = 4;
		
}
else if(collision_avec_souris(m->pos_btn_quit) == 1)
{
		if(m->btn_select != 5){
			Mix_PlayChannel(-1, m->son,0);}
		m -> btn_select = 5;

}

else
{
m -> btn_select = 0;
}
	
}

