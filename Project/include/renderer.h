#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SFML/Graphics.hpp>

typedef unsigned int uint32;

class Renderer {
public:
  static Renderer* getInstance();

  void init(uint32 width = 1024, uint32 height = 768);
  void end();
  void getInput();
  void render();

  uint32 getWidth() const;
  uint32 getHeight() const;
  
  bool isOpen() const;

private:
  Renderer();
  ~Renderer();

  static Renderer *m_instance;

  void setWidth(uint32 width);
  void setHeight(uint32 height);

  uint32 m_width;
  uint32 m_height;
  sf::RenderWindow m_window;
  sf::Sprite m_grid;
  sf::Texture m_grid_texture;
  uint32 m_grid_offset_x;
  uint32 m_grid_offset_y;
  uint32 m_grid_box_size;
};

#endif // __RENDERER_H__