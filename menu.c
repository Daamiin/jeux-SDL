#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

static int resources_initialized = 0;

void cleanup_menu(Menu *m) {
    if (!m || !resources_initialized) return;

    // Stop music if it's playing
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }

    // Free audio resources
    if (m->musique_bg) {
        Mix_FreeMusic(m->musique_bg);
        m->musique_bg = NULL;
    }
    if (m->son) {
        Mix_FreeChunk(m->son);
        m->son = NULL;
    }
    if (m->sonbutton) {
        Mix_FreeChunk(m->sonbutton);
        m->sonbutton = NULL;
    }

    // Free surfaces
    if (m->bg_principale) {
        SDL_FreeSurface(m->bg_principale);
        m->bg_principale = NULL;
    }
    if (m->options_bg) {
        SDL_FreeSurface(m->options_bg);
        m->options_bg = NULL;
    }

    // Free button surfaces
    for (int i = 0; i < 2; i++) {
        if (m->jouer_btn[i]) {
            SDL_FreeSurface(m->jouer_btn[i]);
            m->jouer_btn[i] = NULL;
        }
        if (m->option_btn[i]) {
            SDL_FreeSurface(m->option_btn[i]);
            m->option_btn[i] = NULL;
        }
        if (m->meilleur_btn[i]) {
            SDL_FreeSurface(m->meilleur_btn[i]);
            m->meilleur_btn[i] = NULL;
        }
        if (m->histoir_btn[i]) {
            SDL_FreeSurface(m->histoir_btn[i]);
            m->histoir_btn[i] = NULL;
        }
        if (m->quit_btn[i]) {
            SDL_FreeSurface(m->quit_btn[i]);
            m->quit_btn[i] = NULL;
        }
    }

    // Free options menu buttons
    if (m->DIM1) SDL_FreeSurface(m->DIM1);
    if (m->DIM2) SDL_FreeSurface(m->DIM2);
    if (m->AUG1) SDL_FreeSurface(m->AUG1);
    if (m->AUG2) SDL_FreeSurface(m->AUG2);
    if (m->FEN1) SDL_FreeSurface(m->FEN1);
    if (m->FEN2) SDL_FreeSurface(m->FEN2);
    if (m->PLEIN1) SDL_FreeSurface(m->PLEIN1);
    if (m->PLEIN2) SDL_FreeSurface(m->PLEIN2);
    if (m->RET1) SDL_FreeSurface(m->RET1);
    if (m->RET2) SDL_FreeSurface(m->RET2);

    // Cleanup high scores
    cleanup_highscores(m);

    resources_initialized = 0;
}

