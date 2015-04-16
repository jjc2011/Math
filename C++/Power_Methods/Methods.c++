/* 										
	C++ code implementing:
	9.1: Power Method
	9.2: Symmetric Power Method
	9.3: Inverse Power Method	
	9.4: Wielandt Deflation
*/

#include <iostream>
#include <complex>
#include <math.h>

using namespace std;

// Assuming max unknowns of 100
#define MAX_N 100
#define A(i,j) A[i][j]
#define B(i,j) B[i][j]

double A[MAX_N][MAX_N];
double B[MAX_N][MAX_N];

double x[MAX_N];
double y[MAX_N];
double v[MAX_N];
double u[MAX_N];


int print_x(int n){
	cout << "x = ";
	int i;
    for(i = 0; i < n; ++i){
    	cout << " " << x[i];
    }
    cout << endl;
}

int print_y(int n){
	cout << "y = ";
	int i;
    for(i = 0; i < n; ++i){
    	cout << " " << y[i];
    }
    cout << endl;
}

int print_v(int n){
	cout << "v = ";
	int i;
    for(i = 0; i < n; ++i){
    	cout << " " << v[i];
    }
    cout << endl;
}

int gauss_seidel_ipm(int n, double q, double TOL){
	double prev[n];
	int i, j;
	double temp[n][n];
	for(i = 0; i < n; ++i){
		prev[i] = y[i] = x[i];
		for(j = 0; j < n; ++j){
			temp[i][j] = A[i][j];
			if(i == j) temp[i][j] -= q;
		}
	}
	int iter = 1;
	bool end = 0;
	while(!end && iter < 1000){
		for(i = 0; i < n; ++i){
			double sum = 0;
			for(j = 0; j < i; ++j){
				sum += (temp[i][j] * y[j]);
			}
			for(j = i+1; j < n; ++j){
				sum += (temp[i][j] * prev[j]);
			}
			y[i] = (x[i]-sum)/temp[i][i];
		}
		double error = 0;
		for(i = 0; i < n; ++i){
			error += pow(y[i]-prev[i], 2);
		}
		error = sqrt(error);
		if(abs(error) > TOL){
			for(i = 0; i < n; i++){
				prev[i] = y[i];
			}
			iter++;
		}
		else
			return 0;
	}
	return 0;
}

// Find the location of first max in x
int max_x(int n){
	int p = 0;
	double max = x[0];
	int i;
	for(i = 0; i < n; ++i){
		if(abs(x[i]) > max) p = i;
	}
	return p;
}

// Find the location of first max in y
int max_y(int n){
	int p = 0;
	double max = y[0];
	int i;
	for(i = 0; i < n; ++i){
		if(abs(y[i]) > max) p = i;
	}
	return p;
}

// Find the location of first max in y
int max_v(int n){
	int p = 0;
	double max = v[0];
	int i;
	for(i = 0; i < n; ++i){
		if(abs(v[i]) > max) p = i;
	}
	return p;
}

double x_square(int n){
	double total = 0;
	int i;
	for(i = 0; i < n; ++i){
		total += pow(x[i], 2);
	}
	return total;
}

// Finds 2-norm of x
double x_2_norm(int n){
	return sqrt(x_square(n));
}

// Finds 2-norm of y
double y_2_norm(int n){
	double total = 0;
	int i;
	for(i = 0; i < n; ++i){
		total += pow(y[i], 2);
	}
	return sqrt(total);
}

// Calculates 2 norm of (x-y/||y||_2)
double spm_2_norm(int n, double norm){
	double total = 0;
	int i;
	for(i = 0; i < n; ++i){
		double temp = x[i] - (y[i] / norm);
		total += pow(temp, 2);
	}
	return sqrt(total);
}

// Does calculation of y = Ax
int set_y_as_Ax(int n){
	int i, j;
	for(i = 0; i < n; ++i){
		y[i] = 0;
		for(j = 0; j < n; ++j){
			y[i] += A[i][j]*x[j];
		}
	}
	return 0;
}

// Does calculation of y = Bv
int set_y_as_Bv(int n){
	int i, j;
	for(i = 0; i < n; ++i){
		y[i] = 0;
		for(j = 0; j < n; ++j){
			y[i] += B[i][j]*v[j];
		}
	}
	return 0;
}


// Does calculation of mu = x^t y
double x_dot_y(int n){
	double total = 0;
	int i;
	for(i = 0; i < n; ++i){
		total += x[i]*y[i];
	}
	return total;
}

