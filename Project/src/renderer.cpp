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
  m_number_offset_x = 20;
  m_number_offset_y = 7;
  m_grid_ref = nullptr;
  m_selected_box = 100;
  m_incorrect_box = 100;
  m_incorrect_number = false;

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

  m_selected_cell_texture.create(m_grid_box_size, m_grid_box_size);
  //byte *data = (byte*)malloc(m_grid_box_size * m_grid_box_size);
  //for (uint32 i = 0; i < m_grid_box_size; i++) {
  //  for (uint32 j = 0; j < m_grid_box_size; j++) {
  //    int p = (j + m_grid_box_size * i) + 4;

  //    data[p] = 32;       // R
  //    data[p + 1] = 255;  // G
  //    data[p + 2] = 32;   // B
  //    data[p + 3] = 255;  // A;
  //  }
  //}

  sf::Image image;
  image.create(m_grid_box_size, m_grid_box_size, sf::Color(85, 162, 10, 255));
  m_selected_cell_texture.update(image);
  
  m_selected_cell.setTexture(m_selected_cell_texture);
  m_selected_cell.setPosition(10, 10);
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
    } else {
      m_selected_box = 100;
    }
  }

  if (m_selected_box < 100) {
    short number = 10;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
      number = 1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
      number = 2;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
      number = 3;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
      number = 4;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
      number = 5;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
      number = 6;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
      number = 7;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
      number = 8;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
      number = 9;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
      number = 0;
    }

    if (number < 10) {
      m_incorrect_number = !m_grid_ref->insertNumber(m_selected_box, number);
    }
  }
}

void Renderer::render() {
  m_window.clear();

  m_window.draw(m_grid);

  m_selected_cell.setPosition(m_grid_offset_x + 4, m_grid_offset_y + 4);
  m_window.draw(m_selected_cell);

  m_grid_offset_x += m_number_offset_x;
  m_grid_offset_y += m_number_offset_y;

  sf::Text text("1", m_font);
  text.setCharacterSize(35);
  text.setStyle(sf::Text::Bold);
  //text.setColor(sf::Color::White);
  //text.setPosition(m_grid_offset_x + m_grid_box_size * 0 + m_number_offset_x,
  //  m_grid_offset_y + m_grid_box_size * 0 + m_number_offset_y);
  ////m_window.draw(text);

  //text.setString("7");
  //text.setStyle(sf::Text::Regular);
  //text.setColor(sf::Color(180, 180, 180, 255));
  //text.setPosition(m_grid_offset_x + m_grid_box_size * 1 + m_number_offset_x,
  //  m_grid_offset_y + m_grid_box_size * 0 + m_number_offset_y);
  ////m_window.draw(text);

  uint32 placed_row = 0;
  uint32 placed_column = 0;
  uint32 hor_offset = 0;
  uint32 ver_offset = 3;
  for (uint32 i = 0; i < 9; i++) {
    for (uint32 j = 0; j < 9; j++) {
      short number = m_grid_ref->getCellNumber(m_grid_ref->getLinealPosition(j, i));
      //if (number != 0) {
        std::string tmp = std::to_string(number);
        text.setString(tmp);
      //} else {  // number == 0
      //  text.setString("");
      //}
      if (m_grid_ref->isCellFixed(m_grid_ref->getLinealPosition(j, i)) == true) {
        text.setColor(sf::Color::Yellow);
      } else {
        text.setColor(sf::Color(180, 180, 180, 255));
      }

      if (placed_row == 3) {
        placed_row = 0;
      }
      
      if (placed_row < 1) {
        hor_offset += 3;
      } else {
        hor_offset += 1;
      }

      placed_row++;

      text.setPosition(m_grid_offset_x + m_grid_box_size * j + hor_offset,
        m_grid_offset_y + m_grid_box_size * i + ver_offset);

      m_window.draw(text);
    }

    if (placed_column == 3) {
      placed_column = 0;
    }

    if (placed_column < 1) {
      ver_offset += 3;
    } else {
      ver_offset += 1;
    }

    placed_column++;

    hor_offset = 0;
  }

  m_grid_offset_x -= m_number_offset_x;
  m_grid_offset_y -= m_number_offset_y;

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