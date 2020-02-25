/*
interface.c
-----------

par vianel99, pour le projet de fin de Semestre

Rôle: afficher des pages où l'utlisateur est appelé à faire des choix;

Date de creation: 05/02/2020 01h49

Dernière modification: 11/02/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "constantes.h"
#include "interface.h"
#include "init.h"
#include "fctevent.h"
#include "jeu.h"

void interface_posElementsJouer(ContextMenu* cmenu)
{

}

void interface_pageJouer(SDL_Surface* ecran, Input* in, ContextMenu* cmenu, char** tab, Preference* pref)
{

}

void interface_posElementsStat(ContextMenu* cmenu)
{

}

void interface_pageStat(SDL_Surface* ecran, Input* in, ContextMenu* cmenu, char** tab, Preference* pref)
{
	interface_posElementsStat(cmenu);

	while(!in->quit && !in->key[SDLK_ESCAPE])
	{

	}
}

void interface_posElementsMenu(ContextMenu* cmenu)
{
	int i;

	// Jouer la musique
	Mix_PlayMusic(cmenu->music, -1);

	// -->Background
	cmenu->bg.pos.x = 0;
	cmenu->bg.pos.y = 0;		
	// --> titre
	cmenu->butt[1].pos.x = LARGEUR_FENETRE - LARGEUR_FENETRE / 1.6;
	cmenu->butt[1].pos.y = HAUTEUR_FENETRE / 5.3;	
	SDL_SetAlpha(cmenu->butt[1].img[0], SDL_SRCALPHA, 128); // Transparence alpha du titre
	// --> Mascotte
	cmenu->butt[2].pos.x = (LARGEUR_FENETRE / 1.4 - cmenu->butt[2].img[0]->h / 2) ;
	cmenu->butt[2].pos.y = cmenu->butt[1].pos.y - 10;
	// --> Copyright
	cmenu->butt[6].pos.x = (LARGEUR_FENETRE / 1.3 - cmenu->butt[2].img[0]->h / 2) ;
	cmenu->butt[6].pos.y = HAUTEUR_FENETRE - cmenu->butt[6].img[0]->h - 14;
	// --> Rectangle
	cmenu->butt[0].pos.x = LARGEUR_FENETRE / 10;
	cmenu->butt[0].pos.y = HAUTEUR_FENETRE / 5,5;
	for(i = TMENU; i < TMENU + 5; i++)
	{
		cmenu->butt[i].pos.x = (cmenu->butt[0].pos.x + cmenu->butt[0].img[0]->w / 2) - (cmenu->butt[i].img[0]->w / 2);
		cmenu->butt[i].pos.y = (cmenu->butt[0].pos.y + cmenu->butt[0].img[0]->h / 2) - (cmenu->butt[i].img[0]->h / 2);
		cmenu->butt[0].pos.y += 83;
	}
	cmenu->butt[0].pos.y = HAUTEUR_FENETRE / 5,5;
	// --> Selec
	cmenu->butt[7].pos.x = 7;
	cmenu->butt[7].pos.y = cmenu->butt[0].pos.y - 70;

	for(i = 3; i < 6; i++)
	{
		cmenu->butt[i].pos.x = LARGEUR_FENETRE / 2;
		cmenu->butt[i].pos.y = HAUTEUR_FENETRE / 2;
	}

	SDL_SetAlpha(cmenu->butt[3].img[0], SDL_SRCALPHA, 128);
	SDL_SetAlpha(cmenu->butt[4].img[0], SDL_SRCALPHA, 128);
	SDL_SetAlpha(cmenu->butt[5].img[0], SDL_SRCALPHA, 128);
}

int* interface_posElementsReglages(ContextMenu* cmenu, Preference* pref)
{
	int i, *test;
	test = malloc(sizeof(int) * 5);
	// Definition des elemnts	
	cmenu->butt[TMENU + 5].pos.x = LARGEUR_FENETRE / 2 - cmenu->butt[TMENU + 5].img[0]->w / 2;
	cmenu->butt[TMENU + 5].pos.y = 20 + 130;
	cmenu->butt[TMENU + 6].pos.y = cmenu->butt[TMENU + 5].pos.y;
	cmenu->butt[TMENU + 6].pos.x = LARGEUR_FENETRE / 2 - cmenu->butt[TMENU + 6].img[0]->w / 2;	

	test[0] = TMENU + 5;
	test[1] = TMENU + 7;
	if(pref->etatmus)
		test[2] = TMENU + 8;
	else
		test[2] = TMENU + 9;
	if(pref->etatsons)
		test[3] = TMENU + 10;
	else
		test[3] = TMENU + 11;
	test[4] = TMENU + 12;
	test[5] = TMENU + 13;

	// langue
	cmenu->butt[TMENU + 7].pos.y = cmenu->butt[TMENU + 5].pos.y + (80);
	cmenu->butt[TMENU + 7].pos.x = LARGEUR_FENETRE / 2 - cmenu->butt[TMENU + 7].img[0]->w / 2;
	// la musique
	cmenu->butt[TMENU + 9].pos.y = cmenu->butt[TMENU + 5].pos.y + (2 * 80);
	cmenu->butt[TMENU + 9].pos.x = LARGEUR_FENETRE / 2 - cmenu->butt[TMENU + 9].img[0]->w / 2;
	cmenu->butt[TMENU + 8].pos.y = cmenu->butt[TMENU + 5].pos.y + (2 * 80);
	cmenu->butt[TMENU + 8].pos.x = LARGEUR_FENETRE / 2 - cmenu->butt[TMENU + 8].img[0]->w / 2;
	// le son
	cmenu->butt[TMENU + 10].pos.y = cmenu->butt[TMENU + 5].pos.y + (3 * 80);
	cmenu->butt[TMENU + 10].pos.x = LARGEUR_FENETRE / 2 - cmenu->butt[TMENU + 10].img[0]->w / 2;
	cmenu->butt[TMENU + 11].pos.y = cmenu->butt[TMENU + 5].pos.y + (3 * 80);
	cmenu->butt[TMENU + 11].pos.x = LARGEUR_FENETRE / 2 - cmenu->butt[TMENU + 11].img[0]->w / 2;
	// dernier
	cmenu->butt[TMENU + 12].pos.y = cmenu->butt[TMENU + 5].pos.y + (4 * 80);
	cmenu->butt[TMENU + 12].pos.x = LARGEUR_FENETRE / 2 - cmenu->butt[TMENU + 12].img[0]->w / 2;
	// Back to main menu
	cmenu->butt[0].pos.x = 20;
	cmenu->butt[0].pos.y = 20;
	cmenu->butt[TMENU + 13].pos.x = (cmenu->butt[0].pos.x + cmenu->butt[0].img[0]->w / 2) - (cmenu->butt[TMENU + 13].img[0]->w / 2);
	cmenu->butt[TMENU + 13].pos.y = (cmenu->butt[0].pos.y + cmenu->butt[0].img[0]->h / 2) - (cmenu->butt[TMENU + 13].img[0]->h / 2);
	
	return test;
}

char** interface_pageReglages(SDL_Surface* ecran, Input* in, ContextMenu* cmenu, char** tab, Preference* pref)
{
	SDL_Surface *reglages, *ancecran, *imgvolmus = NULL;
	SDL_Rect posregl, posvolmus;
	int i, clic = 0, OK = 0, *test, nb, tapres, tavant = 0;
	char volmus[4];
	TTF_Font *police;
	SDL_Color color = {30, 100, 255};
	police = TTF_OpenFont("fonts/ALBA.TTF", 70);
	reglages = TTF_RenderText_Blended(police, tab[2], color);
	TTF_CloseFont(police);
	police = TTF_OpenFont("fonts/ALBA.TTF", 35);
	posregl.x = LARGEUR_FENETRE / 2 - reglages->w / 2;
	posregl.y = 20;
	test = interface_posElementsReglages(cmenu, pref);

	posvolmus = cmenu->butt[TMENU + 8].pos;
	posvolmus.x += cmenu->butt[TMENU + 9].img[1]->w + 15;
	posvolmus.y -= 8;

	while(!in->quit && !in->key[SDLK_ESCAPE])
	{
		fctevent_updateEvents(in);	
		if(in->key[SDLK_RETURN])
		{
			clic = 1;
			in->key[SDLK_RETURN] = 0;
		}
		if(!in->key[SDLK_UP] && !in->key[SDLK_DOWN] && !in->key[SDLK_RETURN])
		{
			// Evenement Souris
			for(i = 0; i < 6; i++)
			{
				if((in->mousex > cmenu->butt[test[i]].pos.x && in->mousex < (cmenu->butt[test[i]].pos.x + cmenu->butt[test[i]].img[0]->w)) && 
				(in->mousey > cmenu->butt[test[i]].pos.y && in->mousey < (cmenu->butt[test[i]].pos.y + cmenu->butt[test[i]].img[0]->h)))
				{
					OK = i;
					Mix_PlayChannel(1, cmenu->son[0], 0);
					if(in->mousebuttons[SDL_BUTTON_LEFT])
					{
						clic = 1;
						in->mousebuttons[SDL_BUTTON_LEFT] = 0;
					}
				}
				cmenu->butt[test[i]].focus = 0;
			}
		}
		else
			Mix_PlayChannel(1, cmenu->son[0], 0);

		// On efface l'ecran
		SDL_BlitSurface(cmenu->bg.img[0], NULL, ecran, &cmenu->bg.pos);
		SDL_BlitSurface(reglages, NULL, ecran, &posregl);	

		//cmenu->butt[test[OK]].focus = 0;			
		if(in->key[SDLK_UP])
		{
			if(OK > 0)
				OK-- ;
			else
				OK = 5;	
			in->key[SDLK_UP] = 0;				
		}
		if(in->key[SDLK_DOWN])
		{				
			if(OK < 5)
				OK++ ;
			else
				OK = 0;
			in->key[SDLK_DOWN] = 0;
		}
		cmenu->butt[test[OK]].focus = 1;

		SDL_BlitSurface(cmenu->butt[0].img[0], NULL, ecran, &cmenu->butt[0].pos); 
		for(i = 0; i < 6; i++)
		{
			if(cmenu->butt[test[i]].focus)
			{				
				if(clic)
				{
					switch(test[i])
					{
						case TMENU + 5:
							ancecran = ecran;
							SDL_FreeSurface(ancecran);
							ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
							SDL_Delay(1000);
							test[i] = TMENU + 6;
							break;
						case TMENU + 6:
							ancecran = ecran;
							SDL_FreeSurface(ancecran);
							ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
							SDL_Delay(1000);
							test[i] = TMENU + 5;
							break;
						case TMENU + 7:
							init_libererContextMenu(cmenu);
							nb = sizeof(tab) / sizeof(char*);
							for(int i = 0; i < nb; i++)
								free(tab[i]);
							free(tab);
							if(pref->lang == 1)
							{
								tab = init_loadRessources("fichiers/languages/en_EN.res");
								pref->lang = 0;
							}
							else
							{
								tab = init_loadRessources("fichiers/languages/fr_FR.res");
								pref->lang = 1;
							}				
							/*for(i = 0; i < 11; i++)
								printf("%d) %s\n", i, tab[i]);*/
							*cmenu = init_loadContextMenu(tab);
							SDL_Delay(500);	
							TTF_Font *police;
							SDL_Color color = {30, 100, 255};
							police = TTF_OpenFont("fonts/ALBA.TTF", 70);
							reglages = TTF_RenderText_Blended(police, tab[2], color);
							TTF_CloseFont(police);
							posregl.x = LARGEUR_FENETRE / 2 - reglages->w / 2;
							posregl.y = 20;	
							test = interface_posElementsReglages(cmenu, pref);	
							interface_posElementsMenu(cmenu);	
							cmenu->butt[0].pos.x = 20;
							cmenu->butt[0].pos.y = 20;			
							break;
						case TMENU + 8:
							Mix_PauseMusic();
							test[i] = TMENU + 9;
							pref->etatmus = 0;
							break;
						case TMENU + 9:
							Mix_ResumeMusic();
							test[i] = TMENU + 8;
							pref->etatmus = 1;
							Mix_VolumeMusic(pref->nivmus);
							break;
						case TMENU + 10:
							Mix_Volume(-1, 0);
							Mix_HaltChannel(-1);
							test[i] = TMENU + 11;
							pref->etatsons = 0;
							break;
						case TMENU + 11:
							Mix_Volume(-1, pref->nivsons);
							test[i] = TMENU + 10;
							pref->etatsons = 1;
							break;
						case TMENU + 12:
							break;
						case TMENU + 13:
							in->key[SDLK_ESCAPE] = 1;
							break;
					}
					clic = 0;
				}
				tapres = SDL_GetTicks();
				if(test[i] == TMENU + 8 && (in->key[SDLK_LEFT] || in->key[SDLK_RIGHT]))
				{
					if(in->key[SDLK_LEFT])
					{
						if(pref->nivmus > 0 && tapres - tavant > 10)
							pref->nivmus--;
						sprintf(volmus, "%d%%", pref->nivmus);
					}
					else
					{
						if(pref->nivmus < 100 && tapres - tavant > 10)
							pref->nivmus++;
						sprintf(volmus, "%d%%", pref->nivmus);
					}
					imgvolmus = TTF_RenderUTF8_Blended(police, volmus, color);					
					tavant = tapres;
					Mix_VolumeMusic(pref->nivmus);
				}	
				if(test[2] != TMENU + 9)
					SDL_BlitSurface(imgvolmus, NULL, ecran, &posvolmus);
				SDL_BlitSurface(cmenu->butt[test[i]].img[1], NULL, ecran, &cmenu->butt[test[i]].pos);				
			}
			else
				SDL_BlitSurface(cmenu->butt[test[i]].img[0], NULL, ecran, &cmenu->butt[test[i]].pos);		
		}
		SDL_Flip(ecran);
	}
	// Liberation de la memoire
	SDL_FreeSurface(reglages);
	SDL_FreeSurface(imgvolmus);

	TTF_CloseFont(police);

	free(test);
	cmenu->butt[0].pos.x = HAUTEUR_FENETRE / 5,5;

	return tab;
}