// Does calculation for rayleigh quotient
double get_rayleigh(int n){
	double bot = x_square(n);
	double temp[n];
	int i, j;
	double total = 0;
	for(i = 0; i < n; ++i){
		total = 0;
		for(j = 0; j < n; ++j){
			total += A(j, i)*x[j];
		}
		temp[i] = total;
	}
	total = 0;
	for(i = 0; i < n; ++i){
		total += temp[i]*x[i];
	}
	return (total/bot);
}

// use v and b instead of x and a 
double wielandt_power_method(int n, double TOL, int N){
	int i;
	double err, mu;
	int p = max_v(n);
	if(v[p] != 0){
		for(i = 0; i < n; ++i)
			v[i] = v[i] / v[p];
	}
	int k = 1;
	while(k <= N){
		set_y_as_Bv(n);
		mu = y[p];
		p = max_y(n);
		if(y[p] == 0) return 0;
		int tmp = 0;
		err = abs(v[0] - (y[0]/y[p]));
		for(i = 0; i < n; ++i){
			if(abs(v[i] - (y[i]/y[p])) > err) err = abs(v[i] - (y[i]/y[p]));
				v[i] = y[i]/y[p];
		}
		if(err < TOL) return mu;
		k += 1;
	}
	cout << "The maximum number of iterations exceeded in wielandt power method (ignore mu value)" << endl;
	return 0;
}

// ----- 9.1 ----- //

// n is dimension, TOL is epsilon, N is max iterations
// Outputs: eigenvalue
double power_method(int n, double TOL, int N){
	int i;
	double err, mu;
	int p = max_x(n);
	for(i = 0; i < n; ++i)
		x[i] = x[i] / x[p];
	int k = 1;
	while(k <= N){
		set_y_as_Ax(n);
		mu = y[p];
		p = max_y(n);	
		if(y[p] == 0) return 0;
		int tmp = 0;
		err = abs(x[0] - (y[0]/y[p]));
		for(i = 0; i < n; ++i){
			if(abs(x[i] - (y[i]/y[p])) > err) err = abs(x[i] - (y[i]/y[p]));
				x[i] = y[i]/y[p];
		if(err < TOL) return mu;
		}
		k += 1;
	}
	cout << "The maximum number of iterations exceeded in power method (ignore mu value)" << endl;
	return 0;
}

// ----- 9.2 ----- //

// n is dimension, TOL is epsilon, N is max iterations
// Outputs: eigenvalue
double symmetric_power_method(int n, double TOL, int N){
	int i;
	double err, mu;
	double norm = x_2_norm(n);
	if(norm != 0){
		for(i = 0; i < n; ++i)
			x[i] = x[i] / norm;
	}
	int k = 1;
	while(k <= N){
		set_y_as_Ax(n);
		mu = x_dot_y(n);
		norm = y_2_norm(n);
		if(norm == 0) return 0;
		int tmp = 0;
		err = spm_2_norm(n, norm);
		for(i = 0; i < n; ++i){
			x[i] = y[i]/norm;
		}
		if(err < TOL) return mu;
		k += 1;
	}
	cout << "The maximum number of iterations exceeded in symmetric power method (ignore mu value)" << endl;
	return 0;
}

// ----- 9.3 ----- //

// n is dimension, TOL is epsilon, N is max iterations
// Outputs: eigenvalue
double inverse_power_method(int n, double TOL, int N){
	int i;
	double err, mu;
	double q = get_rayleigh(n);
	int p = max_x(n);
	if(x[p] != 0){
		for(i = 0; i < n; ++i)
			x[i] = x[i] / x[p];
	}
	int k = 1;
	while(k <= N){
		// Uses G-S to solve for y

// This is not converging, which is causing the -nan stuff
		gauss_seidel_ipm(n, q, TOL);

		mu = y[p];
		p = max_y(n);
		if(y[p] == 0) return 0;
		else{
			int tmp = 0;
			err = spm_2_norm(n, y[p]);
			for(i = 0; i < n; ++i){
				x[i] = y[i]/y[p];
			}
			if(err < TOL) return (1/mu) + q;
		}
		k += 1;
	}
	cout << "The maximum number of iterations exceeded in inverse power method (ignore mu value)" << endl;
	return 0;
}

// ----- 9.4 ----- //

