#include <iostream>
using namespace std;
#include "../include/Grid.h"

int main() {

//  Renderer* renderer = Renderer::getInstance();
//  renderer->init();

  Grid * grid = new Grid(4);
//  renderer->setGrid(grid);

//  grid->insertNumber(10, 5);
//  grid->insertNumber(10, 5);
//  grid->insertNumber(11, 5);

//  grid->insertNumber(30, 6);
//  grid->insertNumber(39, 6);

//  grid->insertNumber(60, 7);
//  grid->insertNumber(70, 7);
//  grid->insertNumber(80, 7);

  grid->printGrid();

//  while (renderer->isOpen()) {
//    renderer->getInput();
//    renderer->render();
//  }


  delete grid;
//  renderer->end();
  
  return 0;
}
