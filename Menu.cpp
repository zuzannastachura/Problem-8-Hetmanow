#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "Nag³ówek.h"
using namespace std;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
void XY(int x, int y) // ustawianie pozycji na ekranie
{
    COORD c; // struktura stosowana do pozycjonowania
    c.X = x - 1; // x i y to numery wiersza i kolumny
    c.Y = y - 1;
    SetConsoleCursorPosition(handle, c); // ustaw pozycjê
}
void RysujMenu(string& str, int id, int idset)
{
    if (id == idset) { // wybrana pozycja
        SetConsoleTextAttribute(handle, 240); // podœwietlenie
        cout << str << "[" << id << "]" << endl; // wypisanie na ekranie numeru pozycji
        SetConsoleTextAttribute(handle, 7); // domyœlny kolor
    }
    else { // nie wybrana pozycja
        cout << str << "[" << id << "]" << endl; // wypisanie bez podœwietlenia
    }
}
void RysujLinie(unsigned int ile)
{
    for (unsigned int i = 0; i < ile; i++) {
        cout << "=";
    }
    cout << endl;
}
int menu(string title, vector<string>& tMenu, int& id)
{
HOP: // znacznik miejsca skoku
    XY(1, 1); // ustawienie w linii 1 i kolumnie 1
    RysujLinie(80);
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << title << "\n\n";
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    RysujLinie(80);
    for (int i = 0; i < tMenu.size(); i++) { // dla wszystkich pozycji menu
        RysujMenu(tMenu[i], i, id); // wypisanie
    }
    int c = _getch(); // pobranie znaku
    if (c == 224) { // 
        c = c << 8; // przesuniêcie bitowe
        c |= _getch(); // bitowe OR
    }

    switch (c)
    {
    case (224 << 8) | 72: // strza³ka w górê
        if (id != 0)
            id = id - 1;
        XY(1, 1); // ustawienie  w linii 1 i wierszu 1
        goto HOP; // skok do znacznika A
    case (224 << 8) | 80: // strza³ka w dó³
        if (id + 1 < tMenu.size())
            id++;
        else
            id = tMenu.size() - 1;
       XY(1, 1); // ustawienie  w linii 1 i wierszu 1
        goto HOP; // skok do znacznika A
    default:
        if (c > 47 && c < 48 + tMenu.size()) {
            id = c - 48; // pozycji z menu
            return id;
        }
        break;
    }
    return id; // numer pozycji
}
int main() {

    setlocale(LC_CTYPE, "Polish");
    vector<string> tMenuGl;
    tMenuGl.push_back("WyjdŸ z programu\t");
    tMenuGl.push_back("Graj\t\t\t");
    tMenuGl.push_back("Instrukcje\t\t");
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "    _______         __              _______        __          " << endl;
    cout << "  |    |    |.---- |  |_ _.-------- |  _   |.-----|__| " << endl;
    cout << "  |         |  -__ |     _|    |    |      |      |  |" << endl;
    cout << "  |___ | ___|_____ | ____ | __ | __ |__|___|___|__|__|  " << endl;
    cout << "                                                                          " << endl;
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    Sleep(3000);
    system("cls");
    int id = 0;
    do {
        menu("Menu g³ówne", tMenuGl, id);
        system("cls");
        switch (id) {
        case 1: // GRA
        {
            bool start = true;
            rozgrywka(start);
            break;
        }
        case 2: // dla instrukcji
        {
            RysujLinie(80);
            cout << " Twoim zadaniem jest ustawiæ na planszy 8 Hetmanów tak by:" << endl;
            cout << " 1.Nie atakowali siê nawzajem. " << endl;
            cout << " 2.Na planszy nie zosta³o ¿adne puste pole.  " << endl;
            cout << " Gra koñczy siê gdy na planszy: " << endl;
            cout << " 1.Nie ma pustych pól. " << endl;
            cout << " 2.Gdy Hetman zostanie zaatakowany przez innego Hetmana. " << endl;
            cout << " Koordynaty mo¿na wpisywaæ na 3 sposoby : " << endl;
            cout << " 1.Wielka litera (spacja/enter) cyfra. " << endl;
            cout << " 2.Ma³a litera (spacja/enter) cyfra. " << endl;
            cout << " 3.Cyfra (spacja/enter) cyfra. \n\n";
            RysujLinie(80);
            break;
        }
        case 0: // dla wyjœcia z programu
        {
            cout << "Wciœnij t, jeœli naprawdê chcesz wyjœæ z programu...";
            if (_getch() == 't')
                id = -1;
            cout << endl;
            break;
        }
        }
        if (id > 0)
        {
            RysujLinie(80);
            cout << "Wciœnij dowolny klawisz, aby przejœæ do menu...";
            _getch();
        }
        system("cls");
    } while (id > -1);
    cout << "Wciœnij enter, aby zamkn¹æ program...";
    _getch;
    return 0;
}
