/*
init.c
------

par vianel99, pour le projet de fin de Semestre

Rôle: Implemente les prototypes des fonctions definit dans init.h;

Date de creation: 05/02/2020 01h49

Dernière modification: 05/02/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "init.h"

// Permet d'adapter l'interface en fonction des choix de l'utilisateur
Preference init_loadPreferencesUser(const char* fichier)
{
	FILE* fic = fopen(fichier, "r");
	if(fic == NULL)
	{
		fprintf(stderr, "le fichier %s est introuvable\n", fichier);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	Preference pref;
	fscanf(fic, "%d %d %d %d %d", &pref.etatmus, &pref.lang, &pref.etatsons, &pref.nivmus, &pref.nivsons);
	fclose(fic);
	return pref;
}

// Permet de charger les ressources en fonction du choix de l'utilisateur
char** init_languageRessources(Preference* pref)
{
	char** tab;
	if(pref->lang)
		tab = init_loadRessources("fichiers/languages/fr_FR.res");
	else
		tab = init_loadRessources("fichiers/languages/en_EN.res");
	return tab;
}

// Enregistrer les preferences utilisateurs
void init_savePreferencesUser(Preference* pref, const char* fichier)
{
	FILE* fic = fopen(fichier, "w");
	if(fic == NULL)
	{
		fprintf(stderr, "le fichier %s est introuvable\n", fichier);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	fprintf(fic, "%d %d %d %d %d", pref->etatmus, pref->lang, pref->etatsons, pref->nivmus, pref->nivsons);
	fclose(fic);
}

// permet de passer l'image au format de l'ecran afin d'optimiser l'affichage
SDL_Surface* init_loadImage32(const char* fichier_Image)
{
	SDL_Surface *image_result = NULL;
	SDL_Surface *image_ram = IMG_Load(fichier_Image); // charge l'image dand image_ram en RAM 
	if(image_ram == NULL)
	{
		fprintf(stderr, "l'image %s est introuvable\n", fichier_Image);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	image_result = SDL_DisplayFormat(image_ram); // recupere l'image dans image_ram et l'adapte au format de l'ecran
	SDL_FreeSurface(image_ram);  // on libere image_ram maintenant inutile
	return image_result;
}

void init_errorQuit(const char* error)
{
	fprintf(stderr, "%s", error);
	SDL_Quit();
	exit(EXIT_FAILURE);
}

char** init_loadRessources(const char* fichier)
{
	char **tab, ligne[FCTMAP_CACHE_SIZE];
	int nb, i;
	FILE* fic = fopen(fichier, "r");
	if(fic == NULL)
		init_errorQuit("Impossible d'acceder au fichier de langue\n");
	fscanf(fic, "%d\n", &nb);
	tab = malloc(nb * sizeof(char*));
	if(tab == NULL)
		init_errorQuit("Impossible d'allouer de la memoire\n");
	for(i = 0; i < nb; i++)
		tab[i] = malloc(FCTMAP_CACHE_SIZE * sizeof(char));
	i = 0;
	while(fgets(ligne, FCTMAP_CACHE_SIZE, fic) != NULL)
	{		
		strcpy(tab[i], ligne);
		tab[i][strlen(tab[i]) - 1] = '\0';
		i++;
	}
	fclose(fic);
	return tab;
}

Button* init_loadButtonText(char** tab, int nbbutt)
{
	Button* but;
	SDL_Color color = {30, 100, 255}, colorfocus = {130, 50, 150};
	TTF_Font *police;
	police = TTF_OpenFont("fonts/BasculaCollege.ttf", 35);
	if(police == NULL)
		init_errorQuit("Erreur d'ouverture de la police\n");
	int nbimages, i;
	char *images[] = {"images/img_button01.png",
						"images/img_button02.png",						
						"images/title.png",
						"images/Fichier3.png",
						"images/vent_01.png",
						"images/vent_02.png",
						"images/vent_03.png",
						"images/copyright.png",
						"images/selec.png",
						"images/ArrowLeft.png",
						"images/ArrowRight.png",
						"images/stat.png"};
	nbimages = sizeof(images) / sizeof(char*);
	nbimages--;
	but = malloc(nbbutt * sizeof(Button));
	but[0].img = malloc(2 * sizeof(SDL_Surface*));
	but[0].img[0] = init_loadImage32(images[0]);
	but[0].img[1] = init_loadImage32(images[1]);
	but[0].nbimg = 2;
	for(i = 1; i < nbimages; i++)
	{
		but[i].img = malloc(sizeof(SDL_Surface*));
		but[i].img[0] = init_loadImage32(images[i + 1]);
		but[i].nbimg = 1;
		SDL_SetColorKey(but[i].img[0], SDL_SRCCOLORKEY, SDL_MapRGB(but[i].img[0]->format, 0, 0, 0)); // Transparence couleur noir
	}
	for(i = i; i < nbbutt; i++)
	{
		//printf("%d\n", i);
		but[i].img = malloc(2 * sizeof(SDL_Surface*));
		but[i].img[0] = TTF_RenderUTF8_Blended(police, tab[i - nbimages], color);
		but[i].img[1] = TTF_RenderUTF8_Blended(police, tab[i - nbimages], colorfocus);
		but[i].nbimg = 2;
		but[i].focus = 0;
		printf("%d) %s\n", i, tab[i - nbimages]);
	}
	but[nbimages].focus = 1;
	TTF_CloseFont(police);
	return but;
}

ContextMenu init_loadContextMenu(char** tab)
{
	int nbbg = 2, i;
	char imgbg[100];
	ContextMenu cmenu;
	cmenu.nbbutt = 25;  // Nombres d'images (bouton) à charger
	cmenu.butt = init_loadButtonText(tab, cmenu.nbbutt);
	cmenu.music = Mix_LoadMUS("musics/bad-world.mp3");
	cmenu.son[0] = Mix_LoadWAV("sons/son1.wav");
	cmenu.son[1] = Mix_LoadWAV("sons/son2.wav");
	cmenu.bg.img = malloc(nbbg * sizeof(SDL_Surface*));
	cmenu.bg.nbimg = nbbg;
	for(i = 0; i < nbbg; i++)
	{
		sprintf(imgbg, "backgrounds/bg%d.png", i+1);
		cmenu.bg.img[i] = IMG_Load(imgbg);
	}
	return cmenu;
}

int init_libererContextMenu(ContextMenu* cmenu)
{
	int i, j;
	for(i = 0; i < cmenu->nbbutt; i++)
	{
		for(j = 0; j < cmenu->butt[i].nbimg; j++)
			SDL_FreeSurface(cmenu->butt[i].img[j]);
		free(cmenu->butt[i].img);
	}
	free(cmenu->butt);
	printf("\nici2\n");
	/*for(i = 0; i < cmenu->bg.nbimg; i++)       // ---> Pourquoi cela genere une erreur de segementation de type CORE DUMPED
		SDL_FreeSurface(cmenu->bg.img[i]);*/
	printf("\nici3\n");	
	free(cmenu->bg.img);
	//liberation de la musique
	Mix_FreeMusic(cmenu->music);
	Mix_FreeChunk(cmenu->son[0]);
	Mix_FreeChunk(cmenu->son[1]);
}