// Lab01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Matrix.h"
#include "Fraction.h"
#include "Polinom.h"

using namespace std;
int main()
{
	/*Fraction<int, int> frac1, frac2;
	cin >> frac1;
	cin >> frac2;
	cout << frac1 + frac2 << endl;
	frac2 = frac1;
	cout << frac1 << endl << frac2;

	Matrix<double, 2> matr1, matr2;
	cin >> matr1;
	cin >> matr2;
	cout << matr1 + matr2 << endl;
	cout << matr1.reverse();*/

	Polinom<int, int> pol, tmpPol;
	pol.addMonom(1, 2, 'x');
	pol.addMonom(3, 4, 'x');
	cout << pol + pol;
	return 0;
}