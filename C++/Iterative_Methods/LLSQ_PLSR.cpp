/*
	C++ code implementing LLSQ and PLSR
*/

#include <iostream>
#include <complex>
#include <math.h>

#include "Jacobi_Gauss-Seidel.c++"

using namespace std;

// Assuming max unknowns of 100
#define MAX_N 100

double x[MAX_N];
double y[MAX_N];

#define A(i,j) a[(i) * n + (j)]

double a[MAX_N*MAX_N];
double b[MAX_N];

// Coefficients to the polynomial
double c[MAX_N];

double solve_poly(int n, double v){
	int i;
	double sum = 0;
	for(i = 0; i < n; ++i)
		sum += (c[i] * pow(v, i));
	return sum;
}

void print_matrix(int n){
	int i, j;
	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			cout << a[i*n + j] << " ";
		}
		cout << b[i] << endl;
	}

}


// Uses arrays x and y to fill the 2 values in c
// Returns the error
double LLSQ(int m, int print_error){
	double sum_x, sum_y, sum_xy, sum_x2, error = 0;

	int i;
	for(i = 0; i < m; ++i){
		sum_x += x[i];
		sum_y += y[i];
		sum_xy += (x[i] * y[i]);
		sum_x2 += pow(x[i], 2);
	}
	double bot = ((m * sum_x2) - (pow(sum_x, 2)));
	c[0] = ((sum_x2 * sum_y) - (sum_xy * sum_x)) / bot;
	c[1] = ((sum_xy * m) - (sum_x * sum_y)) / bot;
	// Normal linear
	cout << "a0 = " << c[0] << ", a1 = " << c[1] << endl;
	cout << "y = " << c[0] << " + " << c[1] << "x" << endl;
	// Finding error
	for(i = 0; i < m; ++i)
		error += pow((y[i] - (c[1]*x[i]) - c[0]), 2);
	if(print_error)
		cout << "Error = " << error << endl;
	return error;
}

double LSA1(int m, int print_error){
	double sum_x, sum_y, sum_xy, sum_x2, error = 0;

	int i;
	for(i = 0; i < m; ++i){
		sum_x += x[i];
		sum_y += log(y[i]);
		sum_xy += (x[i] * log(y[i]));
		sum_x2 += pow(x[i], 2);
	}
	double bot = ((m * sum_x2) - (pow(sum_x, 2)));
	c[0] = ((sum_x2 * sum_y) - (sum_xy * sum_x)) / bot;
	c[1] = ((sum_xy * m) - (sum_x * sum_y)) / bot;
	// Normal linear
	cout << "b = " << exp(c[0]) << ", a = " << c[1] << endl;
	cout << "y = " << exp(c[0]) << " e ^ (" << c[1] << ")x" << endl;
	// Finding error
	for(i = 0; i < m; ++i)
		error += pow((y[i] - (exp(c[0])*exp(x[i]*c[1]))), 2);
	if(print_error)
		cout << "Error = " << error << endl;
	return error;
}

double LSA2(int m, int print_error){
	double sum_x, sum_y, sum_xy, sum_x2, error = 0;

	int i;
	for(i = 0; i < m; ++i){
		sum_x += log(x[i]);
		sum_y += log(y[i]);
		sum_xy += (log(x[i]) * log(y[i]));
		sum_x2 += pow(log(x[i]), 2);
	}
	double bot = ((m * sum_x2) - (pow(sum_x, 2)));
	c[0] = ((sum_x2 * sum_y) - (sum_xy * sum_x)) / bot;
	c[1] = ((sum_xy * m) - (sum_x * sum_y)) / bot;
	// Normal linear
	cout << "b = " << exp(c[0]) << ", a = " << c[1] << endl;
	cout << "y = " << exp(c[0]) << " x ^ (" << c[1] << ")" << endl;
	// Finding error
	for(i = 0; i < m; ++i)
		error += pow((y[i] - (exp(c[0])*(pow(x[i],c[1])))), 2);
	if(print_error)
		cout << "Error = " << error << endl;
	return error;
}

double LSA3(int m, int print_error){
	double sum_x, sum_xy, sum_x2, error = 0;

	int i;
	for(i = 0; i < m; ++i){
		sum_x += x[i];
		sum_xy += (x[i] * y[i]);
		sum_x2 += pow(x[i], 2);
	}
	c[0] = sum_xy/(sum_x2+53*sum_x);
	// Normal linear
	cout << "k = " << c[0] << endl;
	// Finding error
	for(i = 0; i < m; ++i)
		error += pow((y[i] - (c[0]*x[i])), 2);
	if(print_error)
		cout << "Error = " << error << endl;
	return error;
}

