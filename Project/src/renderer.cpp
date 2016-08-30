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
  m_grid_box_size = 60;
  m_number_offset_x = 20;
  m_number_offset_y = 7;
  m_grid_ref = nullptr;
  m_selected_box = 100;
  m_incorrect_box = 100;
  m_game_won = false;
  m_selected_box_size = 60;
  m_easy_sudoku_x = 20;
  m_easy_sudoku_y = 120;
  m_easy_sudoku_width = 120;
  m_easy_sudoku_height = 50;
  m_medium_sudoku_x = 20;
  m_medium_sudoku_y = 175;
  m_medium_sudoku_width = 120;
  m_medium_sudoku_height = 50;
  m_hard_sudoku_x = 20;
  m_hard_sudoku_y = 230;
  m_hard_sudoku_width = 120;
  m_hard_sudoku_height = 50;
  m_reset_x = 850;
  m_reset_y = 120;
  m_reset_width = 100;
  m_reset_height = 50;
  m_credits_x = 5;
  m_credits_y = 750;
  m_win_x = 400;
  m_win_y = 20;

  m_font.loadFromFile("resources/arial.ttf");

  m_debug_text.setFont(m_font);
  m_debug_text.setString("");
  m_debug_text.setColor(sf::Color::White);
  m_debug_text.setCharacterSize(30);
  m_debug_text.setPosition(25, 100);

  m_easy_sudoku_text.setFont(m_font);
  m_easy_sudoku_text.setString("EASY");
  m_easy_sudoku_text.setColor(sf::Color::Black);
  m_easy_sudoku_text.setPosition(m_easy_sudoku_x + 20, m_easy_sudoku_y + 5);

  m_medium_sudoku_text.setFont(m_font);
  m_medium_sudoku_text.setString("MEDIUM");
  m_medium_sudoku_text.setColor(sf::Color::Black);
  m_medium_sudoku_text.setPosition(m_medium_sudoku_x, m_medium_sudoku_y + 5);

  m_hard_sudoku_text.setFont(m_font);
  m_hard_sudoku_text.setString("HARD");
  m_hard_sudoku_text.setColor(sf::Color::Black);
  m_hard_sudoku_text.setPosition(m_hard_sudoku_x + 20, m_hard_sudoku_y + 5);

  m_reset_text.setFont(m_font);
  m_reset_text.setColor(sf::Color::Black);
  m_reset_text.setString("RESET");
  m_reset_text.setPosition(m_reset_x, m_reset_y + 5);

  m_credits_text.setFont(m_font);
  m_credits_text.setCharacterSize(13);
  m_credits_text.setString("Guillermo Barco Munoz & Olmo Prieto Sanchez");
  m_credits_text.setPosition(m_credits_x, m_credits_y);

  m_win_text.setFont(m_font);
  m_win_text.setCharacterSize(40);
  m_win_text.setColor(sf::Color::Magenta);
  m_win_text.setString("WIN\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t  WIN");
  m_win_text.setPosition(m_win_x, m_win_y);
}

