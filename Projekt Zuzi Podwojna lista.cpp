// Projekt Zuzi Podwojna lista.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct element
{
	element *poprz;
	int info; //numer grupy
	element *pocz2; //wskaznik na poczatek podlisty w liscie (tam wartosci)
	element *koniec2; //wskaznik na koniec podlisty w liscie (tam wartosci)
	element *nast;
};

void NowaLista(element **pocz, element **koniec, int ans1, int ans2)
{
	*pocz = new element;
	*koniec = *pocz;
	(*pocz)->nast = NULL;
	(*pocz)->poprz = NULL;
	(*pocz)->info = ans1;

	(*pocz)->pocz2 = new element;
	(*pocz)->koniec2 = (*pocz)->pocz2;
	(*pocz)->pocz2->nast = NULL;
	(*pocz)->pocz2->poprz = NULL;
	(*pocz)->pocz2->info = ans2;
}

void WyswietlListe(element *pocz)
{
	if (pocz != NULL)
		while (pocz != NULL)
		{
			cout << pocz->info << ' ';
			pocz = pocz->nast;
		}
	else cout << "na";

	cout << endl;
}

void DodajPocz(element *&pocz, int wartosc)
{
	element *nowy = new element;
	nowy->info = wartosc;
	nowy->nast = pocz;
	nowy->poprz = NULL;
	pocz->poprz = nowy;
	pocz = nowy;
}

void DodajKoniec(element *&koniec, int wartosc)
{
	element *nowy = new element;
	nowy->info = wartosc;
	nowy->nast = NULL;
	nowy->poprz = koniec;
	koniec->nast = nowy;
	koniec = nowy;
}

element* ZwrocElement(element *pocz, int x)
{
	if (x < 1) return NULL;
	for (int i = 1; i < x && pocz != NULL; i++)
		pocz = pocz->nast;
	return pocz;
}

bool Zmien(element *pocz, int ind, int wartosc)
{
	element *wsk = ZwrocElement(pocz, ind);
	if (wsk != NULL)
	{
		wsk->info = wartosc;
		return true;
	}
	else return false;
}

void WstawPrzed(element *wsk, int wartosc)
{
	element *nowy = new element;
	nowy->info = wartosc;
	nowy->nast = wsk;
	nowy->poprz = wsk->poprz;
	wsk->poprz->nast = nowy;
	wsk->poprz = nowy;
}

void WstawZa(element *wsk, int wartosc)
{
	element *nowy = new element;
	nowy->info = wartosc;
	nowy->nast = wsk->nast;
	nowy->poprz = wsk;
	wsk->nast->poprz = nowy;
	wsk->nast = nowy;
}

//Funkcja dodaje element, zachowujac kolejnosc malejaca wartosci 'info'
element* Wstaw(element **pocz, element **koniec, int wartosc)
{
	element *wsk = *pocz;

	while (wsk->info > wartosc && wsk->nast != NULL)
		wsk = wsk->nast;

	if (wsk->info > wartosc)
	{
		if (wsk->nast == NULL)
		{
			DodajKoniec(*koniec, wartosc);
			return *koniec;
		}
		else
		{
			WstawZa(wsk, wartosc);
			return wsk->nast;
		}
	}
	else
	{
		if (wsk->poprz == NULL)
		{
			DodajPocz(*pocz, wartosc);
			return *pocz;
		}
		else
		{
			WstawPrzed(wsk, wartosc);
			return wsk->poprz;
		}
	}
	return NULL;
}

element* Szukaj(element *pocz, int szukany)
{
	while (pocz != NULL && pocz->info != szukany)
		pocz = pocz->nast;

	if (pocz == NULL) return NULL;
	else return pocz;
}

bool KasujPierwszy(element *&pocz)
{
	if (pocz != NULL && pocz->nast != NULL)
	{
		element *temp;
		temp = pocz->nast;
		delete pocz;
		pocz = temp;
		pocz->poprz = NULL;
		return true;
	}
	return false;
}

bool KasujOstatni(element *&koniec)
{
	if (koniec != NULL && koniec->poprz != NULL)
	{
		element *temp;
		temp = koniec->poprz;
		delete koniec;
		koniec = temp;
		koniec->nast = NULL;
		return true;
	}
	return false;
}

bool UsunXelement(element *wsk)
{
	if (wsk != NULL && wsk->nast != NULL && wsk->poprz != NULL)
	{
		wsk->poprz->nast = wsk->nast;
		wsk->nast->poprz = wsk->poprz;
		delete wsk;
		return true;
	}
	return false;
}

void ZwolnijListe(element *&pocz, element *&koniec)
{
	element *temp;
	while (pocz != NULL)
	{
		temp = pocz;
		pocz = pocz->nast;
		delete temp;
	}
	koniec = NULL;
}

void aFun(element **pocz, element **koniec, int ans1, int ans2)
{
	//Jesli lista nie istnieje, to tworzymy ja i wypelniamy od razu potrzebnymi danymi (problem z glowy)
	if (*pocz == NULL) NowaLista(pocz, koniec, ans1, ans2);
	else
	{
		element *wsk = Szukaj(*pocz, ans1);
		//Sprawdzamy czy grupa o numerze ans1 istnieje:
		//1) Jesli tak, to wsk = wskaznik na ta grupke na liscie
		//2) Jesli nie, to wsk = NULL
		if (!wsk) //Jesli nie znalazlo nam grupy o numerze ans1
		{
			wsk = Wstaw(pocz, koniec, ans1);	//Funkcja wrzuca ans1 na liste, zachowujac kolejnosc malejaca (tworzy grupe)
			wsk->pocz2 = new element;			//Przy okazji zwraca wskaznik na wlasnie dodany element
			wsk->koniec2 = (*pocz)->pocz2;		//Wykorzystujemy go do utworzenia podlisty
			wsk->pocz2->nast = NULL;
			wsk->pocz2->poprz = NULL;
			wsk->pocz2->info = ans2;
		}
		else
		{
			Wstaw(&(wsk->pocz2), &(wsk->koniec2), ans2);
		}	
	}
}

