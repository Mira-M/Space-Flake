/**
 * \file Polygon.c
 * \brief Functions related to polygons
 * \author Benjamin Chetioui
 */

#include "Polygon.h"

void P_init(Polygon *p) {

	p->nb_vertices = 0;
	p->is_closed = 0;
	p->is_filled = 0;
	p->is_convex = 0;
}

void P_copy(Polygon *original, Polygon *copie) {

	*copie = *original;
}

void P_addVertex(Polygon *P, Vector pos) {

	P->vertices[P->nb_vertices] = pos;
	P->nb_vertices++;
}

void P_removeLastVertex(Polygon *P) {
	if (P->nb_vertices > 0) P->nb_vertices--;
}

void P_print(Polygon *P, char *message) {

	int i;
	fprintf(
			stderr, "%s : %d %d %d\n",
			message,
			P->is_closed,
			P->is_filled,
			P->is_convex
			);
	for(i=0; i < P->nb_vertices; i++) {
		V_print(P->vertices[i], "-");
	}
}

void P_draw(Polygon *P){

	int i;
	// Filled polygon
	if (P->is_filled == 1){
		if (P->nb_vertices < 3) glBegin(GL_LINES);
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_POLYGON);
		}
		for (i = 0; i < P->nb_vertices; i++) {
			glVertex3f(P->vertices[i].x, P->vertices[i].y, 0);
		}
	}
	// Empty polygon
	else {
		// Closed polygon
		if (P->is_closed == 1) {
			// Shouldn't happen if it is closed, duuuh
			if (P->nb_vertices == 1) glBegin(GL_POINTS);
			else glBegin(GL_LINE_LOOP);
			for(i = 0; i < P->nb_vertices; i++) {
				glVertex3f(P->vertices[i].x, P->vertices[i].y, 0);
			} 
		}
		// Open polygon
		else {
			if (P->nb_vertices == 1) glBegin(GL_POINTS);
			else glBegin(GL_LINE_STRIP);
			for (i = 0; i < P->nb_vertices; i++){
				glVertex3f(P->vertices[i].x, P->vertices[i].y, 0);
			} 
		}	
	}
	glEnd();
}

int P_isConvex(Polygon *P) {

	if ((P->nb_vertices < 3) || (P->is_convex == -1)) return 0;
	if (P->nb_vertices == 3) {
		P->is_convex = 1;
		return 1;
	}

	// x and y coordinates of the vector between 
	// P->vertices[0] and P->vertices[1]
	double x1 = P->vertices[1].x-P->vertices[0].x;
	double y1 = P->vertices[1].y-P->vertices[0].y;
	// x and y coordinates of the vector between 
	// P->vertices[1] and P->vertices[2]
	double x2 = P->vertices[2].x-P->vertices[1].x;
	double y2 = P->vertices[2].y-P->vertices[1].y;

	// Computing the z coordinate of the cross product of both our vectors
	double z_sign = x1*y2-y1*x2;

	// Storing (i+1)%P->nb_vertices and (i+2)%P->nb_vertices
	int rank1, rank2;
	int i;

	for(i = 1; i < P->nb_vertices; i++) {
		rank1 = (i+1)%(P->nb_vertices);
		rank2 = (i+2)%(P->nb_vertices);
		x1 = P->vertices[rank1].x-P->vertices[i].x;
		y1 = P->vertices[rank1].y-P->vertices[i].y;
		x2 = P->vertices[rank2].x-P->vertices[rank1].x;
		y2 = P->vertices[rank2].y-P->vertices[rank1].y;

		// Property of the cross product : 
		// u^v = w => (u,v,w) is direct, which implies that if
		// z_sign*(x1*y2-y1*x2) < 0, the polygon isn't convex
		if ((z_sign*(x1*y2-y1*x2)) < 0) {
			P->is_convex = -1;
			return 0;
		}
	}

	P->is_convex = 1;
	return 1;
}

void P_turnAroundY(Polygon *P, double radians) {
	
	int i;
	for (i = 0; i < P->nb_vertices; i++){
		P->vertices[i] = V_turnAroundY(P->vertices[i], radians);
	}
}

Vector P_center(Polygon *P) {
	
	int i;
	if ((P == NULL) || (P->nb_vertices == 0))
		return V_new(0, 0, 0);
	Vector result = P->vertices[0];
	for(i = 1; i < P->nb_vertices; i++) {
		result = V_add(result, P->vertices[i]);
	}
	return V_multiply(1./P->nb_vertices, result);
}

Vector P_normal(Polygon *P) {

	int i, j;
	Vector V_tmp, V_res;
	
	// Extensive error checking makes the function a bit long
	for(i = 0; i < P->nb_vertices; i++) {
		// Getting the first vector in the polygon which is not null
		V_tmp = V_substract(
				P->vertices[(i+1)%(P->nb_vertices)],
				P->vertices[i]
				);
		if (!V_isNull(V_tmp)) break;
	}

	// Starting at i+1, all of the previous vectors were null except for V_tmp
	for(j = i+1; j < P->nb_vertices; j++) {
		V_res = V_cross(
				V_tmp,
				V_substract(P->vertices[(j+1)%P->nb_vertices], P->vertices[j])
				);
		// Getting the cross product of two non-colinear vectors.
		// In this particular use case, V_res == (0,0,0) implies that the points
		// are aligned.
		if (!V_isNull(V_res))
			return V_unit(V_res);
	}

	return V_new(0, 0, 0);
}

void P_translate(Polygon *P, Vector trans) {
	
	int i;
	for(i = 0; i < P->nb_vertices; i++) {
		P->vertices[i] = V_add(P->vertices[i], trans);
	}
}

void P_rotate(Polygon *P, Vector normal) {
	
	Vector v_p = P_center(P);
	Vector v_n = P_normal(P);
	normal = V_unit(normal);
	int i;
	
	for(i = 0; i < P->nb_vertices; i++) {
		P->vertices[i] = V_rotate(P->vertices[i], v_p, v_n, normal);
	}
}
