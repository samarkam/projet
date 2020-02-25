/*
init.h
------

par vianel99, pour le projet de fin de Semestre

Rôle: Son rôle est de 
	> recupérer toutes les images utilisé dans le jeu et les charger en mémoire
	> mettre à jour les evenements du clavier, de la souris et des joysticks
	> liberer la memoire à la fin de l'utilisation

Date de creation: 05/02/2020 01h49

Dernière modification: 05/02/2019
*/

#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

	#include "constantes.h"	
	
	// gestion des preferences utilisteurs
	char** init_loadRessources(const char* fichier);
	Preference init_loadPreferencesUser(const char* fichier);
	char** init_languageRessources(Preference* pref);
	void init_savePreferencesUser(Preference* pref, const char* fichier);	

	// adapte le format de l'image au format video (**optimisation de l'affichage de l'image**)
	SDL_Surface* init_loadImage32(const char* fichier_Image);	
	ContextMenu init_loadContextMenu(char** tab);
	

	// Liberation de memoire allouée
	void release(Context* C);
	void init_errorQuit(const char* error);
	int init_libererContextMenu(ContextMenu* cmenu);

#endif