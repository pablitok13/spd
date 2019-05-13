#include <cstdlib>
#include <iostream>


using namespace std;

int ZnajdzNaj(int *tab, int roz)
{
	int x = tab[0], el = 0;

	for (int i = 0; i < roz; ++i)
	{
		if (x < tab[i])
		{
			x = tab[i];
			el = i;
		}
	}
	return el;
}

int ZnajdzMin(int *tab, int roz)
{
	int x = tab[0], el = 0;
	for (int i = 0; i < roz; ++i)
	{
		if (x > tab[i])
		{
			x = tab[i];
			el = i;
		}
	}
	return el;
}



void SortQmax(int *tab , int *tabsort, int N)
{
	int kopia_tab[500];
	for (int j = 0; j < N; ++j) {
		kopia_tab[j] = tab[j];
	}
	for (int i = 0;i < N;++i) {
		tabsort[i] = ZnajdzNaj(kopia_tab, N);
		//cout << tabsort[i] << " ";
			kopia_tab[tabsort[i]] = -1; // umowne usuniecie elementu
	}
}

void SortRmin(int *tab, int *tabsort, int N)
{
	int kopia_tab[500];
	for (int j = 0; j < N; ++j) {
		kopia_tab[j] = tab[j];
	}
	for (int i = 0;i < N;++i) {
		tabsort[i] = ZnajdzMin(kopia_tab, N);
			kopia_tab[tabsort[i]] = 999999999; // umowne usuniecie elementu
	}
}

int Licz(int N, int *R, int *P, int *Q, int *X)
{
	int C = 0, f = 0;

	for (int i = 0; i<N; ++i) {

		if (R[X[i]] >= C) C = R[X[i]] + P[X[i]];
		else C = C + P[X[i]];
		f = max(C + Q[X[i]], f);
	}

	return f;
}


class Kopiec{
	private :
		int Tab[3][500]; //R P Q
		int Size;
		
		void Swap(int i1, int i2){
			int pom = Tab[0][i1];
			Tab[0][i1] = Tab[0][i2];
			Tab[0][i2] = pom;
			pom = Tab[1][i1];
			Tab[1][i1] = Tab[1][i2];
			Tab[1][i2] = pom;
			pom = Tab[2][i1];
			Tab[2][i1] = Tab[2][i2];
			Tab[2][i2] = pom;
		}
	public:
		Kopiec(){
			Size = 0;
			for(int i=0 ; i < 500; ++i){
				Tab[0][i] = 0;
				Tab[1][i] = 0;
				Tab[2][i] = 0;
			}
		}
		
		bool czypuste(){
			return !(Size > 0);
		}
		
		void Dodaj(int R, int P, int Q){
			++Size;
			int ind = Size;
			
			Tab[0][Size -1] = R;
			Tab[1][Size -1] = P;
			Tab[2][Size -1] = Q;
			while(1){
				if(ind / 2 > 0 ){
					if(Tab[2][ind -1] > Tab[2][ind /2 -1]){
						Swap(ind-1, ind/2-1);
						ind = ind /2;
					}
					else break;
				}
				else break;
			}
		}
		void Zdejmij(int &R, int &P, int &Q){
			R = Tab[0][0];
			P = Tab[1][0];
			Q = Tab[2][0];
			
			int ind = 1;
			Swap(0,Size-1);
			
			Tab[0][Size -1] = 0;
			Tab[1][Size -1] = 0;
			Tab[2][Size -1] = 0;
			--Size;
			while(1){
				if(Tab[2][ind *2 -1] >= Tab[2][ind *2]){
					if(Tab[2][ind -1] < Tab[2][ind * 2 -1]){
						Swap(ind-1, ind*2-1);
						ind = ind*2;
					}
					else break;
				}
				else {
					if(Tab[2][ind -1] < Tab[2][ind *2]){
						Swap(ind-1, ind*2);
						ind = ind*2 + 1;
					}
					else break;
				}
			}

			
		}
		void Wyswietl(){
			for(int i = 0; i < Size; ++i ){
				cout<<"R = " <<Tab[0][i]<<", ";
				cout<<"P = " <<Tab[1][i]<<", ";
				cout<<"Q = " <<Tab[3][i]<<endl;
			}
		}
			
};