// n is dimension, TOL is epsilon, N is max iterations, lam is most dominant e-val
// Use: A, x eigenvector for lam, v for mu
// Outputs: eigenvalue mu, second most dominant eigenvalue
double wielandt_deflation(int n, double TOL, int N, double lam){
	int i = max_x(n);
	int k, j;
	if(i != 0){
		for(k = 0; k < i-1; ++k){
			for(j = 0; j < i-1; ++j){
				B(k,j) = A(k,j) - (A[i][j]*x[k]/x[i]) ;
			}
		}
	}
	if(i != 0 && i != n-1){
		for(k = i; k < n-1; ++k){
			for(j = 0; j < i-1; ++j){
				B(k,j) = A(k+1,j) - (A[i][j]*x[k+1]/x[i]) ;
				B(j,k) = A(j,k+1) - (A(i,k+1)*x[j]/x[i]) ;
			}
		}
	}
	if(i != n-1){
		for(k = i; k < n-1; ++k){
			for(j = i; j < n-1; ++j){
				B(k,j) = A(k+1,j+1) - (A(i,j+1)*x[k+1]/x[i]) ;
			}
		}
	}
	double old[n-1];
	for(k = 0; k < n-1; ++k){
		old[k] = v[k] = x[k];
	}
	// v is initial approx
	double mu = wielandt_power_method(n-1, TOL, N);
	double w[n-1];
	if(i != 0){
		for(k = 0; k < i; ++k) w[k] = v[k];
	}
	w[i] = 0;
	if(i != n-1){
		for(k = i+1; k < n; ++k) w[k] = v[k-1];
	}
    for(k = 0; k < n; ++k){
    	u[k] = 0;
    	for(j = 0; j < n; ++j){
    		u[k] += A[i][j]*w[j];
    	}
    	u[k] *= (v[k]/v[i]);
    	u[k] += (mu-lam)*w[k];
    }
    return mu;
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

int copy_contents(double a [], double b [], int n){
	copy(a, a+n, b);
}

int main(){

	int n, N;
	double TOL, lam;
	int i; int j;

	double data_1a_A[] = { 2, 1, 1,
						   1, 2, 1,
						   1, 1, 2};
	double data_1a_x[] = {1, -1, 2};
	
	double data_1b_A[] = { 1, 1, 1,
						   1, 1, 0,
						   1, 0, 1};
	double data_1b_x[] = {-1, 0, 1};

	double data_1c_A[] = { 1,-1, 0,
						  -2, 4,-2,
						   0,-1, 2};
	double data_1c_x[] = {-1, 2, 1};

	double data_1d_A[] = { 4, 1, 1, 1,
						   1, 3,-1, 1,
						   1,-1, 2, 0,
						   1, 1, 0, 2};
	double data_1d_x[] = {1, -2, 0, 3};

	double data_5a_A[] = { 2, 1, 1,
						   1, 2, 1,
						   1, 1, 2};
	double data_5a_x[] = {1, -1, 2};
	
	double data_5b_A[] = { 1, 1, 1,
						   1, 1, 0,
						   1, 0, 1};
	double data_5b_x[] = {-1, 0, 1};

	double data_5c_A[] = { 4.75, 2.25, -.25,
						   2.25, 4.75, 1.25,
						   -.25, 1.25, 4.75};
	double data_5c_x[] = {0, 1, 0};

	double data_5d_A[] = { 4, 1,-1, 0,
						   1, 3,-1, 0,
						  -1,-1, 5, 2,
						   0, 0, 2, 4};
	double data_5d_x[] = {0, 1, 0, 0};

	double data_6a_A[] = {-2, 1, 3,
						   1, 3,-1,
						   3,-1, 2};
	double data_6a_x[] = {1, -1, 2};
	
	double data_6b_A[] = { 4, 2,-1,
						   2, 0, 2,
						  -1, 2, 0};
	double data_6b_x[] = {-1, 0, 1};

	double data_6c_A[] = { 4, 1, 1, 1,
						   1, 3,-1, 1,
						   1,-1, 2, 0,
						   1, 1, 0, 2};
	double data_6c_x[] = {1, 0, 0, 0};

	double data_6d_A[] = { 5, -2, -.5, 1.5,
						   -2, 5, 1.5, -.5,
						  -.5, 1.5, 5, -2,
						   1.5, -.5, -2, 5};
	double data_6d_x[] = {1, 1, 0, -3};

// 9a
	n = 3;
	N = 25;
	TOL = pow(10,-4);
	copy_contents(data_1a_A, A, n);
	copy_contents(data_1a_x, x, n);
	cout << "\n9a:" << endl;
	cout << "mu = " << inverse_power_method(n, TOL, N) << endl;
	print_x(n);

// 9b
	copy_contents(data_1b_A, A, n);
	copy_contents(data_1b_x, x, n);
	cout << "\n9b:" << endl;
	cout << "mu = " << inverse_power_method(n, TOL, N) << endl;
	print_x(n);

// 9c
	copy_contents(data_1c_A, A, n);
	copy_contents(data_1c_x, x, n);
	cout << "\n9c:" << endl;
	cout << "mu = " << inverse_power_method(n, TOL, N) << endl;
	print_x(n);

// 9d
	n = 4;
	copy_contents(data_1d_A, A, n);
	copy_contents(data_1d_x, x, n);
	cout << "\n9d:" << endl;
	cout << "mu = " << inverse_power_method(n, TOL, N) << endl;
	print_x(n);

// 11a
	n = 3;
	N = 25;
	TOL = pow(10,-4);
	copy_contents(data_5a_A, A, n);
	copy_contents(data_5a_x, x, n);
	cout << "\n11a:" << endl;
	cout << "mu = " << symmetric_power_method(n, TOL, N) << endl;
	print_x(n);

// 11b
	copy_contents(data_5b_A, A, n);
	copy_contents(data_5b_x, x, n);
	cout << "\n11b:" << endl;
	cout << "mu = " << symmetric_power_method(n, TOL, N) << endl;
	print_x(n);

// 11c
	copy_contents(data_5c_A, A, n);
	copy_contents(data_5c_x, x, n);
	cout << "\n11c:" << endl;
	cout << "mu = " << symmetric_power_method(n, TOL, N) << endl;
	print_x(n);

// 11d
	n = 4;
	copy_contents(data_5d_A, A, n);
	copy_contents(data_5d_x, x, n);
	cout << "\n11d:" << endl;
	cout << "mu = " << symmetric_power_method(n, TOL, N) << endl;
	print_x(n);

// 12a
	n = 3;
	N = 25;
	TOL = pow(10,-4);
	copy_contents(data_6a_A, A, n);
	copy_contents(data_6a_x, x, n);
	cout << "\n12a:" << endl;
	cout << "mu = " << symmetric_power_method(n, TOL, N) << endl;
	print_x(n);

// 12b
	copy_contents(data_6b_A, A, n);
	copy_contents(data_6b_x, x, n);
	cout << "\n12b:" << endl;
	cout << "mu = " << symmetric_power_method(n, TOL, N) << endl;
	print_x(n);

// 12c
	n = 4;
	copy_contents(data_6c_A, A, n);
	copy_contents(data_6c_x, x, n);
	cout << "\n12c:" << endl;
	cout << "mu = " << symmetric_power_method(n, TOL, N) << endl;
	print_x(n);

// 12d
	copy_contents(data_6d_A, A, n);
	copy_contents(data_6d_x, x, n);
	cout << "\n12d:" << endl;
	cout << "mu = " << symmetric_power_method(n, TOL, N) << endl;
	print_x(n);

// 13a
	n = 3;
	N = 25;
	TOL = pow(10,-4);
	copy_contents(data_1a_A, A, n);
	copy_contents(data_1a_x, x, n);
	cout << "\n13a:" << endl;
	lam = power_method(n, TOL, N);
	cout << "lam = " << lam << endl;
	print_x(n);
	cout << "mu = " << wielandt_deflation(n, TOL, N, lam) << endl;
	print_x(n);

// 13b
	copy_contents(data_1b_A, A, n);
	copy_contents(data_1b_x, x, n);
	cout << "\n13b:" << endl;
	lam = power_method(n, TOL, N);
	cout << "lam = " << lam << endl;
	print_x(n);
	cout << "mu = " << wielandt_deflation(n, TOL, N, lam) << endl;
	print_x(n);

// 13c
	copy_contents(data_1c_A, A, n);
	copy_contents(data_1c_x, x, n);
	cout << "\n13c:" << endl;
	lam = power_method(n, TOL, N);
	cout << "lam = " << lam << endl;
	print_x(n);
	cout << "mu = " << wielandt_deflation(n, TOL, N, lam) << endl;
	print_x(n);

// 13d
	n = 4;
	copy_contents(data_1d_A, A, n);
	copy_contents(data_1d_x, x, n);
	cout << "\n13d:" << endl;
	lam = power_method(n, TOL, N);
	cout << "lam = " << lam << endl;
	print_x(n);
	cout << "mu = " << wielandt_deflation(n, TOL, N, lam) << endl;
	print_x(n);



	return 0;
}


