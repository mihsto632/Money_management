#include "money.cpp"

int main(){

  //Variables gonna be needed when showing specific views that enter current year and current month values
  //int current_year = 2024;
  //const char* current_month = "October";''
  Database database;
  int action;
  //Function enters action (0-3) and does diffent things based on it
   //add_record gets called if action is 1
  action_0_3_logic(action, database);

  return 0;

}