class Kopiec2{
	private :
		int Tab[4][500]; //R P Q Ind
		int Size;
		
		void Swap(int i1, int i2){
			int pom = Tab[0][i1];
			Tab[0][i1] = Tab[0][i2];
			Tab[0][i2] = pom;
			pom = Tab[1][i1];
			Tab[1][i1] = Tab[1][i2];
			Tab[1][i2] = pom;
			pom = Tab[2][i1];
			Tab[2][i1] = Tab[2][i2];
			Tab[2][i2] = pom;
			pom = Tab[3][i1];
			Tab[3][i1] = Tab[3][i2];
			Tab[3][i2] = pom;
		}
	public:
		Kopiec2(){
			Size = 0;
			for(int i=0 ; i < 500; ++i){
				Tab[0][i] = 0;
				Tab[1][i] = 0;
				Tab[2][i] = 0;
				Tab[3][i] = 0;
			}
		}
		
		bool czypuste(){
			return !(Size > 0);
		}
		
		void Dodaj(int R, int P, int Q, int Ind){
			++Size;
			int ind = Size;
			
			Tab[0][Size -1] = R;
			Tab[1][Size -1] = P;
			Tab[2][Size -1] = Q;
			Tab[3][Size -1] = Ind;
			while(1){
				if(ind / 2 > 0 ){
					if(Tab[2][ind -1] > Tab[2][ind /2 -1]){
						Swap(ind-1, ind/2-1);
						ind = ind /2;
					}
					else break;
				}
				else break;
			}
		}
		void Zdejmij(int &R, int &P, int &Q, int &Ind){
			R = Tab[0][0];
			P = Tab[1][0];
			Q = Tab[2][0];
			Ind = Tab[3][0];
						
			int ind = 1;
			Swap(0,Size-1);
			
			Tab[0][Size -1] = 0;
			Tab[1][Size -1] = 0;
			Tab[2][Size -1] = 0;
			Tab[3][Size -1] = 0;
			--Size;
			while(1){
				if(Tab[2][ind *2 -1] >= Tab[2][ind *2]){
					if(Tab[2][ind -1] < Tab[2][ind * 2 -1]){
						Swap(ind-1, ind*2-1);
						ind = ind*2;
					}
					else break;
				}
				else {
					if(Tab[2][ind -1] < Tab[2][ind *2]){
						Swap(ind-1, ind*2);
						ind = ind*2 + 1;
					}
					else break;
				}
			}

			
		}
		void Wyswietl(){
			for(int i = 0; i < Size; ++i ){
				cout<<"R = " <<Tab[0][i]<<", ";
				cout<<"P = " <<Tab[1][i]<<", ";
				cout<<"Q = " <<Tab[2][i]<<", ";
				cout<<"Ind = " <<Tab[3][i]<<endl;
			}
		}
			
};

