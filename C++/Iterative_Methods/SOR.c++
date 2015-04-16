/*
	C++ code implementing Iterative Method SOR 
*/

#include <iostream>
#include <complex>
#include <math.h>

using namespace std;

// Assuming max unknowns of 100
#define MAX_N 100
#define A(i,j) a[(i) * n + (j)]

double a[MAX_N*MAX_N];
double b[MAX_N];

int jacobi(int n, double epsilon, int max_iter, double init){
	double x[n];
	double prev[n];
	int i;
	for(i = 0; i < n; ++i)
		x[i] = prev[i] = init;
	int iter = 1;
	bool end = 0;
	while(!end){
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
		if((max_iter != 0 && iter >= max_iter) ||
		 		(max_iter == 0 && abs(error) <= epsilon)){
			cout << "    Iteration " << iter << ": ";
			for(i = 0; i < n; i++)
				cout << x[i] << " ";
			cout << endl;
			end = 1;
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

int gauss_seidel(int n, double epsilon, int max_iter, double init){
	double x[n];
	double prev[n];
	int i;
	for(i = 0; i < n; ++i)
		x[i] = prev[i] = init;
	int iter = 1;
	bool end = 0;
	while(!end){
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
		if((max_iter != 0 && iter >= max_iter) || 
				(max_iter == 0 && abs(error) <= epsilon)){
			cout << "    Iteration " << iter << ": ";
			for(i = 0; i < n; i++)
				cout << x[i] << " ";
			cout << endl;
			end = 1;
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

int sor(int n, int max_iter, double w, double epsilon, double init){
	double x[n];
	double prev[n];
	int i;
	for(i = 0; i < n; ++i)
		x[i] = prev[i] = init;
	int iter = 1;
	int end = 0;
	while(!end){
		for(i = 0; i < n; ++i){
			double sum = 0;
			int j;
			for(j = 0; j <= i-1; ++j)
				sum -= (A(i,j) * x[j]);
			for(j = i+1; j < n; ++j)
				sum -= (A(i,j) * prev[j]);
			sum += b[i];
			sum *= (w/A(i,i));
			sum += ((1-w)*prev[i]);
			x[i] = sum;
		}
		double error = 0;
		// l_inf
		for(i = 0; i < n; ++i){
			if (error < abs(x[i]-prev[i]))
				error = abs(x[i]-prev[i]);
		
		}
		// Set max_iter to 0 if using epsilon
		if((max_iter != 0 && iter >= max_iter) || 
				(max_iter == 0 && abs(error) <= epsilon)){
			cout << "    Iteration " << iter << ": ";
			for(i = 0; i < n; i++)
				cout << x[i] << " ";
			cout << endl;
			end = 1;
		}
		/*
		else{
			cout << "    Iteration " << iter << ": ";
			for(i = 0; i < n; i++)
				cout << x[i] << " ";
			cout << endl;
		}
		*/
		for(i = 0; i < n; i++)
			prev[i] = x[i];
		iter++;
	}
	return 0;
}


int main(){

	int n;
	double epsilon;
	int i; int j;

//-----//
// 7.4 //
//-----//

// 1a)
	n = 3;
	double a_t_1a[] = { 3,-1, 1,
			 			3, 6, 2,
			 			3, 3, 7};
	double b_t_1a[] = { 1, 0, 4};
	copy(a_t_1a, a_t_1a+(n*n), a);
	copy(b_t_1a, b_t_1a+n, b);
	cout << "\n1a)" << endl;
	sor(n, 2, 1.1, 0, 0);
// 1b)
	n = 3;
	double a_t_1b[] = {10,-1, 0,
			 		   -1,10,-2,
			 		    0,-2,10};
	double b_t_1b[] = { 9, 7, 6};
	copy(a_t_1b, a_t_1b+(n*n), a);
	copy(b_t_1b, b_t_1b+n, b);
	cout << "\n1b)" << endl;
	sor(n, 2, 1.1, 0, 0);
// 1c)
	n = 4;
	double a_t_1c[] = {10, 5, 0, 0,
			 		    5,10,-4, 0,
			 		    0,-4, 8,-1,
			 		    0, 0,-1, 5};
	double b_t_1c[] = { 6, 25, -11, -11};
	copy(a_t_1c, a_t_1c+(n*n), a);
	copy(b_t_1c, b_t_1c+n, b);
	cout << "\n1c)" << endl;
	sor(n, 2, 1.1, 0, 0);
// 1d)
	n = 5;
	double a_t_1d[] = { 4, 1, 1, 0, 1,
			 		   -1,-3, 1, 1, 0,
			 		    2, 1, 5,-1,-1,
			 		   -1,-1,-1, 4, 0,
			 		    0, 2,-1, 1, 4};
	double b_t_1d[] = { 6, 6, 6, 6, 6};
	copy(a_t_1d, a_t_1d+(n*n), a);
	copy(b_t_1d, b_t_1d+n, b);
	cout << "\n1d)" << endl;
	sor(n, 2, 1.1, 0, 0);

// 2a)
	n = 3;
	double a_t_2a[] = { 4, 1,-1,
			 		   -1, 3, 1,
			 			2, 2, 5};
	double b_t_2a[] = { 5,-4, 1};
	copy(a_t_2a, a_t_2a+(n*n), a);
	copy(b_t_2a, b_t_2a+n, b);
	cout << "\n2a)" << endl;
	sor(n, 2, 1.1, 0, 0);
// 2b)
	n = 3;
	double a_t_2b[] = {-2, 1, 0.5,
			 		    1,-2,-0.5,
			 			0, 1,   2};
	double b_t_2b[] = { 4,-4, 0};
	copy(a_t_2b, a_t_2b+(n*n), a);
	copy(b_t_2b, b_t_2b+n, b);
	cout << "\n2b)" << endl;
	sor(n, 2, 1.1, 0, 0);
// 2c)
	n = 4;
	double a_t_2c[] = { 4, 1,-1, 1,
			 		    1, 4,-1,-1,
			 		   -1,-1, 5, 1,
			 		    1,-1, 1, 3};
	double b_t_2c[] = {-2,-1, 0, 1};
	copy(a_t_2c, a_t_2c+(n*n), a);
	copy(b_t_2c, b_t_2c+n, b);
	cout << "\n2c)" << endl;
	sor(n, 2, 1.1, 0, 0);
// 2d)
	n = 6;
	double a_t_2d[] = { 4,-1, 0, 0, 0, 0,
			 		   -1, 4,-1, 0, 0, 0,
			 		    0,-1, 4, 0, 0, 0,
			 		    0, 0, 0, 4,-1, 0,
			 		    0, 0, 0,-1, 4,-1,
			 		    0, 0, 0, 0,-1, 4};
	double b_t_2d[] = { 0, 5, 0, 6,-2, 6};
	copy(a_t_2d, a_t_2d+(n*n), a);
	copy(b_t_2d, b_t_2d+n, b);
	cout << "\n2d)" << endl;
	sor(n, 2, 1.1, 0, 0);

// 3a)
	n = 3;
	copy(a_t_1a, a_t_1a+(n*n), a);
	copy(b_t_1a, b_t_1a+n, b);
	cout << "\n3a)" << endl;
	sor(n, 2, 1.3, 0, 0);
// 3b)
	n = 3;
	copy(a_t_1b, a_t_1b+(n*n), a);
	copy(b_t_1b, b_t_1b+n, b);
	cout << "\n3b)" << endl;
	sor(n, 2, 1.3, 0, 0);
// 3c)
	n = 4;
	copy(a_t_1c, a_t_1c+(n*n), a);
	copy(b_t_1c, b_t_1c+n, b);
	cout << "\n3c)" << endl;
	sor(n, 2, 1.3, 0, 0);
// 3d)
	n = 5;
	copy(a_t_1d, a_t_1d+(n*n), a);
	copy(b_t_1d, b_t_1d+n, b);
	cout << "\n3d)" << endl;
	sor(n, 2, 1.3, 0, 0);

// 4a)
	n = 3;
	copy(a_t_2a, a_t_2a+(n*n), a);
	copy(b_t_2a, b_t_2a+n, b);
	cout << "\n4a)" << endl;
	sor(n, 2, 1.3, 0, 0);
// 4b)
	n = 3;
	copy(a_t_2b, a_t_2b+(n*n), a);
	copy(b_t_2b, b_t_2b+n, b);
	cout << "\n4b)" << endl;
	sor(n, 2, 1.3, 0, 0);
// 4c)
	n = 4;
	copy(a_t_2c, a_t_2c+(n*n), a);
	copy(b_t_2c, b_t_2c+n, b);
	cout << "\n4c)" << endl;
	sor(n, 2, 1.3, 0, 0);
// 4d)
	n = 6;
	copy(a_t_2d, a_t_2d+(n*n), a);
	copy(b_t_2d, b_t_2d+n, b);
	cout << "\n4d)" << endl;
	sor(n, 2, 1.3, 0, 0);

// 5a)
	epsilon = pow(10, -3);
	n = 3;
	copy(a_t_1a, a_t_1a+(n*n), a);
	copy(b_t_1a, b_t_1a+n, b);
	cout << "\n5a)" << endl;
	sor(n, 0, 1.2, epsilon, 0);
// 5b)
	n = 3;
	copy(a_t_1b, a_t_1b+(n*n), a);
	copy(b_t_1b, b_t_1b+n, b);
	cout << "\n5b)" << endl;
	sor(n, 0, 1.2, epsilon, 0);
// 5c)
	n = 4;
	copy(a_t_1c, a_t_1c+(n*n), a);
	copy(b_t_1c, b_t_1c+n, b);
	cout << "\n5c)" << endl;
	sor(n, 0, 1.2, epsilon, 0);
// 5d)
	n = 5;
	copy(a_t_1d, a_t_1d+(n*n), a);
	copy(b_t_1d, b_t_1d+n, b);
	cout << "\n5d)" << endl;
	sor(n, 0, 1.2, epsilon, 0);

// 6a)
	epsilon = pow(10, -3);
	n = 3;
	copy(a_t_2a, a_t_2a+(n*n), a);
	copy(b_t_2a, b_t_2a+n, b);
	cout << "\n6a)" << endl;
	sor(n, 0, 1.2, epsilon, 0);
// 6b)
	n = 3;
	copy(a_t_2b, a_t_2b+(n*n), a);
	copy(b_t_2b, b_t_2b+n, b);
	cout << "\n6b)" << endl;
	sor(n, 0, 1.2, epsilon, 0);
// 6c)
	n = 4;
	copy(a_t_2c, a_t_2c+(n*n), a);
	copy(b_t_2c, b_t_2c+n, b);
	cout << "\n6c)" << endl;
	sor(n, 0, 1.2, epsilon, 0);
// 6d)
	n = 6;
	copy(a_t_2d, a_t_2d+(n*n), a);
	copy(b_t_2d, b_t_2d+n, b);
	cout << "\n6d)" << endl;
	sor(n, 0, 1.2, epsilon, 0);

// 7b)
	n = 3;
	double optimal_w = 2.0/(1.0+sqrt(19.0/20.0));
	epsilon = pow(10, -3);
	copy(a_t_1b, a_t_1b+(n*n), a);
	copy(b_t_1b, b_t_1b+n, b);
	cout << "\n7b)" << endl;
	// Did same thing for 7c and 8d, 
	// didnt know if you wanted it like part 1/2 or 5/6
	sor(n, 2, optimal_w, 0, 0);
	sor(n, 0, optimal_w, epsilon, 0);
// 7c)
	n = 4;
	optimal_w = 1.53499;
	epsilon = pow(10, -3);
	copy(a_t_1c, a_t_1c+(n*n), a);
	copy(b_t_1c, b_t_1c+n, b);
	cout << "\n7c)" << endl;
	sor(n, 2, optimal_w, 0, 0);
	sor(n, 0, optimal_w, epsilon, 0);

// 8d)
	n = 6;
	optimal_w = 1.045;
	epsilon = pow(10, -3);
	copy(a_t_2d, a_t_2d+(n*n), a);
	copy(b_t_2d, b_t_2d+n, b);
	cout << "\n8d)" << endl;
	sor(n, 2, optimal_w, 0, 0);
	sor(n, 0, optimal_w, epsilon, 0);

// 10)
	n = 8;
	epsilon = pow(10, -2);
	copy(a_t_18, a_t_18+(n*n), a);
	copy(b_t_18, b_t_18+n, b);
	cout << "\n10)" << endl;
	sor(n, 0, 1.25, epsilon, 1);

// 11)
	n = 80;
	epsilon = pow(10, -5);
	for(i = 0; i<n; ++i){
		for(j = 0; j<n; ++j){
			if(j == i)
				A(i,j) = 2 * (i+1);
			else if(j == i+2 || j == i-2)
				A(i,j) = 0.5 * (i+1);
			else if(j == i+4 || j == i-4)
				A(i,j) = 0.25 * (i+1);
			else
				A(i,j) = 0;	
		}
	}
	for(i =0; i<n; ++i)
		b[i] = 3.1415926535897;	
	cout << "\n11)" << endl;
	sor(n, 0, 1.2, epsilon, 0);


	return 0;
}
