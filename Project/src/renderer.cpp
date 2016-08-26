#include "renderer.h"
#include <cassert>

/*uint32 Renderer::m_width = 0;
uint32 Renderer::m_height = 0;
sf::RenderWindow Renderer::m_window = sf::RenderWindow();
sf::Sprite Renderer::m_grid = sf::Sprite();
sf::Texture Renderer::m_grid_texture = sf::Texture();
uint32 Renderer::m_grid_offset_x = 220;
uint32 Renderer::m_grid_offset_y = 112;
uint32 Renderer::m_grid_box_size = 59;*/

Renderer* Renderer::m_instance = nullptr;

Renderer::Renderer() {
  m_width = 0;
  m_height = 0;
  m_grid_offset_x = 220;
  m_grid_offset_y = 112;
  m_grid_box_size = 59;
}

Renderer::~Renderer() {

}

Renderer* Renderer::getInstance() {
  if (m_instance == nullptr) {
    m_instance = new Renderer();
  } else {
    return m_instance;
  }
}

void Renderer::init(uint32 width, uint32 height) {
  if (m_window.isOpen()) {
    m_window.close(); // !!
  }

  m_window.create(sf::VideoMode(width, height), "Sudoku");

  m_width = width;
  m_height = height;

  bool successful = true;
  successful = m_grid_texture.loadFromFile("resources/sudoku_grid_w.png");
  assert(successful == true && "Failed to load grid image");

  m_grid.setTexture(m_grid_texture);
  m_grid.setPosition(m_grid_offset_x, m_grid_offset_y);
}

void Renderer::end() {
  if (m_window.isOpen()) {
    m_window.close();
  }
}

void Renderer::getInput() {
  sf::Event e;
  while (m_window.pollEvent(e)) {
    // Request for closing the window
    if (e.type == sf::Event::Closed) {
      m_window.close();
    }
  }
}

void Renderer::render() {
  m_window.clear();

  m_window.draw(m_grid);

  m_window.display();
}

uint32 Renderer::getWidth() const {
  return m_width;
}

uint32 Renderer::getHeight() const {
  return m_height;
}

bool Renderer::isOpen() const {
  return m_window.isOpen();
}

void Renderer::setWidth(uint32 width) {
  m_width = width;
}

void Renderer::setHeight(uint32 height) {
  m_height = height;
}