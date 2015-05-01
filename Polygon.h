/**
 * \file Polygon.h
 * \brief Function headers related to polygons
 * \author Benjamin Chetioui
 */
 
#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Vector.h"

#define P_MAX_VERTICES 1000

typedef struct
{
	int nb_vertices;
	Vector vertices[P_MAX_VERTICES];
	int is_closed;
	int is_filled;
	int is_convex;
} Polygon;

void P_init(Polygon *p);
// initialise un polygone (0 sommets)

void P_copy(Polygon *original, Polygon *copie);
// original et copie sont deux polygones déjà alloués.
// Cette fonction copie les donnée
// depuis original vers copie de façon à ce que les
// deux polygones soient identiques.

void P_addVertex(Polygon *P, Vector pos);
// ajoute un sommet au polygone P. Ce nouveau sommet est situé en pos.

void P_removeLastVertex(Polygon *P);
// enlève le dernier sommet de P

void P_draw(Polygon *P);
// dessine le polygone P

void P_print(Polygon *P, char *message);
// Affiche sur une console les données de P
// à des fins de debuggage.

int P_isConvex(Polygon *P);
// Retourne 1 si le polygone donné en paramètre est convexe et 0 sinon.

void  P_tournerAutourDeLAxeY(Polygon *P, double radians);
// tourne tous les points de P d'un angle de radians
// radians autour de l'axe Y.

#endif // __POLYGON_H__