/*
afficher.c
----------

par vianel99, pour le projet de fin de Semestre

Rôle: Contient les prototypes des fonctions du fichiers afficher.c

Date de creation: 05/02/2020 10h16

Dernière modification: 05/02/2019
*/

#ifndef AFFICHER_H_INCLUDED
#define AFFICHER_H_INCLUDED

	#include "constantes.h"

	Map* affihcer_chargerMap(const char* level, int largeur_fenetre, int hauteur_fenetre);
	int afficher_Map(Map* carte, SDL_Surface* ecran);
	int afficher_libererMap(Map* carte);

#endif