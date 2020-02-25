/*
fctmap.c
--------

par vianel99, pour le projet de fin de Semestre

Rôle: Gere toutes les fonctions relative à la creation d'une map

Date de creation: 05/02/2020 01h49

Dernière modification: 05/02/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "init.h"



// determine la taile d'une tile et et sa position
void fctmap_buildTileset(FILE* F, Map* carte)
{
	int numtile, i, j;	
	char buf[FCTMAP_CACHE_SIZE];
	char buf2[FCTMAP_CACHE_SIZE];

	 // petit calcul mathematique :) **;)  on determine la taille d'une tile puisqu'il ont tous les memes dimensions
	carte->LARGEUR_TILE = carte->tileset->w / carte->nbTilex;
	carte->HAUTEUR_TILE = carte->tileset->h / carte->nbTiley; 
	carte->props = malloc(carte->nbTilex * carte->nbTiley * sizeof(Tileprop));

	// On calcule une fois la taille des images à recuperer par notre rectangle et leur position sur la spritesheet
	for(j = 0, numtile = 0; j < carte->nbTiley; j++) 
	{
		for(i = 0; i < carte->nbTilex; i++, numtile++)
		{
			carte->props[numtile].rect.w = carte->LARGEUR_TILE;
			carte->props[numtile].rect.h = carte->HAUTEUR_TILE;
			carte->props[numtile].rect.x = i * carte->LARGEUR_TILE;
			carte->props[numtile].rect.y = j * carte->HAUTEUR_TILE;
			fscanf(F, "%s %s", buf, buf2); // recuperer l'information sur l'aspect du tile "Plein ou vide"
			carte->props[numtile].plein = 0;
			if(strcmp(buf2, "plein") == 0)
				carte->props[numtile].plein = 1;
		}
	}
}

// permet de charger le nombre de sprite et leur caracteristique 
void fctmap_chargerMap_tileset(FILE* F, Map* carte)
{
	char buf[FCTMAP_CACHE_SIZE];
	fscanf(F, "%s", buf); // #tileset
	fscanf(F, "%s", buf); // buf recupere le nom du fichier image
	strcpy(carte->tilesetname, buf); // --> necessaire pour le fichier edit
	carte->tileset = init_loadImage32(buf); // image adapté au format de l'ecran
	fscanf(F, "%d %d", &carte->nbTilex, &carte->nbTiley); // recupere le nombre de tile contenu dans mon image
	fctmap_buildTileset(F, carte);	
}

// remplit ma carte -->necessaire pour le fichier edit
void fctmap_buildLevel(FILE* F, Map* carte)
{
	int i, j;

	//alloue dynamiquement la taille du tableau schema
	carte->schema = malloc(carte->nbtile_LargeurMonde * sizeof(Tileindex*));
	for(i = 0; i < carte->nbtile_LargeurMonde; i++)
		carte->schema[i] = malloc(carte->nbtile_HauteurMonde * sizeof(Tileindex));
	for(j = 0; j < carte->nbtile_HauteurMonde; j++)
	{
		for(i = 0;  i < carte->nbtile_LargeurMonde; i++)
		{
			int tmp;
			fscanf(F, "%d", &tmp);
			if(tmp >= carte->nbTilex * carte->nbTiley)
				init_errorQuit("level tile hors limite\n");
			carte->schema[i][j] = tmp;
		}
	}
}

// remplit mon tableau schema
void fctmap_chargerMap_level(FILE* F, Map* carte)
{	
	char buf[FCTMAP_CACHE_SIZE];
	fscanf(F, "%s", buf);
	fscanf(F, "%d %d", &carte->nbtile_LargeurMonde, &carte->nbtile_HauteurMonde);
	fctmap_buildLevel(F, carte);	
}

// charge les elements du fichier "level" et retourne notre carte
Map* fctmap_chargerMap(const char* level, int largeur_fenetre, int hauteur_fenetre)
{
	FILE* F;
	Map* carte;
	F = fopen(level, "r");
	if(!F)
		init_errorQuit("Fichier level introuvable\n");
	carte = malloc(sizeof(Map));
	fctmap_chargerMap_tileset(F, carte);
	fctmap_chargerMap_level(F, carte);

	// Définit ma fenetre de scrolling
	carte->largeur_fenetre = largeur_fenetre;
	carte->hauteur_fenetre = hauteur_fenetre;
	//carte->scrollx = 0;
	//carte->scrolly = 0;
	fclose(F);
	return carte;
}

// Libere proprement les espaces mémoires alloué à notre Map
int fctmap_libererMap(Map* carte)
{
	int i;
	SDL_FreeSurface(carte->tileset);
	for(i = 0; i < carte->nbtile_HauteurMonde; i++)
		free(carte->schema[i]);
	free(carte->schema);
	free(carte->props);
	free(carte);
	return 0;
}

// Permet de sauvegarder la Map creer dans un fichier
int fctmap_saveMap(const char* fich, Map* carte)
{
	int i, j;
	FILE* F = fopen(fich, "w");
	if(!F)
		return -1;
	fprintf(F, "#tileset\n%s\n", carte->tilesetname);
	fprintf(F, "%d %d\n", carte->nbTilex, carte->nbTiley);
	for(i = 0; i < carte->nbTilex * carte->nbTiley; i++)
		fprintf(F, "tile%d: %s\n", i, (carte->props[i].plein) ?  ("plein") : ("vide"));  // 1 pour plein et 0 pour vide
	fprintf(F, "#level\n%d %d\n", carte->nbtile_LargeurMonde, carte->nbtile_HauteurMonde);
	for(j = 0; j < carte->nbtile_HauteurMonde; j++)
	{
		for(i = 0; i < carte->nbtile_LargeurMonde; i++)
			fprintf(F, "%d \t", carte->schema[i][j]);
		fprintf(F, "\n");
	}
	fclose(F);
	return 0;
}

// Permet d'assigner une nouvelle taille à notre Map (tableau  **shema) *****"Utile si l'on redimensionne notre fenetre"******
int fctmap_resizeMap(Map* carte, int newtaillex, int newtailley)
{
	int i, j;
	Tileindex** anc = carte->schema; // on conserve l'ancien tableau
	
	 // on alloue dynamiquement une nouvelle taille
	carte->schema = malloc(newtaillex * sizeof(Tileindex*));
	for(i = 0; i < newtaillex; i++)
		carte->schema[i] = malloc(newtailley * sizeof(Tileindex));

	// Remplissage de nouvelle carte
	for(i = 0; i < newtaillex; i++)
	{
		for(j = 0; j < newtailley; j++)
		{
			if(i < carte->nbtile_LargeurMonde && j < carte->nbtile_HauteurMonde)
				carte->schema[i][j] = anc[i][j];
			else
				carte->schema[i][j] = 0;
		}
	}

	// on supprime l'ancien
	for(i = 0; i < carte->nbtile_LargeurMonde; i++)
		free(anc);
	free(anc);

	// on assigne les nouvelles dimensions
	carte->nbtile_LargeurMonde = newtaillex;
	carte->nbtile_HauteurMonde = newtailley;
}

// Permet de charger une image et de retourner une carte ******"Utile pour editer une carte à partir d'une nouvelle image"
Map* fctmap_newMap(const char* tileset, int nbTilex, int nbTiley, int nbtile_LargeurMonde, int nbtile_HauteurMonde)
{
	Map* carte = malloc(sizeof(Map));
	strcpy(carte->tilesetname, tileset); // on copie le nom de l'image dans notre champ tilesetname
	carte->tileset = init_loadImage32(tileset);
	carte->nbtile_LargeurMonde = nbtile_LargeurMonde;
	carte->nbtile_HauteurMonde = nbtile_HauteurMonde;
	carte->nbTilex = nbTilex;
	carte->nbTiley = nbTiley;
	fctmap_buildTileset(NULL, carte);
	fctmap_buildLevel(NULL, carte);
	carte->scrollx = 0;
	carte->scrolly = 0;
	carte->hauteur_fenetre = 10;
	carte->largeur_fenetre = 10;
	return carte;
}

// Permet de deplacer la carte
void fctmap_moveMap(Input* in, Map* carte)
{
	if (in->key[SDLK_LEFT])
		carte->scrollx-=MOVEMAP;
	if (in->key[SDLK_RIGHT])
		carte->scrollx+=MOVEMAP;
	if (in->key[SDLK_UP])
		carte->scrolly-=MOVEMAP;
	if (in->key[SDLK_DOWN])
		carte->scrolly+=MOVEMAP;

	// limitation
	if (carte->scrollx<0)
		carte->scrollx=0;
	if (carte->scrolly<0)
		carte->scrolly=0;
	if (carte->scrollx > carte->nbtile_LargeurMonde * carte->LARGEUR_TILE-carte->largeur_fenetre-1)
		carte->scrollx = carte->nbtile_LargeurMonde * carte->LARGEUR_TILE-carte->largeur_fenetre-1;
	if (carte->scrolly > carte->nbtile_HauteurMonde * carte->HAUTEUR_TILE-carte->hauteur_fenetre-1)
		carte->scrolly = carte->nbtile_HauteurMonde * carte->HAUTEUR_TILE-carte->hauteur_fenetre-1;
}

int fctmap_afficherMap(Map* carte, SDL_Surface* ecran)
{
	int i, j;
	SDL_Rect rect_Dest;
	int numtile;
	int miny, maxy, minx, maxx; // variable permettant de restreindre le calcul des tiles au tile present sur la fenetre

	// définition des tiles à afficher
	minx = carte->scrollx / carte->LARGEUR_TILE ;
	miny = carte->scrolly / carte->HAUTEUR_TILE ;
	maxx = (carte->scrollx + carte->largeur_fenetre) / carte->LARGEUR_TILE + 1;
	maxy = (carte->scrolly + carte->hauteur_fenetre) / carte->HAUTEUR_TILE + 1;

	for(i = minx; i < maxx; i++) // Parcour les tiles à aficher et les affiches et ignore ceux qui ne sont pas affichable
	{
		for(j = miny; j < maxy; j++)
		{
			rect_Dest.x = i * carte->LARGEUR_TILE - carte->scrollx;
			rect_Dest.y = j * carte->HAUTEUR_TILE - carte->scrolly;
			if(i < 0 || i >= carte->nbtile_LargeurMonde || j<0 || j >= carte->nbtile_HauteurMonde) // On verifie si nous sommes arrivés à la fin de la carte
				numtile = 0;
			else
				numtile = carte->schema[i][j];
			SDL_BlitSurface(carte->tileset, &(carte->props[numtile].rect), ecran, &rect_Dest);
		}
	}

	return 0;
}