double sum_x_degree(int m, int degree){
	int i;
	double sum = 0;
	for(i = 0; i < m; ++i)
		sum += pow(x[i], degree);
	return sum;
}

double sum_yx_degree(int m, int degree){
	int i;
	double sum = 0;
	for(i = 0; i < m; ++i)
		sum += (y[i] * pow(x[i], degree));
	return sum;
}

// Solves for linear system for a_0, ....., a_n
// a is matrix degree+1 by degree+1
// Then calls Jacobi method to solve for the values in c
double PLSQ(int n, int m){
	int row, col;
	cout << "\nLinear System: " << endl;
	for(row = 0; row < n + 1; ++row){
		for(col = 0; col < n + 1; ++col){
			a[row * (n+1) + col] = sum_x_degree(m, row+col);
			cout << a[row * (n+1) + col] << " ";
		}
		b[row] = sum_yx_degree(m, row);
		cout << b[row] << endl;
	}

	// matrix a should be filled with linear system for coeffs
	double epsilon = pow(10, -12);
	double error = 0;
	// Sets c with coefficients
	cout << "\nCoefficients: " << endl;
	gauss_seidel(n+1, epsilon, m, 0);
	// jacobi(n+1, epsilon, m, 1000000);
	return error;
}

int main(){

// 5a)
	int m = 10;
	double data_5_x[] = {4.0, 4.2, 4.5, 4.7, 5.1, 5.5, 5.9, 6.3, 6.8, 7.1};
	double data_5_y[] = {102.56, 113.18, 130.11, 142.05, 167.53, 195.14, 
		224.87, 256.73, 299.50, 326.72};
	copy(data_5_x, data_5_x+m, x);
	copy(data_5_y, data_5_y+m, y);
	cout << "\n5a)" << endl;
	LLSQ(m, 1);
	cout << "\n5b)" << endl;
	PLSQ(2, m);
	cout << "\n5c)" << endl;
	PLSQ(3, m);
	cout << "\n5d)" << endl;
	LSA1(m, 1);
	cout << "\n5e)" << endl;
	LSA2(m, 1);


// 6a)
	m = 8;
	double data_6_x[] = {.2,.3,.6,.9,1.1,1.3,1.4,1.6};
	double data_6_y[] = {.050446,.098426,.33277,.72660,1.0972,1.5697,1.8487,2.5015};
	copy(data_6_x, data_6_x+m, x);
	copy(data_6_y, data_6_y+m, y);
	cout << "\n6a)" << endl;
	LLSQ(m, 1);
	cout << "\n6b)" << endl;
	PLSQ(2, m);
	cout << "\n6c)" << endl;
	PLSQ(3, m);
	cout << "\n6d)" << endl;
	LSA1(m, 1);
	cout << "\n6e)" << endl;
	LSA2(m, 1);


// 7a)
	m = 3;
	double data_7a_x[] = {2,4,6};
	double data_7a_y[] = {7,9.4,12.3};
	copy(data_7a_x, data_7a_x+m, x);
	copy(data_7a_y, data_7a_y+m, y);
	cout << "\n7a)" << endl;
	LSA3(m, 1);
// 7b)
	m = 4;
	double data_7b_x[] = {3,5,8,10};
	double data_7b_y[] = {8.3,11.3,14.4,15.9};
	copy(data_7b_x, data_7b_x+m, x);
	copy(data_7b_y, data_7b_y+m, y);
	cout << "\n7b)" << endl;
	LSA3(m, 1);

// 11)
	m = 21;
	double data_11_x[] = {13, 15, 16, 21, 22, 23, 25,
						  29, 30, 31, 36, 40, 42, 55,
						  60, 62, 64, 70, 72,100,130};
	double data_11_y[] = {11, 10, 11, 12, 12, 13, 13,
						  12, 14, 16, 17, 13, 14, 22,
						  14, 21, 21, 24, 17, 23, 34};
	copy(data_11_x, data_11_x+m, x);
	copy(data_11_y, data_11_y+m, y);
	cout << "\n11)" << endl;
	LLSQ(m, 0);	

// Example
	m = 5;
	double data_x[] = {0, 0.25, 0.5, 0.75, 1};
	double data_y[] = {1, 1.284, 1.6487, 2.117, 2.7183};
	copy(data_x, data_x+m, x);
	copy(data_y, data_y+m, y);
	PLSQ(2, m);
	PLSQ(3, m);

	return 0;
}
