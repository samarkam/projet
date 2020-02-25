/*
fctevent.c
----------

par vianel99, pour le projet de fin de Semestre

Rôle: Son rôle est de gérer les évenements généré par l'utilisateur

Date de creation: 05/02/2020 11h31

Dernière modification: 05/02/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "fctevent.h"

// permet de mettre à jour les évenements générés
void fctevent_updateEvents(Input* in)
{
	SDL_Event event;
	in->mousebuttons[SDL_BUTTON_WHEELUP] = 0; 
	in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				in->quit = 1;
				break;
			case SDL_KEYDOWN:
				in->key[event.key.keysym.sym] = 1;
				break;
			case SDL_KEYUP:
				in->key[event.key.keysym.sym] = 0;
				break;
			case SDL_MOUSEMOTION:
				in->mousex = event.motion.x;
				in->mousey = event.motion.y;
				in->mouserelx = event.motion.xrel;
				in->mouserely = event.motion.yrel;
				break;
			case SDL_MOUSEBUTTONDOWN:
				in->mousebuttons[event.button.button] = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button != SDL_BUTTON_WHEELDOWN && event.button.button != SDL_BUTTON_WHEELUP)
					in->mousebuttons[event.button.button] = 0;
				break;
		}
	}
}

// initialise tous les champs d'une variable input à 0
void fctevent_init_Events(Input* in)
{
	memset(in, 0, sizeof(Input)); //initialise tout les champs de la variable in à 0
}