#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;



const int wielkosc_ogona = 50;  //Maksymalna wielkosc Ogona
int x=10, y= 10;    //Pozycja startowa
int ogonX[wielkosc_ogona], ogonY[wielkosc_ogona];
int ogon;               //Aktualna wielkosc ogona
int jedzenieX,jedzenieY;        //Aktualna pozycja jaedzenie

enum Kierunek {LEWO,PRAWO,GORA,DOL};    //Kierunki
Kierunek kierunek;      //Aktualny kierunek

bool Gra=true;

void cls()
{
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void Rysuj()
{
    cls();

    for(int i = 0; i < 26; i++)
    {
        cout << "#";
        for(int j = 0; j < 25; j++)
        {
            if(i==0 || i==25)
            {
                cout<< "#";
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

    int pozX,pozY;
    ogonX[0] = x;
    ogonY[0] = y;

    for (int i =ogon; i>0; i--)
    {
        ogonX[i] = ogonX[i-1];
        ogonY[i] = ogonY[i-1];
    }

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

    if(x<=0 || x>25)
    {
        x=10;
        y=10;
        Gra=false;
    }
    else if(y<=0 || y>25)
    {
        x=10;
        y=10;
        Gra=false;
    }

    for (int i =0;i<ogon;i++)
    {
        if(ogonX[i]==x && ogonY[i]==y)
        {
            x=10;
            y=10;
            Gra=false;
        }
    }

    if(x==jedzenieX && y==jedzenieY)
    {
        ogon++;
    }
}

int main()
{
    kierunek=GORA;
    jedzenieX= 5;
    jedzenieY=5;

    while(true)
    {
        Rysuj();
        Ruch();
        Sleep(10);
    }
    return 0;
}
