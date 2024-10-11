#include "money.h"

//------------------------------------------
//CLASS TROSAK FUNCTION IMPLEMENTATIONS
//------------------------------------------
//Constructor
Trosak::Trosak(const char* trosak, int godina, const char* mesec, double dat_novac, double ocekivano, double plata, bool placeno){
    if (trosak){
        //Copying info from expense local variable to trosak class member
        int broj_bajtova_trosak = strlen(trosak) + 1;
        this->trosak = new char[broj_bajtova_trosak];
        strcpy (this->trosak, trosak);
    }
    else
        this->trosak = nullptr;

    if (mesec){
        //Copying info about month from mesec to this->mesec
        int broj_bajtova_mesec = strlen(mesec) + 1;
        this->mesec = new char[broj_bajtova_mesec];
        strcpy(this->mesec, mesec);
    }
    else
        this->mesec = nullptr;

    this->godina = godina;
    this->dat_novac = dat_novac;
    this->ocekivano = ocekivano;
    this->plata = plata;
    this->placeno = placeno;
}

//Destructor
Trosak::~Trosak(){
    delete[] this->trosak;
    delete[] this->mesec;
}


//Copy constructor
Trosak::Trosak(const Trosak& t){
    this->trosak = new char(*t.trosak);
    this->godina = t.godina;
    this->mesec = new char(*t.mesec);
    this->dat_novac = t.dat_novac;
    this->ocekivano = t.ocekivano;
    this->plata = t.plata;
    this->placeno = t.placeno;
}



//Function that prints the record that has been created
void Trosak::print_record(){
    cout<<"Record created:\n\tTrosak: "<<this->trosak<<"\n\tGodina: "<<this->godina<<"\n\tMesec: "<<this->mesec<<"\n\tDat novac: "<<this->dat_novac<<"\n\tOcekivano: "<<this->ocekivano<<"\n\tPlata: "<<this->plata<<" RSD";
    if (placeno){
        cout<<"\n\tPlaceno: da\n\n";
        //cout<<"\n\tPlaceno: "<<L'\u2713'<<"\n\n";
    }
    else
        cout<<"\n\tPlaceno: ne\n\n";
        //cout<<"\n\tPlaceno: "<<L'\u2717'<<"\n\n";
}

//------------------------------------------
//CLASS DATABASE FUNCTION IMPLEMENTATIONS
//------------------------------------------
//Function that adds a record
void Database::add_record(const Trosak& t){
    Table.push_back(t);
}


