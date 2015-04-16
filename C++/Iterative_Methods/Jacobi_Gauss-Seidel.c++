/*
	Write a C/C++ code implementing the Jacobi method and Gauss-Seidel method for 
	solving an nxn linear system. 
*/

#include <iostream>
#include <complex>
#include <math.h>

using namespace std;

// Assuming max unknowns of 10
#define MAX_N 100
#define A(i,j) a[(i) * n + (j)]

double a[MAX_N*MAX_N];
double b[MAX_N];

int jacobi(int n, double epsilon){
	double x[n];
	double prev[n];
	int i;
	for(i = 0; i < n; ++i)
		x[i] = prev[i] = 0;
	int iter = 1;
	bool end = 1;
	while(end){
		for(i = 0; i < n; ++i){
			double sum = 0;
			int j;
			for(j = 0; j < n; ++j){
				if(j != i)
					sum += (A(i,j) * prev[j]);
			}
			x[i] = (b[i]-sum)/A(i,i);
		}
		double error = 0;
		// l_inf
		for(i = 0; i < n; ++i){
			if (error < abs(x[i]-prev[i]))
				error = abs(x[i]-prev[i]);
		
		}
		if(abs(error) <= epsilon){
		//if(iter == 25){
			cout << "Jacobi method:" << endl;
			cout << "Number of iterations needed, " << iter 
				<< ", to get tolerance " << epsilon << endl; 			
			for(i = 0; i < n; i++)
				cout << x[i] << " ";
			cout << endl;
			end = 0;
		}
		else{
			for(i = 0; i < n; i++){
				prev[i] = x[i];
			}
			iter++;
		}
	}
	return 0;
}

int gauss_seidel(int n, double epsilon){
	double x[n];
	double prev[n];
	int i;
	for(i = 0; i < n; ++i)
		x[i] = prev[i] = 0;
	int iter = 1;
	bool end = 1;
	while(end){
		for(i = 0; i < n; ++i){
			double sum = 0;
			int j;
			for(j = 0; j < i; ++j){
				sum += (A(i,j) * x[j]);
			}
			for(j = i+1; j < n; ++j){
				sum += (A(i,j) * prev[j]);
			}
			x[i] = (b[i]-sum)/A(i,i);
		}
		double error = 0;
		// l_inf
		
		for(i = 0; i < n; ++i){
			if (error < abs(x[i]-prev[i]))
				error = abs(x[i]-prev[i]);
		}
		if(abs(error) <= epsilon){
			cout << "Gauss-Seidel method:" << endl;
			cout << "Number of iterations needed, " << iter 
				<< ", to get tolerance " << epsilon << endl; 			
			for(i = 0; i < n; i++)
				cout << x[i] << " ";
			cout << endl;
			end = 0;
		}
		else{
			for(i = 0; i < n; i++){
				prev[i] = x[i];
			}
			iter++;
		}

	}
	return 0;
}


int main(){

// Set number of unknowns in the problem
	int n = 80;
// Set the values of a and b, matrices
	/*double a_t[] = {-1, 0, 0, sqrt(2)/2, 1, 0, 0, 0,
			 0,-1, 0, sqrt(2)/2, 0, 0, 0, 0,
			 0, 0,-1, 0, 0, 0, 0.5, 0,
			 0, 0, 0, -0.5*sqrt(2), 0, -1, -0.5, 0,
			 0, 0, 0, 0,-1, 0, 0, 1,
			 0, 0, 0, 0, 0, 1, 0, 0,
			 0, 0, 0, -0.5*sqrt(2), 0, 0, 0.5*sqrt(3), 0,
			 0, 0, 0, 0, 0, 0,-0.5*sqrt(3),-1};
	double b_t[] = { 0, 0, 0, 0, 0, 10000, 0, 0};
	*/int i; int j;
	for(i = 0; i<n; ++i){
		for(j = 0; j<n; ++j){
			if(j == i)
				A(i,j) = 2*i;
			else if(j == i+2 || j == i-2)
				A(i,j) = 0.5*i;
			else if(j == i+4 || j == i-4)
				A(i,j) = 0.25*i;
			else
				A(i,j) = 0;	
		}
	}
	for(i =0; i<n; ++i)
		b[i] = 3.1415926535897;
	//copy(a_t, a_t+(n*n), a);
	//copy(b_t, b_t+n, b);
// Set the number of iterations
	double epsilon = pow(10, -5);
// Run the Jacobi and/or Gauss-Seidel methods
	jacobi(n, epsilon);
	gauss_seidel(n, epsilon);
	epsilon = pow(10, -8);	
	//jacobi(n, epsilon);
	//gauss_seidel(n, epsilon);
	return 0;
}
