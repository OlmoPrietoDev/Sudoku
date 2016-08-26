#include <iostream>
using namespace std;
#include "Grid.h"
#include "renderer.h"

int main() {

  Renderer* renderer = Renderer::getInstance();
  renderer->init();

  Grid * grid = new Grid();
  renderer->setGrid(grid);

  cout << grid->getLinealPosition(2, 2) << endl;

  short x, y;

  grid->getMatrixPosition(20, x, y);

  cout << x << y << endl;

  grid->insertNumber(10, 5);
  grid->insertNumber(11, 5);
  grid->insertNumber(19, 5);

  grid->insertNumber(30, 6);
  grid->insertNumber(40, 6);
  grid->insertNumber(50, 7);

  grid->printGrid();

  while (renderer->isOpen()) {
    renderer->getInput();
    renderer->render();
  }


  delete grid;
  renderer->end();
  
  return 0;
}
