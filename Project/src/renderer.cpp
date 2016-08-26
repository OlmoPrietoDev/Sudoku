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
  m_number_offset_x = 23;
  m_number_offset_y = 10;
  m_selected_box = 100;

  m_font.loadFromFile("resources/arial.ttf");

  m_debug_text.setFont(m_font);
  m_debug_text.setString("");
  m_debug_text.setColor(sf::Color::White);
  m_debug_text.setCharacterSize(30);
  m_debug_text.setPosition(25, 100);
}

Renderer::~Renderer() {
  if (m_instance != nullptr) {
    delete m_instance;
  }
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

  // Debug for mouse position
  sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);
  std::string mouse_pos_s = "x: " + std::to_string(mouse_pos.x) + "\ny: "
    + std::to_string(mouse_pos.y);
  m_debug_text.setString(mouse_pos_s);
  //

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    uint32 x_pos = mouse_pos.x;
    x_pos -= m_grid_offset_x;
    while (x_pos % m_grid_box_size != 0) {
      x_pos--;
    }
    x_pos /= m_grid_box_size;

    uint32 y_pos = mouse_pos.y;
    y_pos -= m_grid_offset_y;
    while (y_pos % m_grid_box_size != 0) {
      y_pos--;
    }
    y_pos /= m_grid_box_size;

    if (x_pos < 9 && y_pos < 9) {
      std::string tmp = "\n\nx_box: " + std::to_string(x_pos) 
        + "\ny_box: " + std::to_string(y_pos);
      mouse_pos_s += tmp;
      m_debug_text.setString(mouse_pos_s);

      m_selected_box = x_pos + m_width * y_pos;
    }
  }
}

void Renderer::render() {
  m_window.clear();

  m_window.draw(m_grid);

  sf::Text text("1", m_font);
  text.setCharacterSize(35);
  text.setStyle(sf::Text::Bold);
  text.setColor(sf::Color::White);
  text.setPosition(m_grid_offset_x + m_grid_box_size * 0 + m_number_offset_x,
    m_grid_offset_y + m_grid_box_size * 0 + m_number_offset_y);
  //m_window.draw(text);

  text.setString("7");
  text.setStyle(sf::Text::Regular);
  text.setColor(sf::Color(180, 180, 180, 255));
  text.setPosition(m_grid_offset_x + m_grid_box_size * 1 + m_number_offset_x,
    m_grid_offset_y + m_grid_box_size * 0 + m_number_offset_y);
  //m_window.draw(text);


  for (uint32 i = 0; i < 9; i++) {
    for (uint32 j = 0; j < 9; j++) {
      short number = m_grid_ref->getCellNumber(m_grid_ref->getLinealPosition(j, i));
      std::string tmp = std::to_string(number);
      text.setString(tmp);
      text.setPosition(m_grid_offset_x + m_grid_box_size * j + m_number_offset_x,
        m_grid_offset_y + m_grid_box_size * i + m_number_offset_y);

      m_window.draw(text);
    }
  }

  m_window.draw(m_debug_text);

  m_window.display();
}

uint32 Renderer::getWidth() const {
  return m_width;
}

uint32 Renderer::getHeight() const {
  return m_height;
}

void Renderer::setGrid(Grid *g) {
  m_grid_ref = g;
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