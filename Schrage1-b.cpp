#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>  
#include "funkcje.cpp"

void SchrageS_kopiec(int N, int *R, int *P, int *Q, int &F) //schrage z przerwaniami na kopcu
{
	Kopiec tab;
	bool wykonywanieNaMaszynie = false;
	int qmax = 0;
	int C = 0, f = 0;
	int Rs[500], Qs[500];
	int transport = 0;
	int wykonanie = 0;
	int stygniecie = 0;
	int czaskoncowy = 0;
	SortRmin(R, Rs, N); ////sortowanie po R
	SortQmax(Q, Qs, N);//sortowanie po Q
	
	for(int i = 0; i < N; ++i ){
		while(R[Rs[i]] > czaskoncowy){		//sprawdzamy czy czas transportu jest wiekszy niz czas kiedy konczymy aktualne zadanie
			if(tab.czypuste()) {//zerujemy pierwsze zadanie
				transport = 0;
				wykonanie = 0;
				stygniecie = 0;
				
				break;
			}
			else{ //zdejmujemy ostatnie zadanie z kopca
				qmax = max(qmax,czaskoncowy + stygniecie );
				tab.Zdejmij(transport, wykonanie, stygniecie);
				qmax = max(qmax,czaskoncowy + stygniecie );
				czaskoncowy = czaskoncowy + wykonanie;
				//czas zakonczenia 
			}
		}
		if(Q[Rs[i]] > stygniecie){// sprawdzamy czy kolejne zadanie ktore przyszlo ma Q mniejsze od aktualnego, jesli tak to je wykonujemy
			wykonanie = czaskoncowy  - R[Rs[i]];
			if(wykonanie > 0){// jesli przerwane zadanie ma jeszcze cos do wykonania pozniej, to wrzucamy je na stos
				tab.Dodaj(	transport,	wykonanie,	stygniecie);
			}
				qmax = max(qmax,czaskoncowy + stygniecie ); // zliczamy qmaxa do kolejnego zadania 
				transport = R[Rs[i]];
				wykonanie = P[Rs[i]];
				stygniecie = Q[Rs[i]];
				czaskoncowy =  R[Rs[i]] + P[Rs[i]];
				qmax = max(qmax,czaskoncowy + stygniecie );
		}
		
		else {
			tab.Dodaj(R[Rs[i]], P[Rs[i]], Q[Rs[i]]);	//dodajemy kolejny element 
		}	

	
	}// po zakonczeniu petli zajmujemy sie przerwanymi zadaniami 
			while(!tab.czypuste()){
			qmax = max(qmax,czaskoncowy + stygniecie );
			tab.Zdejmij(transport, wykonanie, stygniecie);   // zdejmuje z kopca zadania ktore zostaly(posegregowane po Q) 
			czaskoncowy = czaskoncowy + wykonanie;
			qmax = max(qmax,czaskoncowy + stygniecie );
	}
	czaskoncowy = qmax;
	cout<<endl<<"Schrage z przerwaniami z kopca  = ";// wypisuje juz koncowe zadanie 
	cout<< qmax<<endl;		
	F = czaskoncowy;
	

}

void SchrageS_tablica(int N, int *R, int *P, int *Q, int &F) // schrage z przerwaniami na tablicy 
{
	TablicaPriorytetowa tab;
	bool wykonywanieNaMaszynie = false;
	int qmax = 0;
	int C = 0, f = 0;
	int Rs[500], Qs[500];
	int transport = 0;
	int wykonanie = 0;
	int stygniecie = 0;
	int czaskoncowy = 0;
	SortRmin(R, Rs, N);
	SortQmax(Q, Qs, N);
	
	for(int i = 0; i < N; ++i ){
		while(R[Rs[i]] > czaskoncowy){	
			if(tab.czypuste()) {
				transport = 0;
				wykonanie = 0;
				stygniecie = 0;
				
				break;
			}
			else{
				qmax = max(qmax,czaskoncowy + stygniecie );
				tab.Zdejmij(transport, wykonanie, stygniecie);
				qmax = max(qmax,czaskoncowy + stygniecie );
				czaskoncowy = czaskoncowy + wykonanie;
				
			}
		}
		if(Q[Rs[i]] > stygniecie){// sluzy do zapamietania ile zadania sie wykonalo i jesli cos zostalo to wrzucamy to na kopiec 
			wykonanie = czaskoncowy  - R[Rs[i]];
			if(wykonanie > 0){
				tab.Dodaj(	transport,	wykonanie,	stygniecie);
			}
				qmax = max(qmax,czaskoncowy + stygniecie ); // jesli nic nie zostalo to lecimy dalej 
				transport = R[Rs[i]];
				wykonanie = P[Rs[i]];
				stygniecie = Q[Rs[i]];
				czaskoncowy =  R[Rs[i]] + P[Rs[i]];
				qmax = max(qmax,czaskoncowy + stygniecie );
		}
		
		else {
			tab.Dodaj(R[Rs[i]], P[Rs[i]], Q[Rs[i]]);	
		}	

	
	}
			while(!tab.czypuste()){
			qmax = max(qmax,czaskoncowy + stygniecie );
			tab.Zdejmij(transport, wykonanie, stygniecie);
			czaskoncowy = czaskoncowy + wykonanie;
			qmax = max(qmax,czaskoncowy + stygniecie );
	}
	czaskoncowy = qmax;
	cout<<endl<<"Schrage z przerwaniami z tablicy = ";
	cout<< qmax<<endl;		
	F = czaskoncowy;
	

}