void init_menu(Menu *m, SDL_Surface *ecran)
{
    if (!m) {
        printf("Error: NULL pointer passed to init_menu\n");
        exit(1);
    }

    // Initialize all pointers to NULL
    memset(m, 0, sizeof(Menu));

    // Store the screen surface
    m->ecran = ecran;

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Error initializing SDL_image: %s\n", SDL_GetError());
        exit(1);
    }

    // Initialize SDL_mixer with better parameters
    int audio_rate = 44100;
    Uint16 audio_format = MIX_DEFAULT_FORMAT; // 16-bit stereo
    int audio_channels = 2;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) == -1) {
        printf("Error initializing audio: %s\n", Mix_GetError());
        IMG_Quit();
        exit(1);
    }

    // Allocate more channels for sound effects
    Mix_AllocateChannels(16);

    // Load background
    m->bg_principale = IMG_Load("photo/menue principale.png");
    if(!m->bg_principale) {
        printf("Error loading background: %s\n", SDL_GetError());
        cleanup_menu(m);
        Mix_CloseAudio();
        IMG_Quit();
        exit(1);
    }

    // Load options background
    m->options_bg = IMG_Load("../option/background.png");
    if(!m->options_bg) {
        printf("Error loading options background: %s\n", SDL_GetError());
        cleanup_menu(m);
        Mix_CloseAudio();
        IMG_Quit();
        exit(1);
    }

    // Set options background position
    m->pos_options_bg.x = 0;
    m->pos_options_bg.y = 0;
    m->pos_options_bg.w = m->options_bg->w;
    m->pos_options_bg.h = m->options_bg->h;

    // Load music with error checking
    m->musique_bg = Mix_LoadMUS("son/sonmenue.mp3");
    if(!m->musique_bg) {
        printf("Error loading music: %s\n", Mix_GetError());
        cleanup_menu(m);
        Mix_CloseAudio();
        IMG_Quit();
        exit(1);
    }

    // Load hover sound effect
    m->son = Mix_LoadWAV("son/hover.wav");
    if(!m->son) {
        printf("Error loading hover sound: %s\n", Mix_GetError());
        cleanup_menu(m);
        Mix_CloseAudio();
        IMG_Quit();
        exit(1);
    }

    // Load button images
    m->jouer_btn[0] = IMG_Load("photo/jouer0.jpg");
    m->jouer_btn[1] = IMG_Load("photo/jouer1.png");
    m->option_btn[0] = IMG_Load("photo/option0.png");
    m->option_btn[1] = IMG_Load("photo/option1.png");
    m->meilleur_btn[0] = IMG_Load("photo/mei0.png");
    m->meilleur_btn[1] = IMG_Load("photo/mei1.png");
    m->histoir_btn[0] = IMG_Load("photo/hist0.png");
    m->histoir_btn[1] = IMG_Load("photo/hist1.png");
    m->quit_btn[0] = IMG_Load("photo/quit0.png");
    m->quit_btn[1] = IMG_Load("photo/quit1.png");

    // Load options menu buttons
    m->DIM1 = IMG_Load("option/dimnon.png");
    m->DIM2 = IMG_Load("option/dimoui.png");
    m->AUG1 = IMG_Load("option/augnon.png");
    m->AUG2 = IMG_Load("option/augoui.png");
    m->FEN1 = IMG_Load("option/fennon.png");
    m->FEN2 = IMG_Load("option/fenoui.png");
    m->PLEIN1 = IMG_Load("option/pleinnon.png");
    m->PLEIN2 = IMG_Load("option/pleinoui.png");
    m->RET1 = IMG_Load("option/retnon.png");
    m->RET2 = IMG_Load("option/retoui.png");

    // Verify all images loaded correctly
    if(!m->jouer_btn[0] || !m->jouer_btn[1] || !m->option_btn[0] || !m->option_btn[1] ||
       !m->meilleur_btn[0] || !m->meilleur_btn[1] || !m->histoir_btn[0] || !m->histoir_btn[1] ||
       !m->quit_btn[0] || !m->quit_btn[1] || !m->DIM1 || !m->DIM2 || !m->AUG1 || !m->AUG2 ||
       !m->FEN1 || !m->FEN2 || !m->PLEIN1 || !m->PLEIN2 || !m->RET1 || !m->RET2) {
        printf("Error loading button images: %s\n", SDL_GetError());
        cleanup_menu(m);
        Mix_CloseAudio();
        IMG_Quit();
        exit(1);
    }

    // Set button positions
    m->pos_btn_jouer.x = 50;
    m->pos_btn_jouer.y = 250;
    m->pos_btn_jouer.w = m->jouer_btn[0]->w;
    m->pos_btn_jouer.h = m->jouer_btn[0]->h;

    m->pos_btn_option.x = 50;
    m->pos_btn_option.y = 350;
    m->pos_btn_option.w = m->option_btn[0]->w;
    m->pos_btn_option.h = m->option_btn[0]->h;

    m->pos_btn_meilleur.x = 50;
    m->pos_btn_meilleur.y = 450;
    m->pos_btn_meilleur.w = m->meilleur_btn[0]->w;
    m->pos_btn_meilleur.h = m->meilleur_btn[0]->h;

    m->pos_btn_histoir.x = 50;
    m->pos_btn_histoir.y = 550;
    m->pos_btn_histoir.w = m->histoir_btn[0]->w;
    m->pos_btn_histoir.h = m->histoir_btn[0]->h;

    m->pos_btn_quit.x = 1150;
    m->pos_btn_quit.y = 600;
    m->pos_btn_quit.w = m->quit_btn[0]->w;
    m->pos_btn_quit.h = m->quit_btn[0]->h;

    // Initialize menu state
    m->buttonon = 0;
    m->GAMEPAGE = 0;
    m->changemenu = 1;
    m->SELECTEDBUT = 0;
    m->sonbref = 0;
    m->window = 0;
    m->volume = 50;

    // Set options menu button positions with increased spacing
    m->positionDIM.x = 300;  // Volume decrease
    m->positionDIM.y = 150;
    m->positionDIM.w = m->DIM1->w;  // Use actual button width
    m->positionDIM.h = m->DIM1->h;  // Use actual button height

    m->positionAUG.x = 750;  // Volume increase
    m->positionAUG.y = 150;
    m->positionAUG.w = m->AUG1->w;
    m->positionAUG.h = m->AUG1->h;

    m->positionFEN.x = 300;  // Window mode
    m->positionFEN.y = 300;
    m->positionFEN.w = m->FEN1->w;
    m->positionFEN.h = m->FEN1->h;

    m->positionPLEIN.x = 750;  // Fullscreen mode
    m->positionPLEIN.y = 300;
    m->positionPLEIN.w = m->PLEIN1->w;
    m->positionPLEIN.h = m->PLEIN1->h;

    m->positionRET.x = 500;   // Return button
    m->positionRET.y = 500;
    m->positionRET.w = m->RET1->w;
    m->positionRET.h = m->RET1->h;

    // Set background position for options menu
    m->pos_options_bg.x = 0;
    m->pos_options_bg.y = 0;
    m->pos_options_bg.w = 1280;  // Match window width
    m->pos_options_bg.h = 720;   // Match window height

    // Initialize high scores
    init_highscores(m);

    // Mark resources as initialized
    resources_initialized = 1;

    // Start playing music with volume control
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2); // Set music volume to 50%
    if(Mix_PlayMusic(m->musique_bg, -1) == -1) {
        printf("Error playing music: %s\n", Mix_GetError());
        cleanup_menu(m);
        Mix_CloseAudio();
        IMG_Quit();
        exit(1);
    }
}

