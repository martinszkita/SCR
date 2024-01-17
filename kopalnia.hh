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
    int numer_robota_obslugujacego;
    string nazwa_kamienia;

    Wozek() { 
        status = 1;
        numer_robota_obslugujacego = -1;
    };
    Wozek(int _minuta, int _numer, int _liczba_kamieni,int _waga, string _nazwa_kamienia); // 
};

class Robot{
    public:
        int wolny = 1; // 1 to wolny , 0 to zajety
        void rozladuj_wozek(Wozek *_wozek);
        Robot(){};
};

class Kopalnia{

    public:
        int liczba_robotow;
        vector<Wozek> wozki;
        Robot * roboty;
        Kopalnia(){};
        Kopalnia(vector<Wozek> _wozki, int _liczba_robotow);
        void FCFS();
};

Kopalnia::Kopalnia(vector<Wozek> _wozki, int _liczba_robotow){
    this->liczba_robotow = _liczba_robotow;
    this->wozki = _wozki;

}

Wozek::Wozek(int  _minuta, int  _numer, int _liczba_kamieni,int _waga, string _nazwa_kamienia){
    this->minuta = _minuta;
    this->numer = _numer;
    this->waga = _waga;
    this->nazwa_kamienia = _nazwa_kamienia;
    this->czas_obslugi = _waga * _liczba_kamieni;
    this->status = 1;
    this->pozostaly_czas_obslugi = czas_obslugi;
}
void Robot::rozladuj_wozek(Wozek * _wozek){
    this->wolny = 0;
    _wozek->pozostaly_czas_obslugi--;
    //_wozek->czas_obslugi--;
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
    int ile_wolnych_robotow = liczba_robotow;

    //mowy motyw dla obslugi wielu robotow
    for (int i = 0; i <= total_czas; i++){
        cout << "MINUTA: " << i << endl;
        for (int j = ile_gotowych_wozkow; j < this->wozki.size(); j++){

            cout << "wozek o nazwie: " << this->wozki[j].nazwa_kamienia << " ma status: " << this->wozki[j].status << endl;
            cout << "wozek o nazwie: " << this->wozki[j].nazwa_kamienia << " time left " << this->wozki[j].pozostaly_czas_obslugi << endl;

            if(this->wozki[j].status == -1 ){ // wozek skonczony
                ile_gotowych_wozkow++;
                ile_wolnych_robotow++;

                // ustaw flage robota ktory obslugiwal dany wozek na wolny
                this->roboty[this->wozki[j].numer_robota_obslugujacego].wolny = 1; 

                cout << "w minucie: " << i << " wozek z: " << this->wozki[j].nazwa_kamienia << " zostal skonczony\n";
            }

            if (ile_wolnych_robotow > 0){ // jesli sa wolne roboty

                // znajdz pierwszego wolnego robota
                for (int k = 0; k < liczba_robotow; k++){
                    if(this->roboty[k].wolny == 1){ // k-ty wozek jest wolny
                        cout << "jest wolny robot" << endl;
                        this->roboty[k].rozladuj_wozek(&(this->wozki[j])); // dla statusu 0 wykona sie tylko tp
                        if (this->wozki[j].status == 1) // dla statusu oczekujacego trzeba pozmieniac
                        {
                            this->wozki[j].status = 0;
                            this->wozki[j].numer_robota_obslugujacego = k;
                            ile_wolnych_robotow--;
                            //cout << this->wozki[j].pozostaly_czas_obslugi << endl;
                        }
                        break;     
                    }
                }
            }
        }
    }
}