void pFun(element *pocz, int ans1)
{
	element *wsk = Szukaj(pocz, ans1);
	if (wsk)
	{
		wsk = wsk->pocz2;
		WyswietlListe(wsk);
	}
	else cout << "na" << endl;
}

void iFun(element **pocz, element **koniec, int ans1, int ans2, int ans3)
{
	element *wsk = Szukaj(*pocz, ans1);
	if (wsk) //Czy jest taka grupa?
	{
		element *wsk2 = Szukaj(wsk->pocz2, ans2); //Nowy wskaznik, dzialajacy w podliscie
		if (wsk2) //Czy jest taka wartosc?
		{
			if (wsk2->nast == NULL && wsk2->poprz == NULL) //Czy jest to jedyna wartosc w podliscie?
				Zmien(wsk2, 1, ans3);
			else
			{
				//1) Najpierw usuwamy wartosc z listy
				if (!UsunXelement(wsk2)) //Jesli nie udalo sie usunac elementu, to znaczy, ze element byl ostatni lub pierwszy
				{
					if (wsk2->poprz == NULL) KasujPierwszy(wsk->pocz2);
					else KasujOstatni(wsk->koniec2);
				}

				//2) Pozniej wstawiamy nowa
				Wstaw(&(wsk->pocz2), &(wsk->koniec2), ans3);
			}
		}
		else cout << "na" << endl;
	}
	else cout << "na" << endl;
}

void eFun(element **pocz, element **koniec, int ans1)
{
	element *wsk = Szukaj(*pocz, ans1);
	if (wsk)
	{
		cout << wsk->pocz2->info << endl;

		if (wsk->pocz2->nast == NULL) //Czy wartosc, ktora mamy usunac byla jedyna na liscie? Jesli tak, usun takze grupe
		{
			ZwolnijListe(wsk->pocz2, wsk->koniec2);
			
			if (wsk->poprz == NULL)
			{
				if (wsk->nast == NULL) ZwolnijListe(*pocz, *koniec);
				else KasujPierwszy(*pocz);
			}
			else if (wsk->nast == NULL)
				KasujOstatni(*koniec);
			else
				UsunXelement(wsk);
		}
		else KasujPierwszy(wsk->pocz2);
	}
	else cout << "na" << endl;
}

void mFun(element **pocz, element **koniec, int ans1, int ans2)
{
	element *grupa1 = Szukaj(*pocz, ans1);
	element *grupa2 = Szukaj(*pocz, ans2);

	if (grupa1 && grupa2)
	{
		int wartosc = grupa2->pocz2->info;
		Wstaw(&(grupa1->pocz2), &(grupa1->koniec2), wartosc);
		while (KasujPierwszy(grupa2->pocz2))
		{
			wartosc = grupa2->pocz2->info;
			Wstaw(&(grupa1->pocz2), &(grupa1->koniec2), wartosc);
		}

		ZwolnijListe(grupa2->pocz2, grupa2->koniec2);

		if (!UsunXelement(grupa2)) //Jesli nie udalo sie usunac elementu, to znaczy, ze element byl ostatni lub pierwszy
		{
			if (grupa2->poprz == NULL) KasujPierwszy(*pocz);
			else KasujOstatni(*koniec);
		}
	}
	else cout << "na" << endl;
}

int main()
{
	element *pocz = NULL; //wskaznik na poczatek listy
	element *koniec = NULL; //wskaznik na koniec listy

	int loop_main;
	char operation;
	bool wasLastLoopWrong = false;
	int ans1, ans2, ans3;

	cin >> loop_main;
	for (int i = 0; i < loop_main; i++)
	{
		cin >> operation;
		switch (operation)
		{
		case 'a':
			wasLastLoopWrong = false;
			cin >> ans1 >> ans2;
			aFun(&pocz, &koniec, ans1, ans2);
			break;
		case 'e':
			wasLastLoopWrong = false;
			cin >> ans1;
			eFun(&pocz, &koniec, ans1);
			break;
		case 'p':
			wasLastLoopWrong = false;
			cin >> ans1;
			pFun(pocz, ans1);
			break;
		case 'm':
			wasLastLoopWrong = false;
			cin >> ans1 >> ans2;
			mFun(&pocz, &koniec, ans1, ans2);
			break;
		case 'i':
			wasLastLoopWrong = false;
			cin >> ans1 >> ans2 >> ans3;
			iFun(&pocz, &koniec, ans1, ans2, ans3);
			break;
		default:
			if (wasLastLoopWrong) i--;	//Jakby ktos wpisal bledna literke i po niej liczby, to ominie tylko jedena		
			else cout << "na" << endl;	//kolejke wpisow, a nie od razu tyle, ile pobral cinow (ans1, ans2, ans3)
			wasLastLoopWrong = true;
			break;
		}
	}
	
		
	return 0;
}