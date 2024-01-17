#pragma once
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>

using namespace std;

class Wozek
{
public:

    int minuta;
    int numer;
    int waga;
    int czas_obslugi;
    int pozostaly_czas_obslugi;
    int liczba_kamieni;
    int status; // do oblusgi -1 to obsluga gotowa , 0 to w trakcie pracy , 1 to oczekujacy
    string nazwa_kamienia;

    Wozek() { status = 1; };
    Wozek(int _minuta, int _numer, int _liczba_kamieni,int _waga, string _nazwa_kamienia);
};

Wozek::Wozek(int _minuta, int _numer, int _liczba_kamieni,int _waga, string _nazwa_kamienia){
    this->minuta = _minuta;
    this->numer = _numer;
    this->waga = _waga;
    this->nazwa_kamienia = _nazwa_kamienia;
    this->czas_obslugi = _waga * _liczba_kamieni;
    // this->status = 1;
    this->pozostaly_czas_obslugi = czas_obslugi;
}

class Kopalnia{

    public:
        int liczba_robotow;
        vector<Wozek> wozki;

        Kopalnia(){};
        Kopalnia(vector<Wozek> _wozki, int _liczba_robotow);
        void FCFS();
};

Kopalnia::Kopalnia(vector<Wozek> _wozki, int _liczba_robotow){
    this->liczba_robotow = _liczba_robotow;
    this->wozki = _wozki;
}

void Kopalnia::FCFS(){
    
    // obliczanie calkowitego czasu potrzebnego do obslugi wszystkich wozkow

    int total_czas = 0;
    for(auto & _wozek : this->wozki){
        total_czas += _wozek.czas_obslugi;
    }

    // jesli bylaby nieparzysta suma czasow to zaokragli do dolu wiec dodajemy jedynke
    total_czas % 2 == 0 ? total_czas = total_czas / this->liczba_robotow : total_czas = (total_czas / this->liczba_robotow ) + 1;

    int ile_gotowych_wozkow = 0;

    for (int i = 0; i <= total_czas; i++){ // w kazdej minucie
        cout << "MINUTA: " << i << endl;
        for (int j = ile_gotowych_wozkow; j < this->wozki.size(); j++) // dla kazdego wozka na liscie
        { 
            cout << "wozek o nazwie: " << this->wozki[j].nazwa_kamienia << " ma status: " << this->wozki[j].status << endl;
            cout << "wozek o nazwie: " << this->wozki[j].nazwa_kamienia << " time left " << this->wozki[j].pozostaly_czas_obslugi << endl;
            if (this->wozki[j].status == 0)// jesli jest w trakcie obslugi
            {                                   
                this->wozki[j].pozostaly_czas_obslugi--; // odejmiij mu pozostaly czas
                if(this->wozki[j].pozostaly_czas_obslugi <= 0){ // jesli zostal juz calkowicie obsluzony
                    this->wozki[j].status = -1;                 // zmien mu status na gotowy
                    ile_gotowych_wozkow++;
                    cout << "w minucie: " << i << " wozek z: " << this->wozki[j].nazwa_kamienia << " zostal skonczony\n";
                    break;
                }
                break;
            }
            else if( this->wozki[j].status == 1){ // wozek oczekujacy
                this->wozki[j].pozostaly_czas_obslugi--;
                this->wozki[j].status = 0;
                break;
            }
            // else if(this->wozki[j].status == -1){ // obsluga skonczona
            //     cout << "w minucie: " << i << " wozek z: " << this->wozki[j].nazwa_kamienia << " zostal skonczony\n";
            //     ile_gotowych_wozkow++;
            //     break;
            // }
        }
    }
}