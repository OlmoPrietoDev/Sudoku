#include <iostream>
#include "../include/Grid.h"
using namespace std;

int main() {

  Grid * grid = new Grid();

  cout << grid->getLinealPosition(2,2) << endl;

  short x,y;

  grid->getMatrixPosition(20,x,y);

  cout << x << y << endl;

  grid->insertNumber(10, 5);
  grid->insertNumber(11, 5);
  grid->insertNumber(19, 5);

  grid->insertNumber(30, 6);
  grid->insertNumber(40, 6);
  grid->insertNumber(50, 7);

  grid->printGrid();

  delete grid;

  return 0;
}