void Schrage_kopiec(int N, int *R, int *P, int *Q, int &F, int *X)//schrage bez przerwan na kopcu
{
	Kopiec2 tab;
	int qmax = 0;
	int C = 0, f = 0;
	int Rs[500], Qs[500];
	int transport = 0;
	int wykonanie = 0;
	int stygniecie = 0;
	SortRmin(R, Rs, N);
	SortQmax(Q, Qs, N);
	int j = 0;
	for(int i = 0; i < N; ++i ){
		while((j < N) && (R[Rs[j]] <= C)){
			tab.Dodaj(R[Rs[j]], P[Rs[j]], Q[Rs[j]],Rs[j]);// wrzucamy wszystko na kopiec sortowane po R, 
			++j;
		}
		if(tab.czypuste()){
			C = R[Rs[j]];
			while((j < N) && (R[Rs[j]] <= C)){
				tab.Dodaj(R[Rs[j]], P[Rs[j]], Q[Rs[j]],Rs[j]);
				++j;
			}
		}
		tab.Zdejmij(transport, wykonanie, stygniecie, X[i]) ;

		if (R[X[i]] >= C) C = R[X[i]] + P[X[i]]; // sprawdzamy laczny czas wykonania sie na maszynie(bez stygniecia)
		else C = C + P[X[i]];
		f = max(C + Q[X[i]], f);
	}
	F = f;
//	cout<<"kolejnosc:"<<endl;
//	for(int i = 0; i < N; ++i){
//		cout<<X[i] + 1 <<", ";
//	}
//	cout<<endl;
}

void Schrage_tablica(int N, int *R, int *P, int *Q, int &F, int *X)//schrage bez przerwan na tablicy
{
	TablicaPriorytetowa2 tab;
	int qmax = 0;
	int C = 0, f = 0;
	int Rs[500], Qs[500];
	int transport = 0;
	int wykonanie = 0;
	int stygniecie = 0;
	SortRmin(R, Rs, N);
	SortQmax(Q, Qs, N);
	int j = 0;
	for(int i = 0; i < N; ++i ){
		while((j < N) && (R[Rs[j]] <= C)){
			tab.Dodaj(R[Rs[j]], P[Rs[j]], Q[Rs[j]],Rs[j]);
			++j;
		}
		if(tab.czypuste()){
			C = R[Rs[j]];
			while((j < N) && (R[Rs[j]] <= C)){
				tab.Dodaj(R[Rs[j]], P[Rs[j]], Q[Rs[j]],Rs[j]);
				++j;
			}
		}
		tab.Zdejmij(transport, wykonanie, stygniecie, X[i]) ;

		if (R[X[i]] >= C) C = R[X[i]] + P[X[i]];
		else C = C + P[X[i]];
		f = max(C + Q[X[i]], f);
	}
	F = f;
	//cout<<"kolejnosc:"<<endl;
	//for(int i = 0; i < N; ++i){
//		cout<<X[i] + 1 <<", ";
//	}
//	cout<<endl;
}

int main(int argc, char *argv[])
{
    clock_t t1,t2,t3,t4,t5,t6,t7,t8;
	int N, R[500], P[500], Q[500], F=0, X[500], wynik=0;
	ifstream data("mak.txt");
	for (int i = 0;i < 1;++i) {

		data >> N;
		for (int i = 0;i < N;i++)	data >> R[i] >> P[i] >> Q[i];
		
		t1= clock();
		SchrageS_tablica(N, R, P, Q, F);
		t2 = clock();
		cout<<"Czas schrage z przerwaniami na tablicy: ";
		cout<<(float)(t2-t1)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
		
		
		t3=clock();
		Schrage_tablica(N, R, P, Q, F, X);
		t4=clock();
		cout<<"Czas schrage bez przerwan na tablicy: ";
		cout<<(float)(t4-t3)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
		cout << "Schrage = " << F << endl;
		F = 0;
	
	    t5 = clock();
		SchrageS_kopiec(N, R, P, Q, F);
		t6= clock();
		cout<<"Czas schrage z przerwaniami na kopcu: ";
		cout<<(float)(t6-t5)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
		
		t7 = clock();
		Schrage_kopiec(N, R, P, Q, F, X);
		t8 = clock();
		cout<<"Czas schrage bez przerwan na kopcu: ";
		cout<<(float)(t6-t5)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
		cout << "Schrage = " << F << endl;
		F = 0;
		
		//getchar();
	}
	system("pause");
	return 0;
}

