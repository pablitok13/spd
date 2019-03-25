#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include<algorithm>

using namespace std;

int Cmax(int N,int M, int*tab,int *kolejnosc, int *tabsort,int rozmiar){
	int *x = new int[M+1];
	for(int i=0; i<M+1 ; ++i){
		x[i] = 0 ;
	}
	
	int k = 0;
	for(int j = 0; j < N; ++j){
		if (kolejnosc[j]==0){
			for(int i=0; i < M; ++i){     //kolejnosc posortowanych zadan 
			tabsort[k*M+i]=0;
		}
		}
		else{
			for(int i=0; i < M; ++i){
			tabsort[k*M+i]=tab[(kolejnosc[j]-1)*M+i];	
			}
		k++;	
		}

	}

	for(int t = 0 ; t < rozmiar+1 ; ++t){
		for (int i=1 ; i<M+1 ; ++i){
			x[i] = max( x[i], max(x[i-1] , x[i]) + tabsort[(i-1) + t*M]) ;
		}	 
	}
	return x[M] ;
}

void Swap(int &a, int &b){
	int i=a;
	a=b;
	b=i;
}
// tablica kolejnosc musi miec rozmiarn przynajmniej N
void Sort(int N, int M, int *tab, int *kolejnosc){
	int *Suma = new int [N];
	for(int i=0;i<N;++i){
		Suma[i]=0;
	}
	int max=0,ind=-1;
	for (int i=0;i<N;i++){
		for (int j=0;j<M;j++){                    //Liczenie czasu ca³kowitego zadania
			Suma[i]=Suma[i]+tab[j+i*M];
		}
	}

	for(int i = 0; i < N; ++i){					//sortownie
		for(int j = 0; j < N; ++j){
			if(Suma[j] > max){
				max = Suma[j];
				ind = j;
			}
		}
		kolejnosc[i]=ind +1;
		Suma[ind] = -1;
		max =0;
		ind=0;
	}	
	
	 	
}

void NEH(int N, int M, int*tab){
	int*kolejnosc = new int[N];     //wlasciwy algorytm neh 
	int*k1 = new int[N]; 
	int*k2 = new int[N]; 
	int rozmiar=1;         
	int cm=99999999;    
	int m=9999999;               
	for (int i=0;i<N;i++){
		kolejnosc[i]=0;
		k1[i] = 0;      //k1 i k2 sluza do zmiany kolejnosci w grafie  
		k2[i] = 0;
	}

	Sort(N,M,tab,kolejnosc);  
	cout<<"Najciezsze zadania"<<endl; 
	for (int i=0;i<N;i++)
	cout<<kolejnosc[i]<<", ";                              //sortowanie zadan wzgledem ich czasu calkowitego
	cout<<endl;
	int*tabsort=new int [N*M];
	for (int i=0;i<N*M;i++){
		tabsort[i]=0;
	}
	for(int i = 0; i < N; ++i){
			
		if(i==0){
			k1[0]=kolejnosc[0];
			k2[0]=kolejnosc[0];
		}
		else{
		
				//przesuwanie kolejki
			for(int z = rozmiar-1; z >= 0; --z){
				k1[z+1] = k1[z];
			}
			cm=999999999;
			k1[0] = kolejnosc[i];

			for(int z = 0; z <= rozmiar; ++z){
				if(z==0){

					m=Cmax(N,M,tab,k1,tabsort,i);
					if(cm>m){
						cm=m;
						for(int z=0; z<=rozmiar;++z)k2[z] = k1[z];
					}

					
				}
				else{
					Swap(k1[z-1],k1[z]);
					m=Cmax(N,M,tab,k1,tabsort,i);
				
					if(cm>m){
						cm=m;
						for(int z=0; z<=rozmiar;++z)k2[z] = k1[z];
					}
				}
			}
			
			for(int z = 0; z<=rozmiar; ++z) k1[z] = k2[z];
	
		++rozmiar;
		}

	}
	cout<<"Kolejnosc wykonywania zadan"<<endl;
	for (int i=0; i<rozmiar; ++i)
	cout<<k1[i]<<", ";
	cout <<endl;
	cout<<" Cmax = "<<cm<<endl;


}




int main() {
    int N,M;             // MAIN skopiowany za zgoda prowadzacego :)
    string buf;
    int bufi;
    
    ifstream data("data.txt");
    while(!data.eof()){

		getline(data,buf);
		cout<<buf<<endl;
		
		data>>N>>M;
		int *tab=new int [N*M];
		for(int ind = 0 ; ind < N*M ; ++ind ) data>>tab[ind]  ;
		getline(data,buf);
		getline(data,buf);
		getline(data,buf);
		data>>bufi;
		for(int i=0; i<N;++i) data>>bufi;
		getline(data,buf);	
		NEH(N,M,tab);
		cout<<" finish"<<endl;
		getline(data,buf);
		free(tab);
		getchar();
	}

    data.close();

    return 0;
}
