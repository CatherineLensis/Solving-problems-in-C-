#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double F(double x)
{
	return 1 / x;
}

double Lagrange(double a, double b, double z)
{
	const int n = 16;
	double h = (b - a) / n;
	double x[n]{};
	double y[n]{};
	for (int i = 0; i <= n - 1; i++)
	{
		x[i] = a + i * h;
	}
	for (int i = 0; i <= n - 1; i++)
	{
		y[i] = F(x[i]);
	}

	double S = 0;
	for (int i = 0; i <= n; i++)
	{
		double P = 1;
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				P *= (z - x[j]) / (x[i] - x[j]);
			}
		}
		S = S + y[i] * P;
	}
	return S;
}

int main()
{
	double a = 0.1;
	double b = 1.1;

	double H = 0.1;
	const double N = (b - a) / H;
	double X[100]{};

	for (int i = 0; i <= N; i++)
	{
		X[i] = a + i * H;
	}

	std::ofstream out;
	out.open("ReadMe.txt");
	if (out.is_open())
	{
		for (int k = 0; k <= N; k++)
		{
			out << "X" << k << " = " << X[k] << "\t\t\t" <<
				"F(X" << k << ") = " << Lagrange(a, b, X[k]) << "\t\t\t" <<
				"f(X" << k << ")-F(X" << k << ") = " << F(X[k]) - Lagrange(a, b, X[k]) << endl;
		}
	}
	out.close();

	for (int k = 0; k <= N; k++)
	{
		cout << "X" << k << " = " << X[k] << "\t\t\t" <<
			"F(X" << k << ") = " << Lagrange(a, b, X[k]) << "\t\t\t" <<
			"f(X" << k << ")-F(X" << k << ") = " << F(X[k]) - Lagrange(a, b, X[k]) << endl;
	}

	return 0;
}