void afficher_menu(Menu m, SDL_Surface *ecran)
{
    if (m.GAMEPAGE == 0) {
        // Display main menu
        SDL_BlitSurface(m.bg_principale, NULL, ecran, NULL);

        // Display main menu buttons based on hover state
        if (m.buttonon == 1) {
            SDL_BlitSurface(m.jouer_btn[1], NULL, ecran, &m.pos_btn_jouer);
        } else {
            SDL_BlitSurface(m.jouer_btn[0], NULL, ecran, &m.pos_btn_jouer);
        }

        if (m.buttonon == 2) {
            SDL_BlitSurface(m.option_btn[1], NULL, ecran, &m.pos_btn_option);
        } else {
            SDL_BlitSurface(m.option_btn[0], NULL, ecran, &m.pos_btn_option);
        }

        if (m.buttonon == 3) {
            SDL_BlitSurface(m.meilleur_btn[1], NULL, ecran, &m.pos_btn_meilleur);
        } else {
            SDL_BlitSurface(m.meilleur_btn[0], NULL, ecran, &m.pos_btn_meilleur);
        }

        if (m.buttonon == 4) {
            SDL_BlitSurface(m.histoir_btn[1], NULL, ecran, &m.pos_btn_histoir);
        } else {
            SDL_BlitSurface(m.histoir_btn[0], NULL, ecran, &m.pos_btn_histoir);
        }

        if (m.buttonon == 5) {
            SDL_BlitSurface(m.quit_btn[1], NULL, ecran, &m.pos_btn_quit);
        } else {
            SDL_BlitSurface(m.quit_btn[0], NULL, ecran, &m.pos_btn_quit);
        }
    } else if (m.GAMEPAGE == 1) {
        // Options menu display
        afficherMENU(&m, ecran);
    } else if (m.GAMEPAGE == 2) {
        // High scores display
        afficher_highscores(&m, ecran);
    }
}

int collision_avec_souris(SDL_Rect pos_btn) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    // Add a small buffer around the button (5 pixels) for better edge detection
    return (x >= pos_btn.x - 5 && 
            x <= pos_btn.x + pos_btn.w + 5 && 
            y >= pos_btn.y - 5 && 
            y <= pos_btn.y + pos_btn.h + 5);
}

