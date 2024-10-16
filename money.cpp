#include "money.h"


int action;

//------------------------------------------
//CLASS TROSAK FUNCTION IMPLEMENTATIONS
//------------------------------------------
//Constructor
Trosak::Trosak(const char* trosak, int dat_novac, int ocekivano, const char* mesec, int godina, int plata, bool placeno){
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
    int dat_novac, ocekivano, plata;
    bool placeno;
    system("reset");
    cout<<"------------------";

    do {
        cout << "\nEnter expense: ";
        // Clearing cin before getline
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cin.getline(trosak, 20); // Read input
         if (strlen(trosak) > 20) {
            cout << "Input too long! Please enter at most 20 characters.\n";
        }
    } while (strlen(trosak) < 1 || strlen(trosak) > 21);

    //cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //Enter money given
    cout<<"\nEnter money given: ";
    cin>>dat_novac;
     // Validate dat_novac input
    while (cin.fail()) {
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << "\033[F\033[K"; //Deletes exactly 1 row
        //cout << "Invalid input. Please enter a numeric value for money given: ";
        cout<<"\nEnter money given: ";
        cin>>dat_novac; // Retry input
    }
    
    do{
        //Enter expected price
        cout<<"\nEnter expected price(must be >= money given): ";
        cin>>ocekivano;
    }
    while(ocekivano < dat_novac);

    //Clearing cin before newline and entering a month
    do{
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"\nEnter month: ";
        cin.getline(mesec, 20);
    }
    while (!is_it_month(mesec) || strlen(mesec) < 1 || strlen(mesec) > 20);

    cout<<"\nEnter year: ";
    cin>>godina;

    cout<<"\nEnter salary: ";
    cin>>plata;
    cout<<"------------------\n\n\n";

    if (dat_novac == ocekivano)
        placeno = true;
    else 
        placeno = false;
    cout<<"\n";

    //WORKING WITH FILES
    //Making object of Trosak t that calls its constructor using variables user has entered
    Trosak t(trosak, dat_novac, ocekivano, mesec, godina, plata, placeno);

    //Add record to a file
    ofstream file("database.txt", ios::app); //opens a file for writing and appending
    //printHeader(file);
    if (!file.is_open()){
        cerr<<"Failed to write a record to database. Please try again.\n";
        exit(1);
    }

    //Writing the actual data to the file
    printRow(file, trosak, dat_novac, ocekivano, mesec, godina, plata, placeno); //Putting the row into file
    //Closing the file
    file.close();
    //END OF WORKING WITH FILES

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
        cout<<"\nExiting the program...\n\n\n\n\n\n";
        exit(0);
    }
}

void print_user_interface(){
    system("reset");
    cout<<"\n-----------------------------------------";
    cout<<"\n\nView database:               \t\t0";
    cout<<"\n\nAdd record:                   \t\t1";
    //cout<<"\n\nSearch for record by keyword: \t\t2";
    cout<<"\n\nExit the program:             \t\t2";
    cout<<"\n-----------------------------------------\n\n\n";
}