Renderer::~Renderer() {
  if (m_instance != nullptr) {
    delete m_instance;
  }

  if (m_grid_ref != nullptr) {
    delete m_grid_ref;
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

  sf::Image image;
  image.create(m_selected_box_size, m_selected_box_size, sf::Color(85, 162, 10, 255));
  m_selected_cell_texture.create(m_selected_box_size, m_selected_box_size);
  m_selected_cell_texture.update(image);
  
  m_selected_cell.setTexture(m_selected_cell_texture);

  m_error_cell_texture.loadFromFile("resources/error_cell.png");
  m_error_cell.setTexture(m_error_cell_texture);
  m_error_cell.setPosition(1000, 1000);

  sf::Image image2;
  image2.create(m_easy_sudoku_width, m_easy_sudoku_height, sf::Color::Green);
  m_easy_sudoku_texture.create(m_easy_sudoku_width, m_easy_sudoku_height);
  m_easy_sudoku_texture.update(image2);
  m_easy_sudoku.setTexture(m_easy_sudoku_texture);
  m_easy_sudoku.setPosition(m_easy_sudoku_x, m_easy_sudoku_y);

  sf::Image image3;
  image3.create(m_medium_sudoku_width, m_medium_sudoku_height, sf::Color::Yellow);
  m_medium_sudoku_texture.create(m_medium_sudoku_width, m_medium_sudoku_height);
  m_medium_sudoku_texture.update(image3);
  m_medium_sudoku.setTexture(m_medium_sudoku_texture);
  m_medium_sudoku.setPosition(m_medium_sudoku_x, m_medium_sudoku_y);

  sf::Image image4;
  image4.create(m_hard_sudoku_width, m_hard_sudoku_height, sf::Color::Red);
  m_hard_sudoku_texture.create(m_hard_sudoku_width, m_hard_sudoku_height);
  m_hard_sudoku_texture.update(image4);
  m_hard_sudoku.setTexture(m_hard_sudoku_texture);
  m_hard_sudoku.setPosition(m_hard_sudoku_x, m_hard_sudoku_y);

  sf::Image image5;
  image5.create(m_reset_width, m_reset_height, sf::Color::White);
  m_reset_texture.create(m_reset_width, m_reset_height);
  m_reset_texture.update(image5);
  m_reset.setTexture(m_reset_texture);
  m_reset.setPosition(m_reset_x, m_reset_y);
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

  // Button checking
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (mouse_pos.x > m_easy_sudoku_x && mouse_pos.x < m_easy_sudoku_x + m_easy_sudoku_width
      && mouse_pos.y > m_easy_sudoku_y && mouse_pos.y < m_easy_sudoku_y + m_easy_sudoku_height) {
      delete m_grid_ref;
      m_grid_ref = new Grid(1);
    } else if (mouse_pos.x > m_medium_sudoku_x && mouse_pos.x < m_medium_sudoku_x + m_medium_sudoku_width
      && mouse_pos.y > m_medium_sudoku_y && mouse_pos.y < m_medium_sudoku_y + m_medium_sudoku_height) {
      delete m_grid_ref;
      m_grid_ref = new Grid(2);
    } else if (mouse_pos.x > m_hard_sudoku_x && mouse_pos.x < m_hard_sudoku_x + m_hard_sudoku_width
      && mouse_pos.y > m_hard_sudoku_y && mouse_pos.y < m_hard_sudoku_y + m_hard_sudoku_height) {
      delete m_grid_ref;
      m_grid_ref = new Grid(3);
    } else if (mouse_pos.x > m_reset_x && mouse_pos.x < m_reset_x + m_reset_width
      && mouse_pos.y > m_reset_y && mouse_pos.y < m_reset_y + m_reset_height) {
      m_grid_ref->reset();
    }
  }
  //

  // Cell selection
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

      m_selected_box = x_pos + ROWSIZE * y_pos;
    } else {
      m_selected_box = 100;
    }
  }
  //

  // Number introduction
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
      m_movement_return_value = m_grid_ref->insertNumber(m_selected_box, number);

      if (m_movement_return_value.returnCode == NUMBERREPEATED) {
        short new_x, new_y;
        m_grid_ref->getMatrixPosition(m_movement_return_value.cellID, new_x, new_y);

        uint32 x_off = 0;
        uint32 y_off = 0;

        short k = 0;
        while (k <= new_x) {
          if (k % 3 == 0) {
            x_off += 3;
          } else {
            x_off += 1;
          }

          k++;
        }

        k = 0;
        while (k <= new_y) {
          if (k % 3 == 0) {
            y_off += 3;
          } else {
            y_off += 1;
          }

          k++;
        }

        m_error_cell.setPosition(m_grid_offset_x + m_grid_box_size * new_x + x_off,
          m_grid_offset_y + m_grid_box_size * new_y + y_off);
      } else {
        m_error_cell.setPosition(1000, 1000);
      }
    }
  }
  //


  if (m_grid_ref->isTheGameWon() == true) {
    m_game_won = true;
  } else {
    m_game_won = false;
  }
}

void Renderer::render() {
  m_window.clear();

  m_window.draw(m_grid);

  if (m_selected_box < 100) {
    short x, y;
    m_grid_ref->getMatrixPosition(m_selected_box, x, y);

    uint32 x_off = 0;
    uint32 y_off = 0;
    
    short k = 0;
    while (k <= x) {
      if (k % 3 == 0) {
        x_off += 3;
      } else {
        x_off += 1;
      }

      k++;
    }

    k = 0;
    while (k <= y) {
      if (k % 3 == 0) {
        y_off += 3;
      } else {
        y_off += 1;
      }

      k++;
    }

    m_selected_cell.setPosition(m_grid_offset_x + m_grid_box_size * x + x_off,
      m_grid_offset_y + m_grid_box_size * y + y_off);
    
    m_window.draw(m_selected_cell);
  }

  m_grid_offset_x += m_number_offset_x;
  m_grid_offset_y += m_number_offset_y;

  sf::Text text("", m_font);
  text.setCharacterSize(35);
  text.setStyle(sf::Text::Bold);

  m_window.draw(m_error_cell);

  uint32 placed_row = 0;
  uint32 placed_column = 0;
  uint32 hor_offset = 0;
  uint32 ver_offset = 3;
  for (uint32 i = 0; i < 9; i++) {
    for (uint32 j = 0; j < 9; j++) {
      short number = m_grid_ref->getCellNumber(m_grid_ref->getLinealPosition(j, i));
      if (number != 0) {
        std::string tmp = std::to_string(number);
        text.setString(tmp);
      } else {  // number == 0
        text.setString("");
      }
      if (m_grid_ref->isCellFixed(m_grid_ref->getLinealPosition(j, i)) == true) {
        text.setColor(sf::Color::Yellow);
      } else {
        text.setColor(sf::Color(200, 200, 200, 255));
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

  //m_window.draw(m_debug_text);

  m_window.draw(m_easy_sudoku);
  m_window.draw(m_easy_sudoku_text);
  m_window.draw(m_medium_sudoku);
  m_window.draw(m_medium_sudoku_text);
  m_window.draw(m_hard_sudoku);
  m_window.draw(m_hard_sudoku_text);
  m_window.draw(m_reset);
  m_window.draw(m_reset_text);
  m_window.draw(m_credits_text);

  if (m_game_won == true) {
    m_window.draw(m_win_text);
  }

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