#include <iostream>
#include <cstdlib>   //rand()
#include <math.h>   //pow()

using namespace std;

//funkcja przystosowania 3*x+3;
static int bity = 5,
                liczba_populacji = 6,
                krzyzowanie = 7,   // if (krzyzowanie <= 10) true;
                mutacja = 1,       // if (mutacja <= 10) true;
                iteracja = 10;
//----------------------------------------------------------------------------
//funkcje - deklaracje
int losuj(int min, int max);
int rozkodowanie_i_przystosowanie(int **tablica_rozk,
                                                  int *tablica_przyst);
int ruletka(int *tablica_rul, int *tablica_przyst);
int przepisanie(int **tablica_sPop, int **tablica_nPop);
int nowa_populacja(int **tablica_sPop,
                           int **tablica_nPop,
                           int *tablica_rul);
int f_krzyzowanie(int **tablica_nPop, int **tablica_sPop);
int f_mutacja(int **tablica_sPop);
void wypisz();
//-----------------------------------------------------------------------------
int main()
{
    srand(time(NULL));   //zaladowanie ziarna czasu
    //stworzenie populacji
    int **populacja = new int *[liczba_populacji];
    int **populacja_dzieci = new int *[liczba_populacji];

    for (int i=0 ; i<liczba_populacji ; ++i)
    {
            populacja[i] = new int[bity];
            populacja_dzieci[i] = new int[bity];
    }
    for (int p=0 ; p<liczba_populacji ; ++p)
    {
        cout << "Osobnik: " << p << ": ";
        for (int b=0 ; b<bity ; ++b)
        {
                //losuj(0,1);
                if (p==1 || p==3) populacja[p][b] = 1;
                else populacja[p][b] = 0; //wylosowanie 0 lub 1
                cout << populacja[p][b] << " ";
                populacja_dzieci[p][b] = 0;
        }
        cout << "\n";
    }
    //stworzenie i przygotowanie tablic do pracy
    //stworzenie tablicy przystosowania
    int *tabl_przystosowania = new int[liczba_populacji];

    //stworzenie "kola" ruletki
    int *tabl_ruletki = new int[liczba_populacji];

    for (int i=0 ; i<liczba_populacji ; ++i)
    {
        tabl_przystosowania[i] = 0;
        tabl_ruletki[i] = 0;
    }

    while (iteracja >= 5)
    {
        rozkodowanie_i_przystosowanie(populacja, tabl_przystosowania);
        ruletka(tabl_ruletki, tabl_przystosowania);
        przepisanie(populacja, populacja_dzieci);
        nowa_populacja(populacja, populacja_dzieci, tabl_ruletki);
        f_krzyzowanie(populacja_dzieci, populacja);
        f_mutacja(populacja);

        --iteracja;
    }


    for (int i=0 ; i<liczba_populacji ; ++i)
    {
        delete[] populacja[i];
        delete[] populacja_dzieci[i];
    }
    delete[] tabl_przystosowania;
    delete[] tabl_ruletki;
}
//---------------------------------------------------------------------------
//funkcje
    int losuj(int i_min, int i_max)
    {
            return rand() % ((i_max - i_min+1) + i_min);
    }

    int rozkodowanie_i_przystosowanie(int **tablica_rozk, int *tablica_przyst)
    {
        int pomocnicza = 0;
        int wynik = 0;
        int potega = bity-1;

        cout << "Funkcja przystosowania dla osobnika \n";
        for (int i=0 ; i<liczba_populacji ; ++i)
        {
            for (int j=0 ; j<bity ; ++j)
            {
                    pomocnicza = tablica_rozk[i][j];
                    wynik += pomocnicza * pow(2, potega);
                    --potega;
            }

        tablica_przyst[i] = 3*wynik + 3;
        cout << i+1
             << " wynosi: "
             << tablica_przyst[i]
             << "\n";
        wynik = 0;
        potega = bity-1;
        }
}

    int ruletka(int *tablica_rul, int *tablica_przyst)
    {
        int pomocnicza = 0;
        for (int i=0 ; i<liczba_populacji ; ++i)
        {
            pomocnicza += tablica_przyst[i];
            tablica_rul[i] = pomocnicza;
        }
    }

    int przepisanie(int **tablica_sPop, int **tablica_nPop)
    {
        for (int i=0 ; i<liczba_populacji ; ++i)
        {
            for (int j=0 ; j<bity ; ++j)
            {
                    tablica_sPop[i][j] = tablica_nPop[i][j];
            }
        }
    }

    int nowa_populacja(int **tablica_sPop, int **tablica_nPop, int *tablica_rul)
    {
    //wylosowanie nowej populacji
        int nowy = 0;
        int pomocnicza = 0;
        int max = tablica_rul[liczba_populacji-1];

        for (int i=0 ; i<liczba_populacji ; ++i)
        {
            nowy = losuj(0, max);
            while ( nowy > tablica_rul[pomocnicza])
            {
                ++pomocnicza;
            }

        for (int j=0 ; j<bity ; ++j)
        {
            tablica_nPop[i][j] = tablica_sPop[pomocnicza][j];
        }
        pomocnicza = 0;
        }
    }

    int f_krzyzowanie(int **tablica_nPop, int **tablica_sPop)
    {
        for (int i=0 ; i<=liczba_populacji ; i=i+2)
        {
            int losowanie_krzyzowania = losuj(0,10);
            if (losowanie_krzyzowania < krzyzowanie)
            {
                int miejsce_krz = losuj(1,3);
                for (int j=0 ; j<miejsce_krz ; ++j)
                {
                    tablica_sPop[i][j] = tablica_nPop[i][j];
                    tablica_sPop[i+1][j] = tablica_nPop[i+1][j];
                }
                for (int j=miejsce_krz ; j<bity ; ++j)
                {
                    tablica_sPop[i][j] = tablica_nPop[i+1][j];
                    tablica_sPop[i+1][j] = tablica_nPop[i][j];
                }
            } else
            {
                for (int j=0 ; j<bity ; ++j)
                {
                    tablica_sPop[i][j] = tablica_nPop[i][j];
                }
            }
        }
    }

    int f_mutacja(int **tablica_sPop)
    {
            for (int i=0 ; i<liczba_populacji ; ++i)
            {
                    int losowanie_mutacji = losuj(0,10);
                    if (losowanie_mutacji <= mutacja)
                    {
                            int miejsce_mutacji = losuj(0,4);
                            if (tablica_sPop[i][miejsce_mutacji] == 0)
                            {
                                    tablica_sPop[i][miejsce_mutacji] = 1;
                            } else tablica_sPop[i][miejsce_mutacji] = 0;
                    }
            }
    }