//Switch-case logic to ensure right action is taken when user enters action
void action_0_3_logic(int& action, Database& d){
    print_user_interface();
    do{
        cout<<"\nEnter action: ";
        cin>>action;

        if (cin.fail() || action <0 || action >2){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            action = -1;
            cout<<"Invalid action. Please try again: ";
        }
    }
    while(action < 0 || action > 2);
    
    switch(action){
        case 0: //View database
            system("reset");
            print_database();
            int action_0;
            cout<<"\n\n\n---------------------------------";
            cout<<"\nReturn to main menu: \t\t0";
            cout<<"\nDelete database: \t\t1";
            cout<<"\nExit the program: \t\t2";
            cout<<"\n---------------------------------\n\n\n";
            do{
                cout<<"\nEnter valid action: ";
                cin >> action_0;
            }
            while(action_0 < 0 || action_0 > 2);
            
            switch(action_0){
                case 0: //Return to main menu
                    action_0_3_logic(action, d);
                    break;               
                case 1: //Delete entire database
                    system("reset");
                    int delete_database_0_1;
                    do{
                        cout<<"----------------------------------------------------------------\n";
                        cout<<"Are you sure? You won't be able to retrieve data after deletion.\n\t-Yes, delete the entire database \t0\n\t-No, keep the database \t\t\t1";
                        cout<<"\n----------------------------------------------------------------\n";
                        cout<<"\n\nChoose action: ";
                        cin>> delete_database_0_1;
                    }
                    while (delete_database_0_1 < 0 || delete_database_0_1 > 1);
                    delete_entire_database();
                    action_0_3_logic(action, d);
                    break;
                case 2:
                    system("reset");
                    cout<<"Exiting the program...\n\n\n\n\n\n";
                    exit(0); //Alternative to return 0, which can't be used in void functions
                    break;
            }
            break;
        case 1: //Add record
            add_record(d); //Adds t to d and prints t
            action_0_3_logic(action, d);
            break;
        /*case 2: //Search for record by keyword
            //search_in_database(char* keyword); //Future function
            action_0_3_logic(action, d);
            break;*/
        case 2: //Exit the program
            system("reset");
            cout<<"Exiting the program...\n\n\n\n\n\n";
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
// Function to print a row with appropriate formatting to any output stream
void printRow(std::ostream& out, const char* trosak, int dat_novac, int ocekivano, const char* mesec, int godina, int plata, bool placeno) {
    out << std::left 
        << std::setw(20) << (strlen(trosak) == 0 ? "N/A" : trosak) 
        << std::setw(20) << (dat_novac == 0.0 ? "0" : std::to_string(dat_novac)) 
        << std::setw(20) << (ocekivano == 0.0 ? "0" : std::to_string(ocekivano)) 
        << std::setw(20) << (strlen(mesec) == 0 ? "N/A" : mesec) 
        << std::setw(20) << (godina == 0 ? "N/A" : std::to_string(godina)) 
        << std::setw(20) << (plata == 0.0 ? "0" : std::to_string(plata))
        << std::setw(20) << (placeno ? "Da" : "Ne")
        << std::endl;
}

// Function to print the table header to any output stream
void printHeader(std::ostream& out) {
    out << left
        << setw(20) << "Trosak" 
        << setw(20) << "Dat novac" 
        << setw(20) << "Ocekivano" 
        << setw(20) << "Mesec"
        << setw(20) << "Godina" 
        << setw(20) << "Plata" 
        << setw(20) << "Placeno" 
        << '\n';
    //out <<"-----------------------------------"; // Draw a separator line
    out<< std::string(140, '-')<<'\n';
}

//Function that shows database views (0 option in Actions beginning menu)
void show_database_views(){
    system("reset");
    cout<<"----------------------------------\n";
    cout<<"Full database: \t\t\t0";
    cout<<"\nCurrent month: \t\t\t1";
    cout<<"\nNext month:    \t\t\t2";
    cout<<"\nPrevious month:\t\t\t3";
    cout<<"\nSavings:       \t\t\t4";
    cout<<"\nCurrent year:  \t\t\t5";
    cout<<"\nReturn to main menu: \t\t6";
    cout<<"\nExit the program: \t\t7";
    cout<<"\n----------------------------------\n\n\n";
}


//Switch-case logic to ensure right action is taken (only present when inition action is 0, so subsequent action_0 needs to be chosen)
/*void action_0_logic(int& action_0, Database& d){
    show_database_views();
    do{
        cout<<"\nSelect action: ";
        cin>>action_0;

        if (cin.fail() || action_0 <0 || action_0 >7){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            action_0 = -1;
            cout<<"Invalid action. Please try again: ";
            show_database_views();
        }
    }
    while(action_0 < 0 || action_0 > 7);
    
    switch(action_0){
        case 0: //Full database
            //printRow(file, "Alice", 2024, "January", 5.34, 7.89, 0.0, true);
            //void print_database(); // FUTURE FUNCTION
            //action_o_logic(action_o, d);
            //action_0_3_logic(action, d);
            break;
        case 1: //Current month
            //void print_current_month_view(); // FUTURE FUNCTION
            break;
        case 2: //Next month
            //void print_next_month_view(); // FUTURE FUNCTION
            break;
        case 3: //Previous month
            system("reset");
            //void print_previous_month_view(); // FUTURE FUNCTION
        case 4: //Savings
            system("reset");
            //void print_savings_view(); // FUTURE FUNCTION
        case 5: //Current year
            system("reset");
            //void print_this_yearly_view(); // FUTURE FUNCTION
        case 6: //Return to main menu
            system("reset");
            action_0_3_logic(action, d);
        case 7:
            system("reset");
            cout<<"Exiting the program...\n\n\n";
            exit(1);
        default: 
            show_database_views();
            break;
    }
}*/

//Function that reads database from the 
void print_database(){
    const int MAX_LINE_LENGTH = 256;  // Define a maximum line length
    char line[MAX_LINE_LENGTH];        // C-style string (character array)

    FILE* file = fopen("database.txt", "r");  // Open the file in read mode

    // Check if the file was opened successfully
    if (file == nullptr) {
        std::cerr << "Error: Could not open the file." << std::endl;
        exit(1);
    }

    // Read each line from the file and print it
    while (fgets(line, MAX_LINE_LENGTH, file) != nullptr) {
        std::cout << line;  // Print the line (fgets includes the newline character)
    }

    fclose(file);  // Close the file
}

//Function that deletes the entire database
void delete_entire_database(){
    ofstream file1("database.txt");
    printHeader(file1);
    file1.close();
}
