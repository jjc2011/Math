/* 										
	C++ code implementing:
	Householder Method
*/

#include <iostream>
#include <complex>
#include <math.h>

using namespace std;

// Assuming max unknowns of 100
#define MAX_N 100
#define A(i,j) A[i][j]
#define H(i,j) B[i][j]

double A[MAX_N][MAX_N];
double H[MAX_N][MAX_N];
double result[MAX_N][MAX_N];

double x[MAX_N];
double y[MAX_N];
double v[MAX_N];
double u[MAX_N];

void print_value(double val, char c){
	cout << c << " = " << round(val * 1000.0)/1000.0 << endl;
}

void print_A(int n){
	cout << "A = " << endl;
    for(int i = 0; i < n; ++i){
	    for(int j = 0; j < n; ++j){
	    	if(abs(A[i][j]) < pow(10,-10))
	    		A[i][j] = 0;
	    	double val = round(A[i][j] * 100000.0)/100000.0;
	    	cout << " " << val;
		}
	    cout << endl;
	}
}

void print_vector(double * v, int n, char c){
	cout << c << " =" << endl;
    for(int i = 0; i < n; ++i){
	    	double val = round(v[i] * 1000.0)/1000.0;
	    	cout << " " << val;
    }
    cout << endl;
}

void householder_method(int n){
	double alpha, r;
	double w[n];
	double v[n];
	double u[n];
	double z[n];

	// Step 1
	for(int k = 0; k < n-2; ++k){

		// Step 2
		double q = 0;
		for(int j = k+1; j < n; ++j)
			q += pow(A[j][k],2);

		// Step 3
		if(A[k+1][k] == 0)	alpha = sqrt(q);
		else				alpha = (-1*sqrt(q)*A[k+1][k])/(abs(A[k+1][k]));
		print_value(alpha,'a');

		// Step 4
		double rsq = (pow(alpha, 2) - alpha*A[k+1][k]);
		r = sqrt(rsq/2);
		print_value(r,'r');

		// Step 5
		for(int j = 0; j < k+1; ++j){
			v[j] = 0;
			w[j] = 0;
		}			
		v[k+1] = (A[k+1][k] - alpha);
		w[k+1] = v[k+1] / (2*r);
		for(int j = k+2; j < n; ++j){
			v[j] = A[j][k];
			w[j] = v[j] / (2*r);
		}
		print_vector(v, n, 'v');
		print_vector(w, n, 'w');

		// Step 6
		for(int j = k; j < n; ++j){
			u[j] = 0;
			for(int i = k+1; i < n; ++i){
				u[j] += A[j][i]*v[i];
			}
			u[j] /= rsq;
		}
		print_vector(u, n,'u');

		// Step 7
		double prod = 0;
		for(int i = k+1; i < n; ++i){
			prod += v[i]*u[i];
		}
		print_value(prod, 'p');

		// Step 8
		for(int j = k; j < n; ++j){
			z[j] = u[j] - (prod/(2*rsq))*v[j];
		}
		print_vector(z, n, 'z');

		// Step 9
		for(int l = k+1; l < n-1; ++l){
			
			// Step 10
			for(int j = l+1; j < n; ++j){
				A[j][l] = A[j][l] - (v[l]*z[j]) - (v[j]*z[l]);
				A[l][j] = A[j][l];
			}

			// Step 11
			A[l][l] = A[l][l] - 2*v[l]*z[l];
		}

		// Step 12
		A[n-1][n-1] = A[n-1][n-1] - 2*v[n-1]*z[n-1]; 

		// Step 13
		for(int j = k+2; j < n; ++j){
			A[j][k] = 0;
			A[k][j] = 0;
		}
		
		// Step 14
		A[k+1][k] = A[k+1][k] - v[k+1]*z[k]; 
		A[k][k+1] = A[k+1][k];

		print_A(n); 
	}
}

// Copies contents in a into b
int copy_contents(double a [], double b [][MAX_N], int n){
	int i,j;
    for(i = 0; i < n; ++i){
    	for(j = 0; j < n; ++j){
			b[i][j] = a[(i*n) + j];
    	}
	}
	return 0;
}

int main(){

	int n;

	double data_1a_A[] = { 12, 10, 4,
						   10, 8, -5,
						   4, -5, 3};
	double data_1b_A[] = { 2, -1, -1,
						   -1, 2, -1,
						   -1, -1, 2};
	double data_1c_A[] = { 1, 1, 1,
						   1, 1, 0,
						   1, 0, 1};
	double data_1d_A[] = { 4.75, 2.25, -0.25,
						   2.25, 4.75, 1.25,
						   -0.25, 1.25, 4.75};

	double data_2a_A[] = { 4, -1, -1,  0,
						  -1,  4,  0, -1,
						  -1,  0,  4, -1,
						   0, -1, -1,  4};
	double data_2b_A[] = {  5,  -2, -.5, 1.5,
						   -2,   5, 1.5, -.5,
						  -.5, 1.5,   5,  -2,
						  1.5, -.5,  -2,   5};
	double data_2c_A[] = {  8, .25,  .5,   2,  -1,
						  .25,  -4,   0,   1,   2,
						   .5,   0,   5, .75,  -1,
						    2,   1, .75,   5, -.5,
						   -1,   2,  -1, -.5,   6};
	double data_2d_A[] = {	2, -1, -1,	0,	0,
						   -1,	3,	0, -2,	0,
						   -1,	0,	4,	2,	1,
							0, -1,	2,	8,	3,
							0,	0,	1,	3,	9};

// 1a
	n = 3;
	copy_contents(data_1a_A, A, n);
	cout << "\n1a:" << endl;
	householder_method(n);
	print_A(n);

// 1b
	copy_contents(data_1b_A, A, n);
	cout << "\n1b:" << endl;
	householder_method(n);
	print_A(n);

// 1c
	copy_contents(data_1c_A, A, n);
	cout << "\n1c:" << endl;
	householder_method(n);
	print_A(n);

// 1d
	copy_contents(data_1d_A, A, n);
	cout << "\n1d:" << endl;
	householder_method(n);
	print_A(n);

// 2a
	n = 4;
	copy_contents(data_2a_A, A, n);
	cout << "\n2a:" << endl;
	householder_method(n);
	print_A(n);

// 2b
	copy_contents(data_2b_A, A, n);
	cout << "\n2b:" << endl;
	householder_method(n);
	print_A(n);

// 2c
	n = 5;
	copy_contents(data_2c_A, A, n);
	cout << "\n2c:" << endl;
	householder_method(n);
	print_A(n);

// 2d
	copy_contents(data_2d_A, A, n);
	cout << "\n2d:" << endl;
	householder_method(n);
	print_A(n);

	return 0;
}




