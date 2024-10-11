#ifndef MONEY_H
#define MONEY_H
#include<iostream>
#include<cstring>
#include<vector>
#include <cstdlib>
using namespace std;

//Forward declaration for class TROSAK
class Trosak;
class Database;

wchar_t check_mark = L'\u2713'; // ✓
wchar_t cross_mark = L'\u2717'; // ✗

//---------------------------------------
//VECTOR TABLE
//---------------------------------------


//---------------------------------------
//CLASS TROSAK
//---------------------------------------
class Trosak{
    private:
        char* trosak;
        char* mesec;
        int godina;
        double dat_novac, ocekivano, plata;
        bool placeno;
        //virtual char* tip = 0; //Every child class overwrittes tip to be appropriate to the child class (ex: "Potrebstina", "Cef", "Racun"...)
    public:
        Trosak(const char* trosak = "Trosak", int godina = 2024, const char* mesec = "Neodredjeno", double dat_novac = 0.0, double ocekivano = 0.0, double plata = 0.0, bool placeno = false);
        ~Trosak();
        Trosak(const Trosak& t); //copy constructor
        void print_record();
};


//---------------------------------------
//CLASS DATABASE
//---------------------------------------
class Database{
    private:
        vector<Trosak> Table;
        int redni_broj;
        float usteda;
    public:
        void add_record(const Trosak& t);
        //void delete_record(Trosak& t);
        //void change_record(Trosak& t);
};


//---------------------------------------
//GENERIC FUNCTIONS
//---------------------------------------
void print_user_interface();// OPTIONS: ENTER A RECORD, DELETE A RECORD, SHOW RECORDS, SEARCH FOR A RECORD, EXIT PROGRAM

#endif
