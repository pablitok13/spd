// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

//#include "pch.h"
#include <iostream>
#include <algorithm>

	using namespace std;


	int main() {
		int zad[] = { 0,1,2,3,4 };
		int bestperm[5];
		int m1[] = { 4, 4, 10, 6, 2 };
		int m2[] = { 5, 1, 4, 10, 3 };
		int n = sizeof(zad) / sizeof(int);
		int i = 0;
		long long silnia = 1;
		int c[5];
		int czas2 = 99999999999;
		int cmax = 0;

		//sort(zad, zad + n - 1);


		for (i = n; i > 1; i--)
		{
			silnia = silnia * i;
		}

		do {
			for (i = 0; i < n; i++)
			{
				cout << zad[i] + 1 << ' ';

			}

			c[0] = m1[zad[0]] + m2[zad[0]];


			if (c[0] > m1[zad[0]] + m1[zad[1]])
				c[1] = c[0] + m2[zad[1]];
			else
				c[1] = m1[zad[0]] + m1[zad[1]] + m2[zad[1]];



			if (c[1] > m1[zad[0]] + m1[zad[1]] + m1[zad[2]])
				c[2] = c[1] + m2[zad[2]];
			else
				c[2] = m1[zad[0]] + m1[zad[1]] + m1[zad[2]] + m2[zad[2]];


			if (c[2] > m1[zad[0]] + m1[zad[1]] + m1[zad[2]] + m1[zad[3]])
				c[3] = c[2] + m2[zad[3]];
			else
				c[3] = m1[zad[0]] + m1[zad[1]] + m1[zad[2]] + m1[zad[3]] + m2[zad[3]];



			if (c[3] > m1[zad[0]] + m1[zad[1]] + m1[zad[2]] + m1[zad[3]] + m1[zad[4]])
				c[4] = c[3] + m2[zad[4]];
			else
				c[4] = m1[zad[0]] + m1[zad[1]] + m1[zad[2]] + m1[zad[3]] + m1[zad[4]] + m2[zad[4]];

			cmax = c[4];

			if (czas2 > cmax) {
				czas2 = cmax;
				for (int j = 0; j < 5; ++j) {
					bestperm[j] = zad[j];
				}
			}
			cout << "Makespan = " << cmax << '\n';
			cout << '\n';


		} while (next_permutation(zad, zad + n));


		cout << "Elementow w tablicy: " << n << '\n';
		cout << "Mozliwych permutacji: " << silnia << '\n';
		cout << "Najlepszy czas: " << czas2 << endl;
		cout << "Najlepsza permutacja:" << endl;
		for (int j = 0; j < 5; ++j) {
			cout << bestperm[j] + 1 << ", ";
		}

		return 0;
	}
