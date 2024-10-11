#include "money.cpp"

int main(){

  Trosak t1;
  Trosak t2("Hlebac", 2024, "OktoMbar", 1850, 3310, 120000, false);

  Database database;
  database.add_record(t1);
  database.add_record(t2);

  t1.print_record();
  t2.print_record();///////////

  return 0;
}
