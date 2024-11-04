#ifndef MONEY_H
#define MONEY_H
#include<iostream>
#include<cstring>
#include<vector>
#include <cstdlib>
#include<limits>
#include<fstream>
#include <iomanip>
#include <string>
using namespace std;

//Forward declaration for class TROSAK
class Trosak;
class Database;
//---------------------------------------
//CLASS TROSAK
//---------------------------------------
class Trosak{
    private:
        char* trosak;
        char* mesec;
        int godina;
        int dat_novac, ocekivano, plata;
        bool placeno;
        //virtual char* tip = 0; //Every child class overwrittes tip to be appropriate to the child class (ex: "Potrebstina", "Cef", "Racun"...)
    public:
        Trosak(const char* trosak = "Trosak", int dat_novac = 0, int ocekivano = 0, const char* mesec = "Neodredjeno", int godina = 2024, int plata = 0, bool placeno = false);
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
        //void print_current_month_view();
        //void print_next_month_view();
        //void print_previous_month_view();
        //void print_savings_view();
        //void print_unspecified_month_view();
        //void print_this_yearly_view();
        //void delete_record(Trosak& t);
        //void update_record(Trosak& t);
};


//---------------------------------------
//GENERIC FUNCTIONS
//---------------------------------------
void print_user_interface();// OPTIONS: ENTER A RECORD, DELETE A RECORD, SHOW RECORDS, SEARCH FOR A RECORD, EXIT PROGRAM
void show_database_views(); // WHEN USER INITIALLY ENTERS ACTION 0, SHOWS MULTIPLE VIEWS FROM WHICH TO CHOOSE FURTHER ACTION (ACTION_0 VARIABLE)
//PRINTS START MENU WITH 0-3 OPTIONS
void action_0_3_logic(int& action, Database& d); 
//IF INITIAL ACTION IS 0, WE CHOOSE FROM 1 OF SEVERAL POSSIBLE VIEWS BASED ON ACTION_0 VARIABLE
void action_0_logic(int& action_0, Database& d);
void add_record(Database& d, Trosak& t);
bool is_it_month(const char* mesec);
// Function to print a row with appropriate formatting to any output stream
void printRow(std::ostream& out, const char* trosak, int dat_novac, int ocekivano, const char* mesec, int godina, int plata, bool placeno);
void printHeader(std::ostream& out);
void print_database();

//Additional functionalities
void delete_entire_database();
void delete_last_entry();

#endif
