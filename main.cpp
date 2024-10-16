#include "money.cpp"

int main(){

  //Logic that opens file for reading (ifstream), checks if file is empty, opens file for writing, and prints the header (for some reason, can't check if file is empty when file already opened for writing)
  ifstream file("database.txt");
  if (file.get() == std::ifstream::traits_type::eof()){
    file.close();
    ofstream file("database.txt", ios::app);
    printHeader(file);
    file.close();
  }

  //Creating database object that will contain a vector filled with information
  Database database;
  int action; //action will be passed to action_0_3_logic for navigating the initial menu

  //Function enters action (0-3) and does diffent things based on it
   //add_record gets called if action is 1
  action_0_3_logic(action, database); // INITIAL MENU

  return 0;

}
