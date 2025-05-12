#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	SDL_Surface *ecran = NULL;
	SDL_Event event;
	int continuer = 1;
	Menu menu;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Initialize SDL_image
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("Error initializing SDL_image: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Initialize SDL_ttf
	if(TTF_Init() == -1) {
		printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// Initialize SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		printf("Error initializing audio: %s\n", Mix_GetError());
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// Set video mode
	ecran = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (!ecran) {
		printf("Error setting video mode: %s\n", SDL_GetError());
		Mix_CloseAudio();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// Set window title
	SDL_WM_SetCaption("Game Menu", NULL);

	// Initialize menu
	init_menu(&menu, ecran);
	menu.ecran = ecran;  // Store the screen surface

	// Main game loop
	while (continuer) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					continuer = 0;
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (menu.GAMEPAGE == 0) {
							// Main menu button handling
							if (menu.buttonon == 1) {
								// Play button clicked
								printf("Play button clicked\n");
							} else if (menu.buttonon == 2) {
								// Options button clicked
								menu.GAMEPAGE = 1;
							} else if (menu.buttonon == 3) {
								// High scores button clicked
								menu.GAMEPAGE = 2;  // Switch to high scores menu
							} else if (menu.buttonon == 4) {
								// History button clicked
								printf("History button clicked\n");
							} else if (menu.buttonon == 5) {
								// Quit button clicked
								continuer = 0;
							}
						} else if (menu.GAMEPAGE == 1) {
							// Options menu button handling
							switch (menu.buttonon) {
								case 1: // Volume decrease
									menu.volume = (menu.volume > 0) ? menu.volume - 10 : 0;
									Mix_VolumeMusic(menu.volume);
									sonbref(&menu);
									break;
								case 2: // Volume increase
									menu.volume = (menu.volume < 128) ? menu.volume + 10 : 128;
									Mix_VolumeMusic(menu.volume);
									sonbref(&menu);
									break;
								case 3: // Window mode
									menu.window = 0;
									SDL_WM_GrabInput(SDL_GRAB_OFF);  // Release mouse grab
									SDL_WM_SetCaption("Game Menu", NULL);
									menu.ecran = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
									if (!menu.ecran) {
										printf("Error setting window mode: %s\n", SDL_GetError());
									} else {
										ecran = menu.ecran;
										// Reset mouse position to center of window
										SDL_WarpMouse(640, 360);
									}
									sonbref(&menu);
									break;
								case 4: // Fullscreen mode
									menu.window = 1;
									SDL_WM_GrabInput(SDL_GRAB_ON);  // Grab mouse in fullscreen
									SDL_WM_SetCaption("Game Menu", NULL);
									menu.ecran = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
									if (!menu.ecran) {
										printf("Error setting fullscreen mode: %s\n", SDL_GetError());
									} else {
										ecran = menu.ecran;
									}
									sonbref(&menu);
									break;
								case 5: // Return to main menu
									menu.GAMEPAGE = 0;
									sonbref(&menu);
									break;
							}
						} else if (menu.GAMEPAGE == 2) {
							// Handle high scores menu clicks
							if (collision_avec_souris(menu.pos_btn_retour)) {
								menu.GAMEPAGE = 0;  // Return to main menu
								sonbref(&menu);
							}
						}
					}
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE && menu.GAMEPAGE == 1) {
						menu.GAMEPAGE = 0;  // Return to main menu on ESC
					} else if (event.key.keysym.sym == SDLK_f) {
						// Toggle fullscreen when F key is pressed
						menu.window = !menu.window;  // Toggle window state
						if (menu.window) {
							SDL_WM_GrabInput(SDL_GRAB_ON);  // Grab mouse in fullscreen
							SDL_WM_SetCaption("Game Menu", NULL);
							menu.ecran = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
						} else {
							SDL_WM_GrabInput(SDL_GRAB_OFF);  // Release mouse grab
							SDL_WM_SetCaption("Game Menu", NULL);
							menu.ecran = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
						}
						if (!menu.ecran) {
							printf("Error toggling fullscreen: %s\n", SDL_GetError());
						} else {
							ecran = menu.ecran;
						}
					}
					break;
			}
		}

		miseajour_menu(&menu);
		afficher_menu(menu, ecran);
		SDL_Flip(ecran);
		
		// Cap frame rate
		SDL_Delay(16); // ~60 FPS
	}

	// Cleanup
	cleanup_menu(&menu);
	Mix_CloseAudio();
	SDL_FreeSurface(ecran);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
} 