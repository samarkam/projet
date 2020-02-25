/*
main.c
------

par vianel99, pour le projet de fin de Semestre

Rôle: Son rôle est d'implementer les fonctions princiales du programme

Date de creation: 05/02/2020 02h17

Dernière modification: 05/02/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "init.h"
#include "jeu.h"
#include "editeur.h"
#include "interface.h"
#include "fctmap.h"
#include "fctevent.h"

int main( int argc, char *argv[])
{
	SDL_Surface *ecran = NULL, *title = NULL; 
	SDL_Event event;
	char **tab;
	int nb;
	Preference pref = init_loadPreferencesUser("fichiers/others/preferences.txt");
	printf("%d %d %d %d %d\n", pref.etatmus, pref.lang, pref.etatsons, pref.nivmus, pref.nivsons);	
	Input in;
	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	// Initialisation de SDL_ttf
	if(TTF_Init() == -1)
		init_errorQuit("Erreur d'initialisation de TTF_Init");
	// Initialisation de SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		init_errorQuit("Erreur d'initialisation de SDL_mixer\n");	
	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(ecran == NULL)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	Mix_AllocateChannels(10);
	SDL_WarpMouse(ecran->w / 2, ecran->h / 2);
	tab = init_languageRessources(&pref);
	fctevent_init_Events(&in);
	interface_pageMenu(ecran, in, tab, &pref);	
	printf("\nici\n");
	init_savePreferencesUser(&pref, "fichiers/others/preferences.txt");
	nb = sizeof(tab) / sizeof(char*);
	for(int i = 0; i < nb; i++)
		free(tab[i]);
	free(tab);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}