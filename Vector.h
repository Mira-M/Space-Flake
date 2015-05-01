/**
 * \file Vector.h
 * \brief Function headers related to vectors
 * \author Benjamin Chetioui
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#define EPSILON 1e-5
// Précision pour comparer des flottants entre eux sans risquer de faire
// d'erreurs.

typedef struct {
	float x, y, z;
} Vector;

Vector V_new(float x, float y, float z);
// retourne un vecteur de composantes x, y et z

void V_print(Vector v, char *message);
// affiche à l'écran les coordonnées de v + un message (debug)

Vector V_add(Vector v1, Vector v2);
// retourne v1+v2

Vector V_substract(Vector v1, Vector v2);
// retourne v1-v2

Vector V_multiply(double lambda, Vector v);
// retourne lambda * v

Vector V_cross(Vector v1, Vector v2);
// retourne le produit vectoriel v1^v2

double V_dot(Vector v1, Vector v2);
// retourne le produit scalaire : v1.v2

double V_det(Vector u, Vector v, Vector w);
// retourne le déterminant de la matrice uvw

int V_isOnTheRight(Vector M, Vector A, Vector B);
// retourne 1 si M est à la droite de la droite (AB) et 0 sinon

int checkPrecision(double x, double y);
// retourne 1 si x == y à EPSILON près, 0 sinon

int isZero(double x);
// retourne 1 si x == 0 à EPSILON près, 0 sinon

int V_isNull(Vector v);
// retourne 1 si le vecteur v est nul à EPSILON près, 0 sinon

int V_areCoplanar(Vector A, Vector B, Vector C, Vector D);
// retourne 1 si A, B, C et D sont coplanaires, 0 sinon

int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2);
// retourne 1 si le segment [p1p2] intersecte le segment [q1q2]

int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2);
// retourne 1 si la demie droite d'origine M et de direction u_ray
// intersect le segment [p1p2]

double V_length(Vector v);
// retourne le module du vecteur v

Vector V_unit(Vector v);
// retourne un vecteur colinéaire à v mais de longueur 1

Vector V_tournerAutourDeLAxeY(Vector p, double radians);
// Tourne d'un angle de radians le point  p autour de l'axe Y
// et retourne le résultat.

double V_decompose(Vector p, Vector u);
// Si (u,v,w) est un repère orthonormé de l'espace, chaque vecteur p
// possède des coordonnées dans ce repère. Cette fonction retourne
// la coordonnée selon u du vecteur p.

Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w);
// Si (u,v,w) est un repère orthonormé de l'espace, cette fonction
// retourne le vecteur dont les coordonnées dans cet espace sont (x,y,z)

void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y); 
// A partir d'un vecteur uz, cette fonction modifie deux vecteurs
// ux et uy tels que (ux, uy, uz) soit un repère orthonormé direct
// et que les vecteurs (uy,uz) soient dans le même plan que les
// vecteurs ((0,1,0),uz) sauf si uz est lui même colinéaire à (0,1,0).

Vector V_rotate(Vector p, Vector centre, Vector v1, Vector v2);
// Cette fonction opère sur le point p une rotation autour de centre
// et qui transforme le vecteur v1 en vecteur v2.

#endif // __VECTOR_H__
