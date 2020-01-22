#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "Nag³ówek.h"
using namespace std;
void wypisanieszachownicy(char SZACHOWNICA[8][8], int WolnePola, int Hetman)
{
	int i, j;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	RysujLinie(80);
	for (i = 0; i < 8; i++)
		cout << "    " << char(i + 65);
	cout << endl;
	cout << " ";
	for (i = 0; i < 8; i++)
		cout << "  " << "___";
	cout << "\n\n";
	for (i = 0; i < 8; i++)
	{
		cout << i + 1 << '|';
		for (j = 0; j < 8; j++)
		{
			if (SZACHOWNICA[i][j] != char(0xB0) && SZACHOWNICA[i][j] != char(0xCE)) {
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
				cout << "  " << SZACHOWNICA[i][j] << "  ";
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			}
			else {
				if (SZACHOWNICA[i][j] == char(0xCE))
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "  " << SZACHOWNICA[i][j] << "  ";
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
				}
				else
					cout << "  " << SZACHOWNICA[i][j] << "  ";
			}
		}
		if (i == 2) {
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << " " << "Pozosta³e wolne pola:" << WolnePola;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}
		if (i == 3) {
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << " " << "Iloœæ HETMANÓW (" << char(0xCE) << ") do postawienia:" << Hetman;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}
		cout << "\n\n";
	}
}
void ruch(char SZACHOWNICA[8][8], int WolnePola, int Hetman)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	bool koordynaty = false;
	int i, n;
	char x, y;
	while (koordynaty == false) {
		wypisanieszachownicy(SZACHOWNICA, WolnePola, Hetman);
		RysujLinie(80);
		cout << " Podaj pozycjê Hetmana : ";
		cin >> y >> x;
		toupper(y);
		toupper(x);
		if (y > 64 && y < 73)
			y = y - 16;
		if (y > 56 || x > 56 || y < 49 || x < 49) {
			cout << endl;
			cout << " Taka pozycja nie istnieje! " << endl;
			Sleep(1000);
		}
		else {
			x = x - 48;
			y = y - 48;
			koordynaty = true;
			SZACHOWNICA[x - 1][y - 1] = 0xCE;
		}
	}
	for (i = 0; i < 8; i++)
	{
		if (SZACHOWNICA[x - 1][i] != 0xCE)
		{
			SZACHOWNICA[x - 1][i] = '*';
		}
	}
	for (i = 0; i < 8; i++)
	{
		SZACHOWNICA[i][y - 1] = '*';
		if (SZACHOWNICA[i][y - 1] != 0xCE)
		{
			SZACHOWNICA[i][y - 1] = '*';
		}
	}
	for (n = 1; n + x <= 8 && n + y <= 8; n++)
	{
		if (SZACHOWNICA[n + x - 1][n + y - 1] != 0xCE)
		{
			SZACHOWNICA[n + x - 1][n + y - 1] = '*';
		}
	}
	for (n = 1; x - n > 0 and y - n > 0; n++)
	{
		if (SZACHOWNICA[x - 1 - n][y - 1 - n] != 0xCE)
		{
			SZACHOWNICA[x - 1 - n][y - 1 - n] = '*';
		}
	}
	for (n = 1; n + x <= 8 and y - n > 0; n++)
	{
		if (SZACHOWNICA[n + x - 1][y - 1 - n] != 0xCE)
		{
			SZACHOWNICA[n + x - 1][y - 1 - n] = '*';
		}
	}
	for (n = 1; x - n > 0 and n + y <= 8; n++)
	{
		if (SZACHOWNICA[x - 1 - n][n + y - 1] != 0xCE)
		{
			SZACHOWNICA[x - 1 - n][n + y - 1] = '*';
		}
	}
	SZACHOWNICA[x - 1][y - 1] = 0xCE;
}
int ZnajdzHetmana(char SZACHOWNICA[8][8])
{
	int Hetmani = 0, i, j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (SZACHOWNICA[i][j] == char(0xCE))
				Hetmani = Hetmani + 1;
	return Hetmani;
}
int IloscPol(char SZACHOWNICA[8][8])
{
	int pola = 0, i, j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (SZACHOWNICA[i][j] == char(0xB0))
				pola++;
	return pola;
}
void rozgrywka(bool start)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char SZACHOWNICA[8][8];
	int i, j, WolnePola, Hetman = 8;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			SZACHOWNICA[i][j] = char(0xB0);
	bool stop = false;
	while (stop == false)
	{
		int pola = IloscPol(SZACHOWNICA);
		ruch(SZACHOWNICA, pola, Hetman);
		Hetman--;
		int Przegrana = ZnajdzHetmana(SZACHOWNICA);
		if (Przegrana != abs(Hetman - 8) || IloscPol(SZACHOWNICA) == 0 && Hetman != 0)
		{
			wypisanieszachownicy(SZACHOWNICA, IloscPol(SZACHOWNICA), Hetman);
			RysujLinie(80);
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << " PRZEGRA£EŒ ! " << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			RysujLinie(80);
			stop = true;
		}
		if (IloscPol(SZACHOWNICA) == 0 && Hetman == 0)
		{
			wypisanieszachownicy(SZACHOWNICA, IloscPol(SZACHOWNICA), Hetman);
			RysujLinie(80);
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << " GRATULACJE ! " << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			RysujLinie(80);
			stop = true;
		}
	}
}