void miseajour_menu(Menu *m)
{
    if (m->GAMEPAGE == 0) {
        // Main menu button handling (existing code)
        if (collision_avec_souris(m->pos_btn_jouer)) {
            m->buttonon = 1;
            if (m->SELECTEDBUT != 1) {
                sonbref(m);
                m->SELECTEDBUT = 1;
            }
        } else if (collision_avec_souris(m->pos_btn_option)) {
            m->buttonon = 2;
            if (m->SELECTEDBUT != 2) {
                sonbref(m);
                m->SELECTEDBUT = 2;
            }
        } else if (collision_avec_souris(m->pos_btn_meilleur)) {
            m->buttonon = 3;
            if (m->SELECTEDBUT != 3) {
                sonbref(m);
                m->SELECTEDBUT = 3;
            }
        } else if (collision_avec_souris(m->pos_btn_histoir)) {
            m->buttonon = 4;
            if (m->SELECTEDBUT != 4) {
                sonbref(m);
                m->SELECTEDBUT = 4;
            }
        } else if (collision_avec_souris(m->pos_btn_quit)) {
            m->buttonon = 5;
            if (m->SELECTEDBUT != 5) {
                sonbref(m);
                m->SELECTEDBUT = 5;
            }
        } else {
            m->buttonon = 0;
            m->SELECTEDBUT = 0;
        }
    } else if (m->GAMEPAGE == 1) {
        // Options menu button handling (existing code)
        if (collision_avec_souris(m->positionDIM)) {
            m->buttonon = 1;
            if (m->SELECTEDBUT != 1) {
                sonbref(m);
                m->SELECTEDBUT = 1;
            }
        } else if (collision_avec_souris(m->positionAUG)) {
            m->buttonon = 2;
            if (m->SELECTEDBUT != 2) {
                sonbref(m);
                m->SELECTEDBUT = 2;
            }
        } else if (collision_avec_souris(m->positionFEN)) {
            m->buttonon = 3;
            if (m->SELECTEDBUT != 3) {
                sonbref(m);
                m->SELECTEDBUT = 3;
            }
        } else if (collision_avec_souris(m->positionPLEIN)) {
            m->buttonon = 4;
            if (m->SELECTEDBUT != 4) {
                sonbref(m);
                m->SELECTEDBUT = 4;
            }
        } else if (collision_avec_souris(m->positionRET)) {
            m->buttonon = 5;
            if (m->SELECTEDBUT != 5) {
                sonbref(m);
                m->SELECTEDBUT = 5;
            }
        } else {
            m->buttonon = 0;
            m->SELECTEDBUT = 0;
        }
    } else if (m->GAMEPAGE == 2) {
        // High scores menu button handling
        if (collision_avec_souris(m->pos_btn_retour)) {
            m->buttonon = 5;  // Use 5 to match the return button state
            if (m->SELECTEDBUT != 5) {
                sonbref(m);
                m->SELECTEDBUT = 5;
            }
        } else {
            m->buttonon = 0;
            m->SELECTEDBUT = 0;
        }
    }
}

void sonbref(Menu *menu)
{
    int channel = Mix_PlayChannel(-1, menu->son, 0);
    if (channel != -1) {
        // Set the volume of the hover sound to match the music volume
        Mix_Volume(channel, menu->volume);
    }
}

void handle_options_input(Menu *menu, SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            switch (menu->buttonon) {
                case 1: // Decrease volume
                    menu->volume = (menu->volume > 0) ? menu->volume - 10 : 0;
                    Mix_VolumeMusic(menu->volume);
                    sonbref(menu);
                    break;
                case 2: // Increase volume
                    menu->volume = (menu->volume < 128) ? menu->volume + 10 : 128;
                    Mix_VolumeMusic(menu->volume);
                    sonbref(menu);
                    break;
                case 3: // Window mode
                    menu->window = 0;
                    sonbref(menu);
                    break;
                case 4: // Fullscreen mode
                    menu->window = 1;
                    sonbref(menu);
                    break;
                case 5: // Return to main menu
                    menu->GAMEPAGE = 0;
                    sonbref(menu);
                    break;
            }
        }
    }
}

