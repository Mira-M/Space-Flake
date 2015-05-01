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
// is_convex can take 3 values :
// - if is_convex == 0, the polygon isn't constructed yet
// - if is_convex == 1, the polygon is convex
// - if is_convex == -1, the polygon isn't convex and can't become convex

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

void P_turnAroundY(Polygon *P, double radians); 
// tourne tous les points de P d'un angle de radians
// radians autour de l'axe Y.

Vector P_center(Polygon *P);
// Cette fonction retourne le centre d'un polygone plan, c'est-à-dire
// la moyenne des positions de ses points.

Vector P_normal(Polygon *P);
// On suppose que P est un polygone plan. Cette fonction retourne
// un vecteur unitaire normal à ce polygone

void P_translate(Polygon *P, Vector trans);
// Translate tous les sommets de P d'un vecteur trans.

void P_rotate(Polygon *P, Vector normal);
// Faire tourner le polygone plan P autour de son centre de façon à
// ce que son vecteur normal soit égal à normal. (Cf fonction V_rotate)

#endif // __POLYGON_H__
