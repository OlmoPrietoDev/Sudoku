#include <iostream>
<<<<<<< HEAD

#include "renderer.h"
=======
using namespace std;
>>>>>>> f4bf3d470911fa22689dee0c23d51b7b11b5b5b3

int main() {
  
  cout << "hola mundo hola!!" << endl;

<<<<<<< HEAD
  Renderer* renderer = Renderer::getInstance();
  renderer->init();

  while (renderer->isOpen()) {
    renderer->getInput();
    renderer->render();
  }

  renderer->end();

=======
>>>>>>> f4bf3d470911fa22689dee0c23d51b7b11b5b5b3
  return 0;
}
