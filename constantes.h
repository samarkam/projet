/*
constantes.h
------------

par vianel99, pour le projet de fin de Semestre

Rôle: Ce fichier contient toutes les constantes les constantes necessaires au bon fonctionnement du programme

Date de creation: 05/02/2020 01h49

Dernière modification: 05/02/2019
*/

#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
	#include "SDL/SDL_ttf.h"
	#include "SDL/SDL_mixer.h"

	#define LARGEUR_FENETRE 960
	#define HAUTEUR_FENETRE 540

	#define TMENU 11

	#define NBPLAYER 2
	#define MOVEMAP 1   // Vitesse de déplacement de la carte

	#define FCTMAP_CACHE_SIZE 500

	#define INTERFACE_MENU 5  // nombre de bouttons de notre menu

	typedef SDL_Surface* SURFACE; 
	typedef int bool;
	#define TRUE 0
	#define FALSE 1

	// Gestion des preferences utilisateurs
	typedef struct 
	{
		int etatmus;
		int lang;
		int etatsons;
		int nivmus;
		int nivsons;
	} Preference;

	// Gestion des boutons
	typedef struct 
	{
		SDL_Surface** img;     // Le nombre d'image du bouton
		SDL_Rect pos;		//position de l'image
		int nbimg;		
		int focus;
	} Button;

	// Gestion du Background
	typedef struct
	{
		SDL_Surface** img;
		SDL_Rect pos;
		int nbimg;
		char* texte;
		SDL_Rect postxt;
	} Background;

	// Gestion des elements du menu
	typedef struct 
	{
		Background bg;
		Button* butt; 	// le nombre d'image de notre background
		Mix_Music* music;  	// la music qui sera jouer en continu
		Mix_Chunk* son[2];   // Son jouer sur les Boutons
		int nbbutt;	
	} ContextMenu;

	// Gestion de l'affichage des tiles
	typedef unsigned int Tileindex; /* definit le nombre de tiles possible à inscrire sur le carte du monde :) Un "int" est largement suffisant */

 	typedef struct 
 	{
 		SDL_Rect rect; //rectangle propre à une tile
 		int plein; // Permettant de verifier si le tile est plein ou vide ("on peut marcher" ou "on ne peut pas")
 	} Tileprop; // propriété d'une tuile

 	typedef struct 
 	{
 		int LARGEUR_TILE, HAUTEUR_TILE;
 		int nbTilex, nbTiley; // nombre de tiles en x et y de notre image stokée dans "tileset"
 		SDL_Surface* tileset;
 		char tilesetname[FCTMAP_CACHE_SIZE]; // necessaire pour le fichier edit
 		Tileprop* props; // nos rectangle deja calculé
 		Tileindex** schema; // notre carte en chiffre
 		int nbtile_LargeurMonde, nbtile_HauteurMonde; 
 		int scrollx, scrolly;
 		int largeur_fenetre, hauteur_fenetre; // l'ecran **
 	}Map; // carte du jeu

	typedef struct 
	{
		SDL_Surface* img;
		int nbimg;
	} Sprite;
	
	// ceci est le contexte du jeu (C'est tout ce qui définit le jeu)
	typedef struct 
	{
		SDL_Surface* ecran;  // l'ecran
		SDL_Surface** image; // tableau d'image
		int nbimg;
		Sprite* sprite;  // tableau de sprite
		int nbsp;
		int XRES, YRES; // Resolution de la fenetre
		Map* carte;
	} Context;

	// Gestion des inputs
	typedef struct
	{	
		int key[SDLK_LAST];
		int mousex, mousey;
		int mouserelx, mouserely;
		int mousebuttons[8];
		int quit;		
	} Input;

#endif