Uint32 avancerVent(Uint32 intervalle, void* position)
{
	SDL_Rect* pos = position;
	int i = (int) (rand() % 14);
	pos->x -= i;
	return intervalle;
}

Uint32 avancerVent1(Uint32 intervalle, void* position)
{
	SDL_Rect* pos = position;
	int i = (int) (rand() % 12) + 2;
	pos->x -= i;
	return intervalle;
}

Uint32 avancerVent2(Uint32 intervalle, void* position)
{
	SDL_Rect* pos = position;
	int i = (int) (rand() % 10) + 4;
	pos->x -= i;
	return intervalle;
}

void interface_pageMenu(SDL_Surface* ecran, Input in, char** tab, Preference* pref)
{
	SDL_Surface *imgbg = NULL;
	SDL_Rect destVent[3];
	ContextMenu cmenu = init_loadContextMenu(tab);

	SDL_TimerID timer;
	SDL_TimerID timerVent[3];

	int i, OK = TMENU, clic = 0, flou = 100, inter, trans[3] = {100};
	int tecran = 0, tavant = 0, tapres;

	interface_posElementsMenu(&cmenu);
	fctevent_init_Events(&in);	
	srand((unsigned int) time (NULL));

	if(!pref->etatmus)
		Mix_VolumeMusic(0);
	// les sons
	if(!pref->etatsons)
	{
		Mix_Volume(-1, 0);
		Mix_HaltChannel(-1);
	}
	

	for(i = 3; i < 6; i++)
	{
		destVent[i - 3] = cmenu.butt[i].pos;
		destVent[i - 3].h = cmenu.butt[i].img[0]->h;
	}
	imgbg = cmenu.bg.img[0];

	timerVent[0] = SDL_AddTimer(10, avancerVent, &destVent[0]);
	timerVent[1] = SDL_AddTimer(20, avancerVent1, &destVent[1]);
	timerVent[2] = SDL_AddTimer(15, avancerVent2, &destVent[2]);

	do
	{
		fctevent_updateEvents(&in);	
		if(in.key[SDLK_RETURN])
		{
			clic = 1;
			in.key[SDLK_RETURN] = 0;	
		}
		if(!in.key[SDLK_UP] && !in.key[SDLK_DOWN] && !in.key[SDLK_RETURN])
		{
			// Evenement Souris
			cmenu.butt[0].pos.y = HAUTEUR_FENETRE / 5,5;
			for(i = TMENU; i < TMENU + 5; i++)
			{
				if((in.mousex > cmenu.butt[0].pos.x && in.mousex < (cmenu.butt[0].pos.x + cmenu.butt[0].img[0]->w)) && 
				(in.mousey > cmenu.butt[0].pos.y && in.mousey < (cmenu.butt[0].pos.y + cmenu.butt[0].img[0]->h)))
				{
					Mix_PlayChannel(1, cmenu.son[0], 0);
					OK = i;					
					if(in.mousebuttons[SDL_BUTTON_LEFT])
						clic = 1;
				}
				cmenu.butt[i].focus = 0;
				cmenu.butt[0].pos.y += 83;
			}
		}
		else
			Mix_PlayChannel(1, cmenu.son[0], 0);

		tapres = SDL_GetTicks();
		// On efface l'ecran
		if((imgbg == cmenu.bg.img[0]) && (tapres - tavant > 1000))
		{
			tavant = tapres;
			imgbg = cmenu.bg.img[1];
		}
		else if((imgbg == cmenu.bg.img[1]) && (tapres - tavant > 1000))
		{
			tavant = tapres;
			imgbg = cmenu.bg.img[0];
		}
		SDL_BlitSurface(imgbg, NULL, ecran, &cmenu.bg.pos);

		//vent
		for(i = 3; i < 6; i++)
		{
			if(cmenu.butt[i].pos.x < 5 && destVent[i - 3].w > 0)
				cmenu.butt[i].pos.w = cmenu.butt[i].img[0]->w - destVent[i - 3].x;	
				cmenu.butt[i].pos.x = destVent[i - 3].x;		
				 cmenu.butt[i].pos.y = destVent[i - 3].y;
			 if(destVent[i - 3].x + cmenu.butt[i].img[0]->w < 0)
			{
				destVent[i - 3].x = LARGEUR_FENETRE - 10;
				destVent[i - 3].y = (int) (rand() % (HAUTEUR_FENETRE)) + 100;
				cmenu.butt[i].pos.w = cmenu.butt[i].img[0]->w;
				trans[i - 3] = flou - (i*10 + 60);
			}
			SDL_BlitSurface(cmenu.butt[i].img[0], NULL, ecran, &cmenu.butt[i].pos);
			SDL_SetAlpha(cmenu.butt[i].img[0], SDL_SRCALPHA, trans[i - 3]); 
		}

		tapres = SDL_GetTicks();

		// On efface l'ecran
		if((flou < 255) && (tapres - tecran > 80))
		{
			flou++;
		}
		else if(flou > 0)
		{
			flou--;
			tecran = tapres;
		}
		// On blitte les surfaces à l'écran	
		SDL_BlitSurface(cmenu.butt[1].img[0], NULL, ecran, &cmenu.butt[1].pos);
		SDL_SetAlpha(cmenu.butt[1].img[0], SDL_SRCALPHA, flou); // Transparence alpha du titre
		SDL_BlitSurface(cmenu.butt[2].img[0], NULL, ecran, &cmenu.butt[2].pos);		

		SDL_BlitSurface(cmenu.butt[6].img[0], NULL, ecran, &cmenu.butt[6].pos);

		// On blitte les text à l'écran			
		if(in.key[SDLK_UP])
		{
			if(OK > TMENU)
				OK-- ;
			else
				OK = TMENU + 5 - 1;	
			in.key[SDLK_UP] = 0;				
		}
		if(in.key[SDLK_DOWN])
		{				
			if(OK < TMENU + 5 - 1)
				OK++ ;
			else
				OK = TMENU;
			in.key[SDLK_DOWN] = 0;
		}
		cmenu.butt[OK].focus = 1;

		cmenu.butt[0].pos.y = HAUTEUR_FENETRE / 5,5;
		for(i = TMENU; i < TMENU + 5; i++)
		{
			if(cmenu.butt[i].focus)
			{
				SDL_BlitSurface(cmenu.butt[0].img[0], NULL, ecran, &cmenu.butt[0].pos);
				SDL_BlitSurface(cmenu.butt[i].img[1], NULL, ecran, &cmenu.butt[i].pos);
				// Selec
				cmenu.butt[7].pos.y = cmenu.butt[0].pos.y - 60;
				SDL_BlitSurface(cmenu.butt[7].img[0], NULL, ecran, &cmenu.butt[7].pos);								
			}
			else
			{
				SDL_BlitSurface(cmenu.butt[0].img[1], NULL, ecran, &cmenu.butt[0].pos);
				SDL_BlitSurface(cmenu.butt[i].img[0], NULL, ecran, &cmenu.butt[i].pos);		
			}
			cmenu.butt[0].pos.y += 83;
		} 

		if(clic)
		{
			Mix_PlayChannel(2, cmenu.son[1], 0);
			switch(OK)
			{
			case TMENU:
				jeu(ecran, &in);
				in.key[SDLK_ESCAPE] = 0;
				break;
			case TMENU + 1:
				break;
			case TMENU + 2:
				tab = interface_pageReglages(ecran, &in, &cmenu, tab, pref);
				in.key[SDLK_ESCAPE] = 0;
				imgbg = cmenu.bg.img[0];
				break;
			case TMENU + 3:				
				break;
			case TMENU + 4:	
				in.quit = 1;						
				break;
			}
			clic = 0;
		}
		SDL_Flip(ecran);
	}
	while(!in.quit && !in.key[SDLK_ESCAPE]);

	// Retrait du timer ID
	for(i = 0; i < 3; i++)
		SDL_RemoveTimer(timerVent[i]);
	SDL_FreeSurface(imgbg);
	printf("\nici1\n");

	init_libererContextMenu(&cmenu);
}