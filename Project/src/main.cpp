#include <iostream>
#include "../include/Grid.h"

using namespace std;

int main() {
  
  cout << "hola mundo hola!!" << endl;

  Grid * grid = new Grid();

  cout << grid->getLinealPosition(2,2) << endl;

  short x,y;

  grid->getMatrixPosition(20,x,y);

  cout << x << y << endl;

  return 0;
}
