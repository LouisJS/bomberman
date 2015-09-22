//
// Picture.cpp for Picture in /home/lecocq_l/Documents/projets/3-Semestre/bomberman
// 
// Made by louis lecocq
// Login   <lecocq_l@epitech.net>
// 
// Started on  Mon May 13 11:37:41 2013 louis lecocq
// Last update Sun Jun  9 15:34:37 2013 bigott-a
//

#include "Picture.hpp"
#include <iostream>

Picture::Picture()
{
}

Picture::Picture(float xt, float yt, float size_x_, float size_y_, int type, Action set)
{
  this->position_.x = xt;
  this->position_.y = yt;
  this->position_.z = 0.0;
  this->size_x = size_x_;
  this->size_y = size_y_;
  this->toDelete = false;
  this->type_ = type;
  this->set_ = set;
  this->clic = true;
}

Picture::~Picture()
{
}

void	Picture::setIG(InterfaceGraphique *ig)
{
  this->IG = ig;
}

void	Picture::initialize()
{
  if (this->type_ == 0)
    this->picture_ = gdl::Image::load("/Menu_assets/background.jpg");
  else if (this->type_ == 1)
    this->picture_ = gdl::Image::load("/Menu_assets/left_button.png");
  else
    this->picture_ = gdl::Image::load("/Menu_assets/right_button.png");
}

int	Picture::check_zone(gdl::Input &input)
{
  if (input.getMousePositionY() > 450 - (this->size_y / 2 + this->position_.y) &&
      input.getMousePositionY() < 450 - ((-1 * this->size_y / 2) + this->position_.y) &&
      input.getMousePositionX() > 800 + (-1 * this->size_x / 2 + this->position_.x) &&
      input.getMousePositionX() < 800 + (this->size_x / 2 + this->position_.x))
    {
      return (0);
    }
  return (-1);
}

int	Picture::update(gdl::GameClock const &gameClock, gdl::Input &input, std::list<AObject*> &list)
{
  (void)gameClock;
  (void)list;

  if (this->type_ == 1 && input.isMouseButtonDown(gdl::Mouse::Left) == true
      && this->clic == true
      && check_zone(input) == 0)
    {
      /* Minus */
      if (this->set_ == MAP)
	this->IG->set_map(this->IG->get_map() - 10);
      else if (this->set_ == NB_IA)
	this->IG->set_nb_ia(this->IG->get_nb_ia() - 1);
      this->clic = false;
    }
  else if (this->type_ == 2 && input.isMouseButtonDown(gdl::Mouse::Left) == true
	   && this->clic == true
	   && check_zone(input) == 0)
    {
      /* Plus */
      if (this->set_ == MAP)
	this->IG->set_map(this->IG->get_map() + 10);
      else if (this->set_ == NB_IA)
	this->IG->set_nb_ia(this->IG->get_nb_ia() + 1);
      this->clic = false;
    }
  if (input.isMouseButtonDown(gdl::Mouse::Left) == false)
    {
      this->clic = true;
    }
  return (0);
}

void	Picture::draw(void)
{
  this->picture_.bind();
  glBegin(GL_QUADS);

  // Vertex superieur gauche
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0.0f, this->size_y / 2 + this->position_.y, (-1 * this->size_x / 2) + this->position_.x);
  /// Vertex inferieur gauche
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0.0f, (-1 * this->size_y / 2) + this->position_.y, (-1 * this->size_x / 2) + this->position_.x);
  /// Vertex inferieur droit
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.0f, (-1 * this->size_y / 2) + this->position_.y, (this->size_x / 2) + this->position_.x);
  /// Vertex superieur droit
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.0f, (this->size_y / 2) + this->position_.y, (this->size_x / 2) + this->position_.x);
  glEnd();
}
