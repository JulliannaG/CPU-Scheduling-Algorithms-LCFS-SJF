// Symulacja1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct proces {
    int czas_przybycia;
    int czas_trwania;
    int numer;
};
int generator(int zakres) {
    int random = zakres + rand() % 20; 
    return random;
}
void odczyt_danych_z_pliku(proces* p, string nazwa_pliku) {
    fstream plik;
    plik.open(".\\dane\\" + nazwa_pliku, ios::in);
    if (!plik.is_open())
        cout << "Plik nie zostal otwarty";
    string wartosc;
    getline(plik, wartosc);//sczytanie początkowego tekstu z pliku
    for (int i = 0; i < 100; i++) {
        plik >> p[i].czas_przybycia >> wartosc >> p[i].czas_trwania; //zmienna 'wartość' sczytuje przecinek
        p[i].numer = i+1;
    }
    plik.close();
}
void zapelnienie_kolejki(proces* x, vector<proces>* wektor, int t1, int t2) {
    for (int t = t1; t <= t2; t++) { // t1-t2 to przedział czasu, w którym przychodzą nowe procesy do kolejki w trakcie realizacji innego procesu
        for (int i = 0; i < 100; i++) { //sprawdzenie i dołożenie do kolejki procesów, których czas przybycia jest zgodny z aktualnym czasem t
            if (x[i].czas_przybycia == t)
                (*wektor).push_back(x[i]);
        }
    }
}
void LCFS(vector<proces>* wektor) { //sortowanie kolejki wg algorytmu LCFS

    for (int i = 0; i < (*wektor).size(); i++)
        for (int j = 1; j < (*wektor).size() - i; j++)
            if ((*wektor)[j - 1].czas_przybycia < (*wektor)[j].czas_przybycia)//porównywany jest czas przybycia
                swap((*wektor)[j - 1], (*wektor)[j]);

}
void SJF(vector<proces>* wektor) { //sortowanie wg algorytmu SJF

    for (int i = 0; i < (*wektor).size(); i++)
        for (int j = 1; j < (*wektor).size() - i; j++)
            if ((*wektor)[j - 1].czas_trwania > (*wektor)[j].czas_trwania) //porównywany jest czas trwania
                swap((*wektor)[j - 1], (*wektor)[j]);

}
void kolejkowanie_procesow(proces* p, string nazwa_algorytmu, string nazwa_pliku, float* sredni_czas_oczekiwania, float* sredni_czas_przetwarzania) {
    vector <proces> kolejka; //stworzenie wektora przechowującego kolejkę procesów gotowych do realizacji
    fstream plik;
    plik.open(".\\dane\\" + nazwa_pliku, ios::out);

    int t1 = 0; //początek realizacji procesu
    int t2 = 0; //koniec realizacji procesu
    float calkowity_czas_oczekiwania = 0; //zmienne przechowujące uśrednione wartości dla jednego ciągu realizowanego algorytmem LCFS
    float calkowity_czas_przetwarzania = 0;
    int n = 100; //ilość procesów pozostałych do wykonania
    plik << "Numer procesu" << ", " << "Czas oczekiwania[s]" << ", " << "Czas przetwarzania[s]" << endl;

    do {
        zapelnienie_kolejki(p, &kolejka, t1, t2);

        if (!kolejka.empty()) { //jeśli kolejka nie jest pusta
            if (nazwa_algorytmu == "LCFS")
                LCFS(&kolejka); //sortowanie kolejki algorytmem LCFS
            if (nazwa_algorytmu == "SJF")
                SJF(&kolejka); //sortowanie kolejki algorytmem SJF
            int czas_oczekiwania = t2 - kolejka[0].czas_przybycia; //obliczamy czas oczekiwania i przetwarzania
            int czas_przetwarzania = t2 - kolejka[0].czas_przybycia + kolejka[0].czas_trwania;

            plik << kolejka[0].numer << ", " << czas_oczekiwania << ", " << czas_przetwarzania << endl;

            calkowity_czas_oczekiwania += czas_oczekiwania; //dane potrzebne do uśrednienia końcowych wartości
            calkowity_czas_przetwarzania += czas_przetwarzania;
            t1 = t2 + 1; //zwiększenie wartości czasów
            t2 += kolejka[0].czas_trwania;
            kolejka.erase(kolejka.begin()); //usunięcie procesu z kolejki
            n--; //zmniejszenie liczby procesów pozostałych do ralizacji
        }
        else { //jeśli kolejka jest pusta to zwiększamy czas
            t1 = t2 + 1;
            t2 += 1;
        }
    } while (n != 0); //pętla wykonuje dopóki wszystkie procesy nie zostaną wykonane

    *sredni_czas_oczekiwania = calkowity_czas_oczekiwania / 100; //obliczanie średnich wartości dla pojedyńczego ciągu
    *sredni_czas_przetwarzania = calkowity_czas_przetwarzania / 100;

    plik << "Sredni czas oczekiwania [s]" << ", " << "Średni czas przetwarzania [s]" << endl;
    plik << *sredni_czas_oczekiwania << ", " << *sredni_czas_przetwarzania << endl;
    plik.close();
}

