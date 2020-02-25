/*
interface.h
-----------

par vianel99, pour le projet de fin de Semestre

Rôle: Son rôle est de gérer les différents niveaux (C'est-à-dire une partie de jeu)

Date de creation: 05/02/2020 01h49

Dernière modification: 05/02/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "jeu.h"
#include "fctmap.h"
#include "fctevent.h"

// Gestion des colisions
bool jeu_collisionAABB(SDL_Rect* box1, SDL_Rect* box2) // Collision par boite englobante
{
	return ((box2->x > box1->x + box1->w) 
			|| (box2->x + box2->w < box1->x) 
			|| (box2->y < box1->y + box1->h) 
			|| (box2->y + box2->h > box1->y))? FALSE : TRUE;
}

void jeu(SDL_Surface* ecran, Input* in)
{
	Map* carte;
	fctevent_init_Events(in);
	carte = fctmap_chargerMap("fichiers/levels/level2.txt", LARGEUR_FENETRE, HAUTEUR_FENETRE);
	fctmap_afficherMap(carte, ecran);
	SDL_Flip(ecran);

	SDL_Delay(20);

	while(!in->quit && !in->key[SDLK_ESCAPE])
	{
		fctevent_updateEvents(in);		
		fctmap_moveMap(in, carte);
		fctmap_afficherMap(carte, ecran);		
		SDL_Flip(ecran);
		SDL_Delay(5);
	}	
	fctmap_libererMap(carte);
}
	