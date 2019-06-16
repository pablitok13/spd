#include <iostream>
#include <fstream>
#include <cmath>
#include <windows.h>
#include "funkcjeSchrage.h"

using namespace std;

void Carlier (int R[], int P[], int Q[], int *X, int  N, int LB, int out[], int koniec, int powtorka)
{
	int N_b; //ilosc zadan
	int *R_b = new int [N]; //transport
	int *P_b = new int [N]; //wykonanie
	int *Q_b = new int [N]; //stygniecie
	int tab_zer[N];
	int tab_last[0];
	int tab_first[0];
	koniec = 0;



    //przypisujemy kolejnosc zadan z Schrage
	for(int i=0;i<N;i++)
	{
		R_b[i] = R[i];
		P_b[i] = P[i];
		Q_b[i] = Q[i];
		N_b = N;
	}
	tab_last[0]=0;


	//Przypisanie UB - cmax z schrage
	int UB = Schrage(R_b,P_b,Q_b,X,N_b,tab_last);



	if(koniec == 0)
	{
	    // czy LB - schrage z przerwaniami wieksze od UB
		if(LB == UB) {koniec = 1; out[0] = UB;}
		int last = tab_last[0];


		//zad A
		if(R[X[0]] == 0) {
                tab_zer[0] = 1;
        } else {
            tab_zer[0] = 0;
            }
		int T = R[X[0]]+P[X[0]];

		for(int i=1;i<N;i++)
		{
			if(R[X[i]] > T) {
                tab_zer[i] = 0;
                T=R[X[i]]+P[X[i]];
            }
			else {
                tab_zer[i] = 1;
                T+=P[X[i]];
                }
		}

        //zad B
		for(int i=last-1; i>0; i--)
		{
			if(tab_zer[i] == 0)
                {
                    tab_first[0] = i;
                    break;
                }
			if(Q[X[i]] < Q[X[last]])
                {
                    tab_first[0] = i;
                    break;
                }
		}
		int first = tab_first[0];

		int Rk = 999999;
		int Pk = 0;
		int Qk = 999999;


		//zad C
		for(int i=first+1; i<=last; i++)
		{
			if(R[X[i]] < Rk) {
                    Rk = R[X[i]];
                }
			Pk += P[X[i]];
			if(Q[X[i]] < Qk) {
                    Qk = Q[X[i]];

                }
		}

		//Hk - Rk - najmn R, Qk - najmn
		int Hk = Rk + Pk + P[X[first]] + Q[X[first]];
		int Hk_c = R[X[first]] + Pk + P[X[first]] + Qk;

		if(Hk_c != powtorka)
		{
			if(Hk < UB) {
                R[X[first]] = Rk+Pk;
                Carlier(R,P,Q,X,N,LB,out,koniec,Hk_c);
                }
			if(Hk_c < UB) {
                Q[X[first]] = Qk+Pk;
                Carlier(R,P,Q,X,N,LB,out,koniec,Hk_c);
                }
			if(Hk >= UB && Hk_c >= UB)
                if(out[0] > UB)
                out[0] = UB;
		}

	}

}




int main() {

	int N, N1, N_b;
	int tab_last[0];
	int *out = new int[0];
	int koniec = 0;
	int powtorka = 0;


	ifstream data("data.txt");

    string buffer;

	for(int i=0; i<9; i++)
	{
    if (i == 0)
        while(buffer!="data.000:") data >> buffer;
    if (i == 1)
        while(buffer!="data.001:") data >> buffer;
    if (i == 2)
        while(buffer!="data.002:") data >> buffer;
    if (i == 3)
        while(buffer!="data.003:") data >> buffer;
    if (i == 4)
        while(buffer!="data.004:") data >> buffer;
    if (i == 5)
        while(buffer!="data.005:") data >> buffer;
    if (i == 6)
        while(buffer!="data.006:") data >> buffer;
    if (i == 7)
        while(buffer!="data.007:") data >> buffer;
    if (i == 8)
        while(buffer!="data.008:") data >> buffer;

    data >> N;
    N1=N;

    int *R = new int [N];
	int *P = new int [N];
	int *Q = new int [N];
	int *X = new int [N];
	int *R_b = new int [N];
	int *P_b = new int [N];
	int *Q_b = new int [N];

    for(int i=0;i<N;i++) {data >> R[i] >> P[i] >> Q[i];}


	for(int i=0;i<N1;i++)
	{
		R_b[i] = R[i];
		P_b[i] = P[i];
		Q_b[i] = Q[i];
	}
	N_b = N;

    int LB = Schrage_przerwania(R_b,P_b,Q_b,N_b);

	for(int i=0;i<N;i++)
	{
		R_b[i] = R[i];
		P_b[i] = P[i];
		Q_b[i] = Q[i];
		N_b = N;
	}
	tab_last[0]=0;

	int UB = Schrage(R_b,P_b,Q_b,X,N_b,tab_last);

	out[0] = UB;

	Carlier(R,P,Q,X,N1,LB,out,koniec,powtorka);


    cout << "Proponowana kolejnosc: " << endl;
    for(int i=0; i<N1;i++)
    {
    	cout << X[i] << " " ;
	}
	cout << endl << endl;

	cout << "Obliczony cmax: " << out[0] << endl<<endl;
	}

}