int main()
{
    srand((unsigned)time(NULL)); //potrzebne do generowania losowych wartości

    float calkowity_czas_oczekiwania_LCFS = 0;  //zmienne przechowujące zsumowane wartości czasów dla 100 ciągów
    float calkowity_czas_przetwarzania_LCFS = 0;
    float calkowity_czas_oczekiwania2_SJF = 0;
    float calkowity_czas_przetwarzania2_SJF = 0;

    string nazwa_pliku4 = "wyniki_eksperymentu.csv";
    fstream plik1;
    fstream plik4;

    plik4.open(".\\dane\\" + nazwa_pliku4, ios::out);
    plik4 << "Średnie wartości dla kolejnych ciągów:" << endl;
    plik4 << "LCFS-średni czas oczekiwania [s]" << ", " << "LCFS-średni czas przetwarzania [s]" << "," << "SJF-średni czas oczekiwania[s]" << ", " << "SJF-średni czas przetwarzania [s]" << endl;

    for (int k = 0; k < 100; k++) { //tworzenie 100 ciągów

        string K = to_string(k + 1);
        string nazwa_pliku1 = "dane_wejsciowe" + K + ".csv"; //generowanie różnych nazw plików dla danych wejściowych
        string nazwa_pliku2 = "LCFS" + K + ".csv";
        string nazwa_pliku3 = "SJF" + K + ".csv";

        //generowanie losowych wartości czasu przyjścia i trwania procesu oraz ich zapis do pliku
        plik1.open(".\\dane\\" + nazwa_pliku1, ios::out);
        plik1 << "Czas przybycia procesu [s]" << ", " << "Czas trwania procesu [s]" << endl;
        for (int i = 0; i < 100; i++) { 
            plik1 << generator(0) << ", " << generator(1) << endl;
        }
        plik1.close();

        proces p[100];//stworzenie tablicy struktury
        odczyt_danych_z_pliku(&p[0], nazwa_pliku1);

        float sredni_czas_oczekiwania_LCFS = 0; //zmienne przechowujące średni czas dla jednego ciągu, algorytm LCFS
        float sredni_czas_przetwarzania_LCFS = 0;

        kolejkowanie_procesow(p, "LCFS", nazwa_pliku2, &sredni_czas_oczekiwania_LCFS, &sredni_czas_przetwarzania_LCFS);

        calkowity_czas_oczekiwania_LCFS += sredni_czas_oczekiwania_LCFS;
        calkowity_czas_przetwarzania_LCFS += sredni_czas_przetwarzania_LCFS;

        float sredni_czas_oczekiwania_SJF = 0; //zmienne przechowujące średni czas dla jednego ciągu, algorytm SJF
        float sredni_czas_przetwarzania_SJF = 0;

        kolejkowanie_procesow(p, "SJF", nazwa_pliku3, &sredni_czas_oczekiwania_SJF, &sredni_czas_przetwarzania_SJF);

        calkowity_czas_oczekiwania2_SJF += sredni_czas_oczekiwania_SJF;
        calkowity_czas_przetwarzania2_SJF += sredni_czas_przetwarzania_SJF;

        plik4 << sredni_czas_oczekiwania_LCFS << ", " << sredni_czas_przetwarzania_LCFS << ", " << sredni_czas_oczekiwania_SJF << ", " << sredni_czas_przetwarzania_SJF << endl;
    }

    plik4 << "Średni czas oczekiwania i przetwarzania dla 100 ciągów:" << endl;

    float sredni_czas_oczekiwania_LCFS_v2 = calkowity_czas_oczekiwania_LCFS / 100; //obliczanie uśrednionych wartości dla 100 ciągów
    float sredni_czas_przetwarzania_LCFS_v2 = calkowity_czas_przetwarzania_LCFS / 100;
    plik4 << "Sredni czas oczekiwania dla algorytmu LCFS [s]" << ", " << "Średni czas przetwarzania dla algorytmu LCFS [s]" << endl;
    plik4 << sredni_czas_oczekiwania_LCFS_v2 << ", " << sredni_czas_przetwarzania_LCFS_v2 << endl;

    float sredni_czas_oczekiwania2_SJF_v2 = calkowity_czas_oczekiwania2_SJF / 100;
    float sredni_czas_przetwarzania_SJF_v2 = calkowity_czas_przetwarzania2_SJF / 100;
    plik4 << "Sredni czas oczekiwania dla algorytmu SJF [s]" << ", " << "Średni czas przetwarzania dla algorytmu SJF [s]" << endl;
    plik4 << sredni_czas_oczekiwania2_SJF_v2 << ", " << sredni_czas_przetwarzania_SJF_v2 << endl;

    plik4.close();
}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