void afficherMENU(Menu *m, SDL_Surface *ecran) {
    // First blit the background
    SDL_BlitSurface(m->options_bg, NULL, ecran, &m->pos_options_bg);
    
    // Display volume decrease button (DIM) with proper scaling
    SDL_Surface *dimSurface = (m->buttonon == 1) ? m->DIM2 : m->DIM1;
    if (dimSurface) {
        SDL_Rect srcRect = {0, 0, dimSurface->w, dimSurface->h};
        SDL_BlitSurface(dimSurface, &srcRect, ecran, &m->positionDIM);
    }
    
    // Display volume increase button (AUG)
    SDL_Surface *augSurface = (m->buttonon == 2) ? m->AUG2 : m->AUG1;
    if (augSurface) {
        SDL_Rect srcRect = {0, 0, augSurface->w, augSurface->h};
        SDL_BlitSurface(augSurface, &srcRect, ecran, &m->positionAUG);
    }
    
    // Display window mode button (FEN)
    SDL_Surface *fenSurface = (m->buttonon == 3) ? m->FEN2 : m->FEN1;
    if (fenSurface) {
        SDL_Rect srcRect = {0, 0, fenSurface->w, fenSurface->h};
        SDL_BlitSurface(fenSurface, &srcRect, ecran, &m->positionFEN);
    }
    
    // Display fullscreen button (PLEIN)
    SDL_Surface *pleinSurface = (m->buttonon == 4) ? m->PLEIN2 : m->PLEIN1;
    if (pleinSurface) {
        SDL_Rect srcRect = {0, 0, pleinSurface->w, pleinSurface->h};
        SDL_BlitSurface(pleinSurface, &srcRect, ecran, &m->positionPLEIN);
    }
    
    // Display return button (RET)
    SDL_Surface *retSurface = (m->buttonon == 5) ? m->RET2 : m->RET1;
    if (retSurface) {
        SDL_Rect srcRect = {0, 0, retSurface->w, retSurface->h};
        SDL_BlitSurface(retSurface, &srcRect, ecran, &m->positionRET);
    }
}

void MenuINPUTS(Menu *menu, SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            // Play hover sound effect for any button click
            Mix_PlayChannel(-1, menu->son, 0);
            
            switch (menu->buttonon) {
                case 1: // Diminuer (Decrease volume)
                    menu->volume = (menu->volume > 0) ? menu->volume - 10 : 0;
                    Mix_VolumeMusic(menu->volume);
                    break;
                    
                case 2: // Augmenter (Increase volume)
                    menu->volume = (menu->volume < 128) ? menu->volume + 10 : 128;
                    Mix_VolumeMusic(menu->volume);
                    break;
                    
                case 3: // Fenetre (Windowed mode)
                    menu->window = 0;
                    menu->ecran = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                    if (!menu->ecran) {
                        printf("Error setting windowed mode: %s\n", SDL_GetError());
                    }
                    break;
                    
                case 4: // Plein ecran (Fullscreen mode)
                    menu->window = 1;
                    menu->ecran = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                    if (!menu->ecran) {
                        printf("Error setting fullscreen mode: %s\n", SDL_GetError());
                    }
                    break;
                    
                case 5: // Retour (Return to main menu)
                    menu->GAMEPAGE = 0;
                    break;
            }
        }
    }
}

void init_highscores(Menu *m) {
    // Initialize TTF if not already initialized
    if (!TTF_WasInit() && TTF_Init() == -1) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    // Initialize font for score display
    m->score_font = TTF_OpenFont("fonts/arial.ttf", 28);
    if (!m->score_font) {
        printf("Error loading font: %s\n", TTF_GetError());
        return;
    }

    // Use the same background as options menu
    m->highscores_bg = m->options_bg;

    // Set high scores background position
    m->pos_highscores_bg.x = 0;
    m->pos_highscores_bg.y = 0;
    m->pos_highscores_bg.w = 1280;  // Match window width
    m->pos_highscores_bg.h = 720;   // Match window height

    // Use the same return button as options menu
    m->retour_btn[0] = m->RET1;
    m->retour_btn[1] = m->RET2;

    // Use the same return button position as options menu
    m->pos_btn_retour = m->positionRET;

    // Initialize score positions with better spacing and centering
    for (int i = 0; i < MAX_SCORES; i++) {
        m->score_positions[i].x = 440;  // Centered horizontally
        m->score_positions[i].y = 200 + (i * 120);  // More vertical spacing
    }

    // Initialize score surfaces array
    for (int i = 0; i < MAX_SCORES; i++) {
        m->score_surfaces[i] = NULL;
    }

    // Load existing high scores
    load_highscores(m);
}

