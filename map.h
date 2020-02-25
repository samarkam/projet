/*
fctmap.h
--------

par vianel99, pour le projet de fin de Semestre

Rôle: Prototypes des fonctions de fmap.c

Date de creation: 05/02/2020 01h49

Dernière modification: 05/02/2019
*/

#ifndef FCTMAP_H_INCLUDED
#define FCTMAP_H_INCLUDED

	#include "constantes.h"

	Map* fctmap_chargerMap(const char* level, int largeur_fenetre, int hauteur_fenetre);
	int fctmap_libererMap(Map* carte);
	int fctmap_saveMap(const char* fich, Map* carte);
	int fctmap_resizeMap(Map* carte, int newtaillex, int newtailley);
	Map* fctmap_newMap(const char* tileset, int nbTilex, int nbTiley, int nbtile_LargeurMonde, int nbtile_HauteurMonde);
	void fctmap_moveMap(Input* in, Map* carte);
	int fctmap_afficherMap(Map* carte, SDL_Surface* ecran);

#endif