class TablicaPriorytetowa{
	public:
		int Liczebnosc;
		int Tab[3][500];  // R P Q [500]
		TablicaPriorytetowa(){for(int i = 0;i<500;++i){Tab[0][i] = -1;Tab[1][i] = -1; Tab[2][i] = -1;} Liczebnosc = 0;}
		void Dodaj(int R, int P, int Q){
			bool dodanie = false;
			++Liczebnosc;
			for(int i=0; i < Liczebnosc ; ++i){
				if(Q > Tab[2][i]){
					for(int j = Liczebnosc; j >= i; --j ){
						Tab[0][j+1] = Tab[0][j];
						Tab[1][j+1] = Tab[1][j];
						Tab[2][j+1] = Tab[2][j];
					}
					Tab[0][i] = R;
					Tab[1][i] = P;
					Tab[2][i] = Q;
					dodanie = true;
					break;
				}
				
			}
			if(!dodanie){
				Tab[0][Liczebnosc] = R;
				Tab[1][Liczebnosc] = P;
				Tab[2][Liczebnosc] = Q;				
			}
		}
		bool czypuste(){
			return !(Liczebnosc > 0);
		}
		void Zdejmij(int &R, int &P, int &Q){
			R = Tab[0][0] ;
			P = Tab[1][0] ;
			Q = Tab[2][0] ;
			for(int i = 0; i < Liczebnosc; ++i){
				Tab[0][i] = Tab[0][i + 1] ;
				Tab[1][i] = Tab[1][i + 1] ;
				Tab[2][i] = Tab[2][i + 1] ;
			}
			--Liczebnosc;
			Tab[0][Liczebnosc] = -1;
			Tab[1][Liczebnosc] = -1;
			Tab[2][Liczebnosc] = -1;
		
		}
		void Wyswietl(){
			cout<<endl<<"TABLICA : "<<Liczebnosc<<endl;
			for(int i=0; i<Liczebnosc; ++i){
				cout<<"R = "<<Tab[0][i]<<", ";
				cout<<"P = "<<Tab[1][i]<<", ";
				cout<<"Q = "<<Tab[2][i]<<endl;
			}
		}
};

class TablicaPriorytetowa2{
	public:
		int Liczebnosc;
		int Tab[4][500];  // R P Q INDEKS  [500]
		TablicaPriorytetowa2(){for(int i = 0;i<500;++i){Tab[0][i] = -1;Tab[1][i] = -1; Tab[2][i] = -1;Tab[3][i] = -1;} Liczebnosc = 0;}
		void Dodaj(int R, int P, int Q, int Ind){
			bool dodanie = false;
			++Liczebnosc;
			for(int i=0; i < Liczebnosc ; ++i){
				if(Q > Tab[2][i]){
					for(int j = Liczebnosc; j >= i; --j ){
						Tab[0][j+1] = Tab[0][j];
						Tab[1][j+1] = Tab[1][j];
						Tab[2][j+1] = Tab[2][j];
						Tab[3][j+1] = Tab[3][j];
					}
					Tab[0][i] = R;
					Tab[1][i] = P;
					Tab[2][i] = Q;
					Tab[3][i] = Ind;
					dodanie = true;
					break;
				}
				
			}
			if(!dodanie){
				Tab[0][Liczebnosc] = R;
				Tab[1][Liczebnosc] = P;
				Tab[2][Liczebnosc] = Q;		
				Tab[3][Liczebnosc] = Ind;				
			}
		}
		bool czypuste(){
			return !(Liczebnosc > 0);
		}
		void Zdejmij(int &R, int &P, int &Q, int &Ind){
			R = Tab[0][0] ;
			P = Tab[1][0] ;
			Q = Tab[2][0] ;
			Ind = Tab[3][0];
			for(int i = 0; i < Liczebnosc; ++i){
				Tab[0][i] = Tab[0][i + 1] ;
				Tab[1][i] = Tab[1][i + 1] ;
				Tab[2][i] = Tab[2][i + 1] ;
				Tab[3][i] = Tab[3][i + 1] ;
			}
			--Liczebnosc;
			Tab[0][Liczebnosc] = -1;
			Tab[1][Liczebnosc] = -1;
			Tab[2][Liczebnosc] = -1;
			Tab[3][Liczebnosc] = -1;
		
		}
		void Wyswietl(){
			cout<<endl<<"TABLICA : "<<Liczebnosc<<endl;
			for(int i=0; i<Liczebnosc; ++i){
				cout<<"R = "<<Tab[0][i]<<", ";
				cout<<"P = "<<Tab[1][i]<<", ";
				cout<<"Q = "<<Tab[2][i]<<", ";
				cout<<"Ind = "<<Tab[3][i]<<endl;
			}
		}
};
