#include "stdafx.h"  //tylko dla Visual Studio
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>


#define zmienna long long 
zmienna N = 90581;
zmienna e = 17993;

using namespace std;
vector <zmienna> Q; //d
vector <zmienna> P;	//k
vector <zmienna> ulamek; //przechowuje ulamek lancuchowy
vector <zmienna> FiN; //fiN 

// WYSWIETLA WEKTOR
void Wyswietl(vector<zmienna> wektor)
{
	for (int i = 0; i < wektor.size(); i++)
	{
		cout << wektor[i] << " ";
	}
	cout << endl;
}
//////

//Oblicza ulamek lancuchowy w skroconej formie [a0,a1,a2....] uzywajac algorytmu Euklidesa 
void UlamekLancuchowy(zmienna X, zmienna Y)
{
	//ulamek.push_back(0);
	while (Y != 0)
	{
		zmienna tmp = X / Y;
		ulamek.push_back(tmp);
		zmienna tmp2 = X;
		X = Y;
		Y = tmp2 - tmp*Y;
	}
}
//////////////

void Redukty() //na podstawie ulamka lancuchowego oblicza kolejne redukty P=k Q=d
{
	zmienna k, d;
	for (int i = 0; i < ulamek.size(); i++)
	{
		if (i == 0)
		{
			Q.push_back(ulamek[i]);
			P.push_back(1);
		}
		if (i == 1)
		{
			Q.push_back((ulamek[i] * Q[i - 1]) + 1);
			P.push_back(ulamek[i]);
		}
		if (i>1)
		{
			Q.push_back((ulamek[i] * Q[i - 1]) + Q[i - 2]);
			P.push_back((ulamek[i] * P[i - 1]) + P[i - 2]);
		}
	}
}

void wypiszredukty()  //wypisuje wartosci reduktow
{
	for (int i = 0; i < Q.size(); i++)
	{
		cout << "redukt " << i+1 << " to : " << P[i] << "/" << Q[i] << endl;
	}
}

void WypelnijFi()  //Wypelnia vector FiN 
{
	for (int i = 0; i < Q.size(); i++)
	{			// e*d - 1 / k
		if (Q[i] == 0)
		{

		}
		else {
			//cout << "e = " << e << " Q = " << Q[i] << " P = " << P[i] << " FiN = "<< (((e*P[i]) - 1) / Q[i])<< endl;
			FiN.push_back(((e*Q[i]) - 1) / P[i]);
		}
	}
}


void Sprawdz() //sprawdza czy po pordstawieniu ktoregos z FiN i rowiazania rownania kwadratowego, uda sie znalesc pasujace d
{
	zmienna x1, x2;
	int i = 0;
	bool flag = false;
	//rownanie ma postac ax2 + bx + c = 0
	// gdzie b = N - FiN + 1 ,  c = N
	do
	{
		zmienna b = (N - FiN[i] + 1);
		zmienna delta = (b*b) - (4 * 1 * N);
		//cout << "i wynosi "<<i<<" FIN = "<<FiN[i]<<" b wynosi " << b << " a delta  = " << delta << endl;
		if (delta < 0)
		{
			//cout << "rownanie " << i << " nie ma rozwiazania (UJEMNA DELTA)  " << endl;
		}
		else if (delta >= 0)
		{
			x1 = (b - sqrt(delta)) / 2;
			x2 = (b + sqrt(delta)) / 2;
			if ((x1*x2) == N)
			{
				cout << "Znaleziono wynik ! " << endl;
				cout << "q = " << x1 << " p = " << x2 << endl;
				cout << "Klucz prywatny (d,N) to : (" << Q[i] << "," << N << ") !"<<endl;
				flag = true;
			}
		}
		if (i == FiN.size()-1)
		{
			cout << "Nie udalo sie znalesc rozwiazania!" << endl;
		}

		i++;
	} while (flag != true && i < FiN.size());

}

void clear() //czysci wektory dla nastepnych danych
{
	ulamek.clear();
	Q.clear();
	P.clear();
	FiN.clear();
}



int main()
{
	cout << "==PROGRAM IMPLEMENTJACY ATAK DIOFANTYCZNY NA ALGORYTM RSA==" << endl << endl;
	cout << "Dla podanych danych N = " << N << " oraz e = " << e << endl;
	cout << "Ulamek lancuchowy : ";
	UlamekLancuchowy(N, e);
	Wyswietl(ulamek);
	Redukty();
	wypiszredukty();
	WypelnijFi();
	Sprawdz();
	cout << endl;
	N = 160523347;
	e = 60728973;
	clear();
	cout << "Dla podanych danych N = " << N << " oraz e = " << e << endl;
	cout << "Ulamek lancuchowy : ";
	UlamekLancuchowy(N, e);
	Wyswietl(ulamek);
	Redukty();
	wypiszredukty();
	WypelnijFi();
	Sprawdz();
	system("PAUSE");
	return 0;
}
