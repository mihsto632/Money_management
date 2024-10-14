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
    system("reset");
    cout<<"------------------\n";
    cout<<"Record created:\n\tTrosak: "<<this->trosak<<"\n\tGodina: "<<this->godina<<"\n\tMesec: "<<this->mesec<<"\n\tDat novac: "<<this->dat_novac<<"\n\tOcekivano: "<<this->ocekivano<<"\n\tPlata: "<<(this->plata/1000)<<"K RSD";
    if (placeno){
        cout<<"\n\tPlaceno: da";
        //cout<<"\n\tPlaceno: "<<L'\u2713'<<"\n\n";
    }
    else
        cout<<"\n\tPlaceno: ne";
        //cout<<"\n\tPlaceno: "<<L'\u2717'<<"\n\n";
    cout<<"\n------------------\n\n\n";
}

//------------------------------------------
//CLASS DATABASE FUNCTION IMPLEMENTATIONS
//------------------------------------------
//Function that adds a record
void Database::add_record(const Trosak& t){
    Table.push_back(t);
}

//Function to print the database in its entirety


//------------------------------------------
//GENERIC FUNCTION IMPLEMENTATIONS
//------------------------------------------
void add_record(Database& d){
    char* trosak = new char[20];
    int godina; 
    char* mesec = new char[20];
    double dat_novac, ocekivano, plata;
    bool placeno;
    system("reset");
    cout<<"------------------";

    do{
        cout<<"\nEnter the expense: ";
        //Clearing cin before getline
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(trosak, 20);
    }
    while (strlen(trosak) < 1 || strlen(trosak) > 20);
    
    cout<<"\nEnter year: ";
    cin>>godina;

    //Clearing cin before newline and entering a month
    do{
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"\nEnter month: ";
        cin.getline(mesec, 20);
    }
    while (!is_it_month(mesec) || strlen(mesec) < 1 || strlen(mesec) > 20);

    cout<<"\nEnter expected price: ";
    cin>>ocekivano;
    do {
        cout<<"\nEnter money given(must be <= than expected): ";
        cin>>dat_novac;
    }
    while (dat_novac > ocekivano);\

    cout<<"\nEnter salary: ";
    cin>>plata;
    cout<<"------------------\n\n\n";

    if (dat_novac == ocekivano)
        placeno = true;
    else 
        placeno = false;
    cout<<"\n";

    //Making object of Trosak t that calls its constructor using variables user has entered
    Trosak t(trosak, godina, mesec, dat_novac, ocekivano, plata, placeno);

    //add_record as a part of database object
    d.add_record(t);
    delete[] trosak;
    delete[] mesec;

    t.print_record();
    cout<<"\n\nReturn to Actions: 0";
    cout<<"\nExit the program: 1";
    cout<<"\n------------------\n";
    int return_to_actions;
    do{
        cout<<"Enter action: ";
        cin>>return_to_actions;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (return_to_actions != 0 && return_to_actions != 1);
    if (return_to_actions == 0)
        return;
    else{
        system("reset");
        cout<<"\nExiting the program...\n";
        exit(0);
    }
}

void print_user_interface(){
    system("reset");
    cout<<"\n-----------------------------------------";
    cout<<"\n\nDatabase views:               \t\t0";
    cout<<"\n\nAdd record:                   \t\t1";
    cout<<"\n\nSearch for record by keyword: \t\t2";
    cout<<"\n\nExit the program:             \t\t3";
    cout<<"\n-----------------------------------------\n\n\n";
}

//Switch-case logic to ensure right action is taken when user enters action
void action_0_3_logic(int& action, Database& d){
    print_user_interface();
    do{
        cout<<"\nEnter action: ";
        cin>>action;

        if (cin.fail() || action <0 || action >3){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            action = -1;
            cout<<"Invalid action. Please try again: ";
        }
    }
    while(action < 0 || action > 3);
    
    switch(action){
        case 0: //Enter database views
            //show_database_views(); //Future function
            action_0_3_logic(action, d);
            break;
        case 1: //Add record
            add_record(d); //Adds t to d and prints t
            action_0_3_logic(action, d);
            break;
        case 2: //Search for record by keyword
            //search_in_database(char* keyword); //Future function
            action_0_3_logic(action, d);
            break;
        case 3: //Exit the program
            system("reset");
            cout<<"Exiting the program...\n\n\n";
            exit(0); //Alternative to return 0, which can't be used in void functions
        default: 
            break;
    }
}

bool is_it_month(const char* mesec){
    if (strcmp(mesec, "JANUARY") == 0   || strcmp(mesec, "January") == 0   || strcmp(mesec, "january") == 0   ||
        strcmp(mesec, "FEBRUARY") == 0  || strcmp(mesec, "February") == 0  || strcmp(mesec, "february") == 0  ||
        strcmp(mesec, "MARCH") == 0     || strcmp(mesec, "March") == 0     || strcmp(mesec, "march") == 0     ||
        strcmp(mesec, "APRIL") == 0     || strcmp(mesec, "April") == 0     || strcmp(mesec, "april") == 0     ||
        strcmp(mesec, "MAY") == 0       || strcmp(mesec, "May") == 0       || strcmp(mesec, "may") == 0       ||
        strcmp(mesec, "JUNE") == 0      || strcmp(mesec, "June") == 0      || strcmp(mesec, "june") == 0      ||
        strcmp(mesec, "JULY") == 0      || strcmp(mesec, "July") == 0      || strcmp(mesec, "july") == 0      ||
        strcmp(mesec, "AUGUST") == 0    || strcmp(mesec, "August") == 0    || strcmp(mesec, "august") == 0    ||
        strcmp(mesec, "SEPTEMBER") == 0 || strcmp(mesec, "September") == 0 || strcmp(mesec, "september") == 0 ||
        strcmp(mesec, "OCTOBER") == 0   || strcmp(mesec, "October") == 0   || strcmp(mesec, "october") == 0   ||
        strcmp(mesec, "NOVEMBER") == 0  || strcmp(mesec, "November") == 0  || strcmp(mesec, "november") == 0  ||
        strcmp(mesec, "DECEMBER") == 0  || strcmp(mesec, "December") == 0  || strcmp(mesec, "december") == 0)
            return true;
    else 
            return false;
}

