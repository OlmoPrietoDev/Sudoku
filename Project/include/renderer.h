#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SFML/Graphics.hpp>

#include "Grid.h"

typedef unsigned int uint32;
typedef unsigned char byte;

class Renderer {
public:
  static Renderer* getInstance();

  void init(uint32 width = 1024, uint32 height = 768);
  void end();
  void getInput();
  void render();

  uint32 getWidth() const;
  uint32 getHeight() const;

  void setGrid(Grid *grid);
  
  bool isOpen() const;

private:
  Renderer();
  ~Renderer();

  static Renderer *m_instance;

  void setWidth(uint32 width);
  void setHeight(uint32 height);

  uint32 m_width;
  uint32 m_height;
  uint32 m_grid_offset_x;
  uint32 m_grid_offset_y;
  uint32 m_grid_box_size;
  uint32 m_number_offset_x;
  uint32 m_number_offset_y;
  uint32 m_number_gap;
  uint32 m_selected_box_size;
  uint32 m_easy_sudoku_x;
  uint32 m_easy_sudoku_y;
  uint32 m_easy_sudoku_width;
  uint32 m_easy_sudoku_height;
  uint32 m_medium_sudoku_x;
  uint32 m_medium_sudoku_y;
  uint32 m_medium_sudoku_width;
  uint32 m_medium_sudoku_height;
  uint32 m_hard_sudoku_x;
  uint32 m_hard_sudoku_y;
  uint32 m_hard_sudoku_width;
  uint32 m_hard_sudoku_height;
  uint32 m_reset_x;
  uint32 m_reset_y;
  uint32 m_reset_width;
  uint32 m_reset_height;
  uint32 m_credits_x;
  uint32 m_credits_y;
  uint32 m_win_x;
  uint32 m_win_y;
  Grid* m_grid_ref;
  short m_selected_box;
  short m_incorrect_box;
  bool m_game_won;
  Grid::MovementReturnValue m_movement_return_value;
  sf::RenderWindow m_window;
  sf::Sprite m_grid;
  sf::Sprite m_selected_cell;
  sf::Sprite m_error_cell;
  sf::Sprite m_easy_sudoku;
  sf::Sprite m_medium_sudoku;
  sf::Sprite m_hard_sudoku;
  sf::Sprite m_reset;
  sf::Texture m_grid_texture;
  sf::Texture m_selected_cell_texture;
  sf::Texture m_error_cell_texture;
  sf::Texture m_easy_sudoku_texture;
  sf::Texture m_medium_sudoku_texture;
  sf::Texture m_hard_sudoku_texture;
  sf::Texture m_reset_texture;
  sf::Font m_font;
  sf::Text m_debug_text;
  sf::Text m_easy_sudoku_text;
  sf::Text m_medium_sudoku_text;
  sf::Text m_hard_sudoku_text;
  sf::Text m_reset_text;
  sf::Text m_credits_text;
  sf::Text m_win_text;
};

#endif // __RENDERER_H__