void load_highscores(Menu *m) {
    FILE *file = fopen("scores.dat", "rb");
    if (!file) {
        // Initialize with default values if file doesn't exist
        for (int i = 0; i < MAX_SCORES; i++) {
            m->top_scores[i].score = 0;
            strcpy(m->top_scores[i].name, "---");
        }
        return;
    }

    fread(m->top_scores, sizeof(HighScore), MAX_SCORES, file);
    fclose(file);
}

void save_highscores(Menu *m) {
    FILE *file = fopen("scores.dat", "wb");
    if (!file) {
        printf("Error saving high scores\n");
        return;
    }

    fwrite(m->top_scores, sizeof(HighScore), MAX_SCORES, file);
    fclose(file);
}

void add_highscore(Menu *m, int score, const char *name) {
    // Find position for new score
    int pos = -1;
    for (int i = 0; i < MAX_SCORES; i++) {
        if (score > m->top_scores[i].score) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        // Shift lower scores down
        for (int i = MAX_SCORES - 1; i > pos; i--) {
            m->top_scores[i] = m->top_scores[i-1];
        }

        // Insert new score
        m->top_scores[pos].score = score;
        strncpy(m->top_scores[pos].name, name, 49);
        m->top_scores[pos].name[49] = '\0';

        // Save updated scores
        save_highscores(m);
    }
}

void afficher_highscores(Menu *m, SDL_Surface *ecran) {
    // Display background
    SDL_BlitSurface(m->highscores_bg, NULL, ecran, &m->pos_highscores_bg);

    // Display title
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *title = TTF_RenderText_Blended(m->score_font, "MEILLEURS SCORES", white);
    if (title) {
        SDL_Rect title_pos = {440, 100, 0, 0};
        SDL_BlitSurface(title, NULL, ecran, &title_pos);
        SDL_FreeSurface(title);
    }

    // Display scores with properly initialized SDL_Color structs
    SDL_Color gold = {255, 215, 0, 255};    // Added alpha value
    SDL_Color silver = {192, 192, 192, 255}; // Added alpha value
    SDL_Color bronze = {205, 127, 50, 255};  // Added alpha value
    SDL_Color colors[MAX_SCORES] = {gold, silver, bronze};

    char score_text[100];
    for (int i = 0; i < MAX_SCORES; i++) {
        snprintf(score_text, sizeof(score_text), "%d. %s: %d", i+1, m->top_scores[i].name, m->top_scores[i].score);
        
        // Free previous surface if it exists
        if (m->score_surfaces[i]) {
            SDL_FreeSurface(m->score_surfaces[i]);
        }
        
        m->score_surfaces[i] = TTF_RenderText_Blended(m->score_font, score_text, colors[i]);
        if (m->score_surfaces[i]) {
            SDL_BlitSurface(m->score_surfaces[i], NULL, ecran, &m->score_positions[i]);
        }
    }

    // Display return button using the same logic as options menu
    if (m->buttonon == 5) {
        SDL_BlitSurface(m->RET2, NULL, ecran, &m->positionRET);
    } else {
        SDL_BlitSurface(m->RET1, NULL, ecran, &m->positionRET);
    }
}

void cleanup_highscores(Menu *m) {
    // Free font
    if (m->score_font) {
        TTF_CloseFont(m->score_font);
        m->score_font = NULL;
    }

    // Don't free highscores_bg as it's the same as options_bg
    // Don't free return buttons as they're shared with options menu

    for (int i = 0; i < MAX_SCORES; i++) {
        if (m->score_surfaces[i]) {
            SDL_FreeSurface(m->score_surfaces[i]);
            m->score_surfaces[i] = NULL;
        }
    }
} 
