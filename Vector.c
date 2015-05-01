/**
 * \file Vector.c
 * \brief Function related to vectors
 * \author Benjamin Chetioui
 */

#include "Vector.h"

//------------------------------------------------

Vector V_new(float x, float y, float z) {

	Vector v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

Vector V_add(Vector v1, Vector v2) {

	return V_new(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

Vector V_substract(Vector v1, Vector v2) {

	return V_new(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

Vector V_multiply(double lambda, Vector v) {

	return V_new(lambda*v.x, lambda*v.y, lambda*v.z);
}

Vector V_cross(Vector v1, Vector v2) {

	return V_new(
			v1.y*v2.z-v1.z*v2.y,
			v1.z*v2.x-v1.x*v2.z,
			v1.x*v2.y-v1.y*v2.x
			);
}

double V_dot(Vector v1, Vector v2) {

	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

double V_det(Vector u, Vector v, Vector w) {

	return (
			(u.x*v.y*w.z + v.x*w.y*u.z + w.x*u.y*v.z) -
			(u.z*v.y*w.x + v.z*w.y*u.x + w.z*u.y*v.x)
			);
}

int V_isOnTheRight(Vector M, Vector A, Vector B) {

	return (V_det(A, B, M) < 0) ? 1 : 0;
}

int checkPrecision(double x, double y) {

	return ((x-y < EPSILON) && (x-y > -EPSILON)) ? 1 : 0;
}

int V_areCoplanar(Vector A, Vector B, Vector C, Vector D) {

	return (checkPrecision(
				0., 
				V_det(V_substract(B, A), V_substract(C, A), V_substract(D, A))
				)) ? 1 : 0;
}

int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2) {

	if (V_areCoplanar(p1, p2, q1, q2))
		return (
				(V_det(p1, p2, q1)*V_det(p1, p2, q2) < 0) &&
				(V_det(q1, q2, p1)*V_det(q1, q2, p2) < 0)
				) ? 1 : 0;
	return 0;
}

double V_length(Vector v) {

	// Euclidean distance between (0, 0, 0) and v
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vector V_unit(Vector v){

	return V_multiply(1/V_length(v), v);
}

double V_decompose(Vector p, Vector u) {

	return V_dot(p, u)*V_length(u);
}

Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w) {

	return V_add(V_multiply(x, u), V_add(V_multiply(y, v), V_multiply(z, w)));

}

void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y) {

	// If u_z and (0, 1, 0) are colinear...
	if ((u_z.x == 0) && (u_z.z == 0)) {
		// *u_x.z = u_z.y in order for the basis to be orthonormal and direct
		*u_x = V_new(0, 0, u_z.y);
		// What comes naturally!
		*u_y = V_new(u_z.y, 0, 0);
	}
	else{
		double length = V_length(u_z);
		// Using cross product to get u_x orthogonal to ((0, 1, 0), u_z)
		*u_x = V_multiply(length, V_unit(V_cross(V_new(0,1,0), u_z)));
		// (u_x, u_y, u_z) must be direct, therefore u_y = u_z^u_x
		*u_y = V_multiply(length, V_unit(V_cross(u_z, *u_x)));
	}
}

Vector V_rotate(Vector p, Vector centre, Vector v1, Vector v2){

	// Now rotating around (0, 0, 0)
	p = V_substract(p, centre);
	// Coordinates to define
	Vector ux, uy, vx, vy;
	// Getting unit vectors so both bases have vectors with the same norm
	Vector v1_u = V_unit(v1);
	Vector v2_u = V_unit(v2);
	// Crafting the needed bases as described in the given file
	V_uxUyFromUz(v1_u, &ux, &uy);
	V_uxUyFromUz(v2_u, &vx, &vy);

	// Getting each coordinate of p in the basis (ux, uy, v1_u) and remaking it
	// in the basis (vx, vy, v2_u).
	// Adding "centre" to finish the rotation. This step is important.
	return V_add(
			centre,
			V_recompose(
				V_decompose(p, ux),
				V_decompose(p, uy),
				V_decompose(p, v1_u),
				vx,
				vy,
				v2_u
				)
			);
}

//------------------------------------------------
// a des fin de debug

void V_print(Vector v, char *message)
{
	fprintf(stderr,"%s : %f %f %f\n",message, v.x,v.y,v.z);
}

