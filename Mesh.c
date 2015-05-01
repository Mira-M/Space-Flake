/**
 * \file Mesh.c
 * \brief Functions related to meshes
 * \author Benjamin Chetioui
 */

#include "Mesh.h"

Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4){
	Quad q;
	q.vertices[0]=v1;
	q.vertices[1]=v2;
	q.vertices[2]=v3;
	q.vertices[3]=v4;
	return q;
}

void M_init(Mesh *M) {
	M->nb_quads = 0;
	M->is_filled = 0;
}

void M_addQuad(Mesh *M, Quad q) {

	M->quads[M->nb_quads] = q;
	M->nb_quads++;
}

void M_draw(Mesh *M) {

	int i;
	float off, color;
	
	if (M->nb_quads != 0) {
		off = (1.0/M->nb_quads);
		color = 0.99+off;
	}

	for(i = 0; i < M->nb_quads; i++){
		if(M->is_filled)
			glBegin(GL_QUADS);
		else				
			glBegin(GL_LINE_LOOP);

		// Simulating levels of gray so that the quads get darker
		// and darker as we iterate.
		color -= off;
		glColor3f(color, color, color);

		glVertex3f(
				M->quads[i].vertices[0].x,
				M->quads[i].vertices[0].y,
				M->quads[i].vertices[0].z
				);
		glVertex3f(
				M->quads[i].vertices[1].x,
				M->quads[i].vertices[1].y,
				M->quads[i].vertices[1].z
				);
		glVertex3f(
				M->quads[i].vertices[2].x,
				M->quads[i].vertices[2].y,
				M->quads[i].vertices[2].z
				);
		glVertex3f(
				M->quads[i].vertices[3].x,
				M->quads[i].vertices[3].y,
				M->quads[i].vertices[3].z
				);
		glEnd();
	}
}
