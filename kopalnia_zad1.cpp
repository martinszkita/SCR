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
    Wozek *wozek_tmp = nullptr;

    while(getline(dane_plik,bufor)){ // dopoki udaje sie czytac z pliku

        istringstream strumien(bufor); // utworz strumien wejsciowy z bufora
        string slowo;
        int ktore_slowo = 0;
        int ktora_minuta;

        strumien >> slowo; // wczytaj pierwszy znak z kazdej linii
        ktora_minuta = stoi(slowo); // bo to jest numer minuty

        while (strumien >> slowo)
        {
            ktore_slowo = ktore_slowo % 4;
            if (ktore_slowo ==0){
                wozek_tmp = new Wozek;
                wozek_tmp->numer = stoi(slowo);
                wozek_tmp->minuta = ktora_minuta;
            }
            else if (ktore_slowo == 1){
  
                wozek_tmp->nazwa_kamienia =slowo;
            }
            else if (ktore_slowo == 2){

                wozek_tmp->liczba_kamieni = stoi(slowo);
            }
            else if (ktore_slowo == 3){

                wozek_tmp->waga = stoi(slowo);
                wozek_tmp->czas_obslugi = (wozek_tmp->waga) * (wozek_tmp->liczba_kamieni);

                if (wozek_tmp == nullptr)
                {
                    cerr << "blad dodawania wozka do wektora!\n";
                    return -1;
                }
                wozki_vec.push_back(*wozek_tmp);
                delete wozek_tmp;
            }
            ktore_slowo++;
        }
        ktora_minuta++;
    }
    dane_plik.close();

    for (int i = 0; i < wozki_vec.size(); i++){
        cout << wozki_vec[i].minuta << " ";
        cout << wozki_vec[i].numer << " ";
        cout << wozki_vec[i].nazwa_kamienia<< " ";
        cout << wozki_vec[i].liczba_kamieni<< " ";
        cout << wozki_vec[i].waga<< endl;
    }
}