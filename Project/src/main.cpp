#include <iostream>

#include "renderer.h"

int main() {

  Renderer* renderer = Renderer::getInstance();
  renderer->init();

  while (renderer->isOpen()) {
    renderer->getInput();
    renderer->render();
  }

  renderer->end();

  return 0;
}
