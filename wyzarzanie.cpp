#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

using namespace std;


void showResult (int moves, int cmax_time) {
    cout << "Ilosc wykonanych ruchow: " << moves << endl;
    cout << "Czas Cmax: " << cmax_time;
}

int Cmax(int arrG[100][100], vector<int> order, int m) {
	int arr[100][100] = { 0 };
	int sumX = 0;
	int sumY = 0;


	for (size_t i = 0; i < order.size(); i++) {
		sumX += arrG[0][*(order.begin() + i)];
		arr[0][i] = sumX;
	}
	for (int j = 0; j < m; j++) {
		sumY += arrG[j][*order.begin()];
		arr[j][0] = sumY;
	}
	for (int y = 1; y < m; y++) {
		for (size_t x = 1; x < order.size(); x++) {
			arr[y][x] = max(arr[y - 1][x], arr[y][x - 1]) + arrG[y][order[x]];
		}
	}
	return arr[m - 1][order.size() - 1];
}




int main()
{
    ///*********************************///
    //czytanie danych z pliku
    int buff[100][100];
    int tasks, machines;

    ifstream data("dane.txt");
    data >> tasks;
    data >> machines;

    for (int i = 0; i < tasks; i++) {
        for (int j = 0; j < machines; j++)
        {
            data >> buff[j][i];
        }
    }

    ///***********************************///


    ///************* KROK 1**************///
    int Clast, Cnow;
    vector<int> last, now;

    float T = 100000;
    float Tk = 0.0001;
    float rat = 0.999;

    //kolejnosc
    vector<int> order;
    for (int i = 0; i < tasks; i++) {
        order.push_back(i);
    }

    srand(time(NULL));
	double randomix;
	int r1,r2;

    float P =0;
	int moves, tmp;

	///*******************************///

    moves = 0;


    // zmienna pomocnicza do insertu
	tmp = 0;

	while (T > Tk) {

	///*** akutalne rozwiazanie ***///
        now = order;
        Cnow = Cmax(buff, order, machines);

    ///*** rozwiazanie somsiada ***///
        last = order;
        r1 = rand() % (last.size() - 1); r2 = rand() % (last.size() - 1);

        tmp = *( last.begin() + r2);
        last.erase(last.begin() + r2);
        last.insert(last.begin() + r1, tmp);
        Clast = Cmax(buff, last, machines);


   ///*** prawdopodobienstwo ***///
		P = exp((Cnow - Clast) / T);


    ///*** Kryterium wykonania ruchu ***///
		if (Clast >= Cnow) {
			randomix = ((double)rand()/(RAND_MAX));
			if (P >= randomix) {
                order = last;
            }
			else {
                order = now;
            }
		}
		else {
            order = last;
        }
    ///*** schladzanie ***///
		moves++;
		T = T * rat;
	}

	int cmax_time = Cmax(buff, order, machines);
    showResult (moves, cmax_time);
}
