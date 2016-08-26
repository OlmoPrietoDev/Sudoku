#include <iostream>
#include "../include/Grid.h"
using namespace std;
#include "renderer.h"

int main() {

  Renderer* renderer = Renderer::getInstance();
  renderer->init();

  while (renderer->isOpen()) {
    renderer->getInput();
    renderer->render();
  }

  renderer->end();

  Grid * grid = new Grid();

  cout << grid->getLinealPosition(2,2) << endl;

  short x,y;

  grid->getMatrixPosition(20,x,y);

  cout << x << y << endl;

  return 0;
}
