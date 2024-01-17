#include "kopalnia.hh"
#include <iostream>

#define PLIK_WEJSCIOWY "dane.txt"

using namespace std;

// w jednym wozku tylko jeden rodzaj kamienia moze byc

int main(int argc , char ** argv)
{

    ifstream dane_plik(PLIK_WEJSCIOWY);

    if(!dane_plik.is_open()){ // jesli nie udalo sie otworzyc pliku zakoncz program
        cout << "blad otwierania pliku!\n";
        return 1;
    }

    vector<Wozek> wozki_vec;

    // wcztytywanie z pliku do vectora wozkow
    string bufor;
    Wozek *wozek_tmp = nullptr;

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
                
                wozek_tmp = new Wozek;

                wozek_tmp->minuta = _minuta;
                wozek_tmp->numer = _numer;
                wozek_tmp->waga = _waga;
                wozek_tmp->liczba_kamieni = _liczba_kamieni;
                wozek_tmp->nazwa_kamienia = _nazwa_kamienia;
                wozek_tmp->czas_obslugi = _czas_obslugi;

                wozki_vec.push_back(*wozek_tmp);
                
                delete wozek_tmp;
            }
            ktore_slowo++;
        }
        ktora_minuta++;
    }
    dane_plik.close();

    for (int i = 0; i < wozki_vec.size(); i++){
        cout << wozki_vec[i].minuta << " " << wozki_vec[i].nazwa_kamienia << " " << wozki_vec[i].liczba_kamieni << " " << wozki_vec[i].waga << endl;
    }
    Kopalnia kopalnia(wozki_vec, 2);

    kopalnia.FCFS();
}
