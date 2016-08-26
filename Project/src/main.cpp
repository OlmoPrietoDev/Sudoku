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

  while (renderer->isOpen()) {
    renderer->getInput();
    renderer->render();
  }

  renderer->end();

  return 0;
}
