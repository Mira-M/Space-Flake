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

	if (M->nb_quads < M_MAX_QUADS) {
		M->quads[M->nb_quads] = q;
		M->nb_quads++;
	}
}

void M_draw(Mesh *M) {

	int i;
	float off, color;

	if (M->nb_quads != 0) {
		off = (1.0/M->nb_quads);
		color = 1+off;
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

void M_print(Mesh *M, char *message) {

	int i;
	fprintf(stderr, "%s\n", message);
	for(i = 0; i < M->nb_quads; i++) {
		V_print(M->quads[i].vertices[0], "s1 : ");
		V_print(M->quads[i].vertices[1], "s2 : ");
		V_print(M->quads[i].vertices[2], "s3 : ");
		V_print(M->quads[i].vertices[3], "s4 : ");
	}
}

void M_addSlice(Mesh *M, Polygon *P1, Polygon *P2) {

	int i, rank;
	int sup = P1->nb_vertices;
	if ((P1->is_closed) && (P2->is_closed)) sup -= 1;
	
	for(i = 0; i < sup; i++) {
		rank = (i+1)%P1->nb_vertices;
		M_addQuad(
				M,
				Q_new(
					P1->vertices[i],
					P1->vertices[rank],
					P2->vertices[rank],
					P2->vertices[i]
					)
				);
	}
}

void M_revolution(Mesh *M, Polygon *P, int nb_tranches) {
	
	if (nb_tranches <= 0) return;
	int i;
	double radians = 2*M_PI/nb_tranches;
	Polygon p1, p2;
	P_copy(P, &p1);
	P_copy(P, &p2);

	for (i = 0; i < nb_tranches; i++) {
		P_turnAroundY(&p2, radians);
		M_addSlice(M, &p1, &p2);
		P_copy(&p2, &p1);
	}
}
