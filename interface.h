/*
interface.h
-----------

par vianel99, pour le projet de fin de Semestre

Rôle: Ce fichier contient toutes les fonctions relatives à l'affichage de page poussant l'utilisateur à faire des choix;
	> page d'acceuil du jeu etc.

Date de creation: 05/02/2020 01h49

Dernière modification: 05/02/2019
*/

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

	#include "constantes.h"

	void interface_pageMenu(SDL_Surface* ecran, Input in, char** tab, Preference* pref);

#endif