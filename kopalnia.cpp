#include "kopalnia.hh"
#include <vector>

#define PLIK_WEJSCIOWY "dane.txt"

using namespace std;

// w jednym wozku tylko jeden rodzaj kamienia moze byc

int main()
{

    ifstream dane_plik(PLIK_WEJSCIOWY);

    if(!dane_plik.is_open()){ // jesli nie udalo sie otworzyc pliku zakoncz program
        cout << "blad otwierania pliku!\n";
        return 1;
    }

    vector<Wozek> wozki_vec;

    // wcztytywanie z pliku do vectora wozkow
    string bufor;
    // Wozek *wozek_tmp = nullptr;

    while(getline(dane_plik,bufor)){ // dopoki udaje sie czytac z pliku

        istringstream strumien(bufor); // utworz strumien wejsciowy z bufora
        string slowo;
        int ktore_slowo = 0;

        // zmienne potrzebne do podania dla argumentow kontruktora parametrycznego klasy Wozek
        int ktora_minuta;
        int _numer;
        int _liczba_kamieni;
        int _waga;
        int _czas_obslugi;
        int _minuta;

        string _nazwa_kamienia;

        strumien >> slowo; // wczytaj pierwszy znak z kazdej linii
        ktora_minuta = stoi(slowo); // bo to jest numer minuty

        while (strumien >> slowo)
        {
            ktore_slowo = ktore_slowo % 4;
            if (ktore_slowo ==0){
                //wozek_tmp = new Wozek;
                _numer = stoi(slowo);
                _minuta = ktora_minuta;
            }
            else if (ktore_slowo == 1){
  
                _nazwa_kamienia =slowo;
            }
            else if (ktore_slowo == 2){

                _liczba_kamieni = stoi(slowo);
            }
            else if (ktore_slowo == 3){

                _waga = stoi(slowo);
                _czas_obslugi = (_waga) * (_liczba_kamieni);
                Wozek wozek_tmp(_minuta, _numer, _liczba_kamieni, _waga, _nazwa_kamienia);

                // if (wozek_tmp == nullptr)
                // {
                //     cerr << "blad dodawania wozka do wektora!\n";
                //     return -1;
                // }
                // wozek_tmp = new Wozek()
                wozki_vec.push_back(wozek_tmp);
                //delete wozek_tmp;
            }
            ktore_slowo++;
        }
        ktora_minuta++;
    }
    dane_plik.close();

    Kopalnia kopalnia(wozki_vec,1);

    kopalnia.FCFS();
}