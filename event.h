/*
fctevent.h
----------

par vianel99, pour le projet de fin de Semestre

Rôle: Contient les prototypes des fonctions de fctevent.c

Date de creation: 05/02/2020 11h31

Dernière modification: 05/02/2019
*/

#ifndef FCTEVENT_H_INCLUDED
#define FCTEVENT_H_INCLUDED

	#include "constantes.h"

	// gestion des evenements de la souris
	void fctevent_updateEvents(Input* in);
	void fctevent_init_Events(Input* in);

#endif