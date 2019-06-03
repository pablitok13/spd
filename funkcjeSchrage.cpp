#include <iostream>
#include <fstream>
#include <cmath>
#include <windows.h>
#include "funkcjeSchrage.h"

using namespace std;



int Schrage(int R[], int P[], int Q[],   int *X, int  N, int ostatni[])
{
	int t=0; // czas
	int l=0; // liczba wykonanych zadan
	int najQ=-1;
	int lpossible=0;
	int indeks=0;
	int c=0;
	int index_tab_zad=0;



	while(l!=N)
	{

		lpossible=0;
		for(int i=0;i<N;i++)
		{
			if(R[i]<=t && P[i]!=0)
			{

				lpossible++;
				if(Q[i]>najQ)
				{
					najQ=Q[i];
					indeks = i;
				}
			}
		}


		if(lpossible==0)
		{
		 	int najmniejsza=99999;
			for (int i=0; i<N; i++)
			{
				if(R[i]-t<najmniejsza && P[i]!=0){ najmniejsza=R[i]-t; 	}
			}

			t+=najmniejsza;
	 	}

		else
		{
			t+=P[indeks];
			c=max( (t+najQ) ,c);
			if(c == t+najQ) {ostatni[0] = index_tab_zad;}
			X[index_tab_zad]=indeks;
			index_tab_zad++;
			P[indeks]=0;
			l++;
		}

		lpossible==0;
		najQ=-1;
	}
	return c;
}

int Schrage_przerwania(int R[], int P[], int Q[], int N)
{

	int t=0; // czas
	int l=0; // liczba wykonanych zadan
	int najQ=-1;
	int lpossible=0;
	int indeks=0;
	int c=0;


	while(l!=N)
	{

		for(int i=0;i<N;i++)
		{
			if(R[i]<=t && P[i]!=0)
			{

				lpossible++;
				if(Q[i]>najQ)
				{
					najQ=Q[i];
					indeks = i;
				}
			}
		}


		if(lpossible==0)
		{

			int najmniejsza=99999;
			for (int i=0; i<N; i++)
			{
				if(R[i]-t<najmniejsza && P[i]!=0){ najmniejsza=R[i]-t; 	}
			}

			t+=najmniejsza;
		}

		else
		{
			int Rmin=999999;
			int indmin=-1;

			for(int i=0;i<N;i++)
			{

				if(R[i]>=t && R[i]<=t+P[indeks] && R[i]<=Rmin)
				{

					if(Q[i]>najQ)
					{

						Rmin=R[i];
						indmin = i;
					}
				}
			}


			if(Rmin!=999999)
			{

				P[indeks] = P[indeks] + t - Rmin;
				if(P[indeks]==0){l++;c = max( (t+P[indeks]+najQ),c);}
				t = Rmin;
				Rmin=999999;
			}

			else
			{
				t+=P[indeks];
				c=max( (t+najQ) ,c);
				P[indeks]=0;
				l++;
			}

			Rmin=999999;
		}

		lpossible=0;
		najQ=-1;
	}

	return c;
}
