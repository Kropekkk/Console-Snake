#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <fstream>

using namespace std;

int WYSOKOSC,SZEROKOSC;
const int wielkosc_ogona = 50;  //Maksymalna wielkosc Ogona
int x=10, y= 10;    //Pozycja startowa
int ogonX[wielkosc_ogona], ogonY[wielkosc_ogona];
int ogon;               //Aktualna wielkosc ogona
int jedzenieX,jedzenieY;        //Aktualna pozycja jaedzenia
int PREDKOSC;

enum Kierunek {LEWO,PRAWO,GORA,DOL};    //Kierunki
Kierunek kierunek;      //Aktualny kierunek

bool Gra=true;

void cls()
{
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void Jedzenie()
{
    jedzenieX = rand() % SZEROKOSC;
    jedzenieY = rand() % WYSOKOSC;
}

void Rysuj()
{
    cls();  //Czyszczenie ekranu

    for(int i = 0; i < WYSOKOSC+2; i++)
    {
        cout << "#";    //Pierwsza linijka od lewej
        for(int j = 0; j < SZEROKOSC; j++)
        {
            if(i==0 || i==WYSOKOSC+1)
            {
                cout<< "#"; //Jesli linijka jest na samej gorze albo na samym dole
            }
            else if(i==y && j==x)
            {
                cout <<"O";
            }
            else if(jedzenieX==j && jedzenieY==i)
            {
                cout << "J";
            }
            else
            {
                bool rysuj = false;

                for (int k = 0; k < ogon; k++)
                {
                    if(ogonX[k]==j && ogonY[k]==i)
                    {
                        cout <<"o";
                        rysuj = true;
                    }
                }

                if(!rysuj)
                {
                    cout<< " ";
                }
            }
        }
        cout << "#\n";
    }
}

void Koniec()
{
        x=10;
        y=10;
        Gra=false;
        ogon=0;
}

void Ruch()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'w':
            kierunek=GORA;
            break;
        case 's':
            kierunek=DOL;
            break;
        case 'a':
            kierunek=LEWO;
            break;
        case 'd':
            kierunek=PRAWO;
            break;
        }
    }

    for (int i = ogon; i>0; i--)
    {
        ogonX[i] = ogonX[i-1];
        ogonY[i] = ogonY[i-1];
    }

    ogonX[0] = x;
    ogonY[0] = y;

    switch(kierunek)
    {
    case GORA:
        y--;
        break;
    case DOL:
        y++;
        break;
    case LEWO:
        x--;
        break;
    case PRAWO:
        x++;
        break;
    }

    if(x<0 || x>SZEROKOSC)
    {
        Koniec();
    }
    else if(y<=0 || y>WYSOKOSC)
    {
        Koniec();
    }

    for (int i =0;i<ogon;i++)
    {
        if(ogonX[i]==x && ogonY[i]==y)
        {
            Koniec();
        }
    }

    if(x==jedzenieX && y==jedzenieY)
    {
        Jedzenie();
        ogon++;
    }
}

void Konfiguracja()
{
    fstream ustawienia;
    string poczatkowy_kierunek;
    ustawienia.open("ustawienia.txt");

    int nrlinia=1;
    string linia;

    while(getline(ustawienia,linia))
    {
        switch(nrlinia)
        {
            case 1: poczatkowy_kierunek=linia; break;
            case 2: WYSOKOSC= atoi(linia.c_str()); break;
            case 3: SZEROKOSC=atoi(linia.c_str()); break;
            case 4: PREDKOSC= atoi(linia.c_str()); break;
        }
        nrlinia++;
    }

    if(poczatkowy_kierunek=="GORA")
    {
        kierunek=GORA;
    }
    else if(poczatkowy_kierunek=="DOL")
    {
        kierunek=DOL;
    }
    else if(poczatkowy_kierunek=="LEWO")
    {
        kierunek=LEWO;
    }
    else if(poczatkowy_kierunek=="PRAWO")
    {
        kierunek=PRAWO;
    }
    else
    {
        kierunek=GORA;
    }

    ustawienia.close();
    Jedzenie();
}

int main()
{
    Konfiguracja();

    while(true)
    {
        Rysuj();
        Ruch();
        Sleep(PREDKOSC);
    }
    return 0;
}
