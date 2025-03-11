#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "menu.h"

int main()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	SDL_Surface *ecran;

	ecran = SDL_SetVideoMode(1366,720,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096);
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096)== -1)
	{
		printf("%s",Mix_GetError());
	}

	int quitter  = 0;
	SDL_Event event;
	int indice_ecran = 0;
	Menu menu;
	init_menu(&menu);
	

	while(quitter == 0)
	{
		switch(indice_ecran)
		{
		 case 0: //menue principale
		 
			// affichege
			afficher_menu(menu,ecran);
			SDL_Flip(ecran);
			
			//gestion des evments
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					//quitter si fenetre closed
				case SDL_QUIT:
					quitter = 1;
					break;
				case SDL_MOUSEBUTTONDOWN :
				if(event.button.button == SDL_BUTTON_LEFT)
					{
						if(menu.btn_select == 5)
							{
								quitter = 1;
							}
						if(menu.btn_select == 4)
							{
								indice_ecran  = 4;
							}
						if(menu.btn_select == 3)
							{
								indice_ecran  = 3;
							}
						if(menu.btn_select == 2)
							{
								indice_ecran  = 2;
							}
						if(menu.btn_select == 1)
							{
								indice_ecran = 1;
							}
					}
				
					break;

				
					 case SDL_KEYDOWN:
					//echape pour quitter
				 if (event.key.keysym.sym == SDLK_ESCAPE)
				   quitter = 1;
					
					//switch to menue savegarde si j is pressed
				 if (event.key.keysym.sym == SDLK_j)
				   indice_ecran = 1;
					
					//switch to option  si o is pressed
				 if (event.key.keysym.sym == SDLK_o)
				   indice_ecran = 2;
					
					//switch to menue meilleur si m is pressed
				 if (event.key.keysym.sym == SDLK_m)
				   indice_ecran = 3;
					break;
		
				   quitter = 1;
					
					
				default:
				 break;				
				
				}
			
				
			}
			miseajour_menu(&menu);
			break;
		 	
		case 1: //sous menue joueur
			SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran -> format,0,0,0));
			SDL_Flip(ecran);
		while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					//quitter si fenetre closed
				case SDL_QUIT:
					quitter = 1;
					break;
				case SDL_KEYDOWN:
					//echape pour quitter
				 if (event.key.keysym.sym == SDLK_ESCAPE)
				   indice_ecran = 0;
					break;
				
				}
			}
		break;
		case 2: //sous menue option
				SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran -> format,20,60,0));
			SDL_Flip(ecran);
		while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					//quitter si fenetre closed
				case SDL_QUIT:
					quitter = 1;
					break;
				case SDL_KEYDOWN:
					//echape pour quitter
				 if (event.key.keysym.sym == SDLK_ESCAPE)
				   indice_ecran = 0;
					break;
				
				}
			}
		break;
		case 3: //sous menue meilleur score
				SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran -> format,50,10,30));
			SDL_Flip(ecran);
		while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					//quitter si fenetre closed
				case SDL_QUIT:
					quitter = 1;
					break;
				case SDL_KEYDOWN:
					//echape pour quitter
				 if (event.key.keysym.sym == SDLK_ESCAPE)
				   indice_ecran = 0;
					break;
				
				}
			}
		break;
		case 4: //sous menue enigme
				SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran -> format,70,0,20));
			SDL_Flip(ecran);
		while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					//quitter si fenetre closed
				case SDL_QUIT:
					quitter = 1;
					break;
				case SDL_KEYDOWN:
					//echape pour quitter
				 if (event.key.keysym.sym == SDLK_ESCAPE)
				   indice_ecran = 0;
					break;
				
				}
			}
		break;
		 default:
		  break;
		}
	}
	SDL_FreeSurface(ecran);
	SDL_Quit();
}

