/*
afficher.c
----------

par vianel99, pour le projet de fin de Semestre

Rôle: Son rôle est d'afficher des choses à l'ecran :) comme son nom l'indique ;)

Date de creation: 05/02/2020 10h16

Dernière modification: 05/02/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"

// affichage de notre Map à l'écran
int afficher_Map(Map* carte, SDL_Surface* ecran)
{
	int i, j;
	SDL_Rect rect_Dest;
	int numtile;
	int miny, maxy, minx, maxx; // variable permettant de restreindre le calcul des tiles au tile present sur la fenetre

	// définition des tiles à afficher
	minx = carte->scrollx / carte->LARGEUR_TILE - 1;
	miny = carte->scrolly / carte->HAUTEUR_TILE -1;
	maxx = (carte->scrollx + carte->largeur_fenetre) / carte->LARGEUR_TILE;
	maxy = (carte->scrolly + carte->hauteur_fenetre) / carte->HAUTEUR_TILE;

	// Parcour les tiles à aficher et les affiches et ignore ceux qui ne sont pas affichable
	for(i = minx; i < maxx; i++) 
	{
		for(j = miny; j < maxy; j++)
		{
			rect_Dest.x = i * carte->LARGEUR_TILE - carte->scrollx;
			rect_Dest.y = j * carte->HAUTEUR_TILE - carte->scrolly;

			// On verifie si nous sommes arrivés à la fin de la carte
			if(i < 0 || i >= carte->nbtile_LargeurMonde || j<0 || j >= carte->nbtile_HauteurMonde) 
				numtile = 0;
			else
				numtile = carte->shema[i][j];
			SDL_BlitSurface(carte->tileset, &(carte->props[numtile].rectangle), ecran, &rect_Dest);
		}
	}

	return 0;
}
